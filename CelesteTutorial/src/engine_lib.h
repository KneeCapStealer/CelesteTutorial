#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/stat.h>

// ###############################################################
//							  Defines
// ###############################################################
#if _WIN32
#define DEBUG_BREAK __debugbreak()

#elif __linux__
#define DebugBreak() __builtin_debugtrap()

#elif __APPLE__
#define DebugBreak() __builtin_trap()
#endif
// ###############################################################
//							  Logging
// ###############################################################

enum TextColor
{
	text_Color_Black,
	text_Color_Red,
	text_Color_Green,
	text_Color_Yellow,
	text_Color_Blue,
	text_Color_Magenta,
	text_Color_Cyan,
	text_Color_White,
	text_Color_Bright_Black,
	text_Color_Bright_Red,
	text_Color_Bright_Green,
	text_Color_Bright_Yellow,
	text_Color_Bright_Blue,
	text_Color_Bright_Magenta,
	text_Color_Bright_Cyan,
	text_Color_Bright_White,
	text_Color_Count
};


template<typename... Args>
void _log(const char* prefix, const char* msg, const TextColor textColor, Args... args)
{
	const static char* textColorTable[text_Color_Count]
	{
		"\x1b[30m", // black
		"\x1b[31m", // red
		"\x1b[32m", // green
		"\x1b[33m", // yellow
		"\x1b[34m", // blue
		"\x1b[35m", // magenta
		"\x1b[36m", // cyan
		"\x1b[37m", // white
		"\x1b[90m", // bright_black
		"\x1b[91m", // bright_red
		"\x1b[92m", // bright_green
		"\x1b[93m", // bright_yellow
		"\x1b[94m", // bright_blue
		"\x1b[95m", // bright_magenta
		"\x1b[96m", // bright_cyan
		"\x1b[97m", // bright_white
	};

	char formatBuffer[8192]{};
	sprintf(formatBuffer, "%s %s %s \033[0m", textColorTable[textColor], prefix, msg);

	char textBuffer[8192]{};
	sprintf(textBuffer, formatBuffer, args...);

	puts(textBuffer);
}


#define SM_TRACE(msg, ...) _log("TRACE: ", msg, text_Color_Green, ##__VA_ARGS__)
#define SM_WARN(msg, ...) _log("WARNING: ", msg, text_Color_Yellow, ##__VA_ARGS__)
#define SM_ERROR(msg, ...) _log("ERROR: ", msg, text_Color_Red, ##__VA_ARGS__)

#define SM_ASSERT(condition, msg, ...)		\
{											\
	if (!(condition))						\
	{										\
		SM_ERROR(msg, ##__VA_ARGS__);		\
		DEBUG_BREAK;						\
	}										\
}


// ###############################################################
//							  Bump Allocator
// ###############################################################
struct BumpAllocator
{
	size_t capacity;
	size_t used;
	void* memory;
};

inline BumpAllocator make_bump_allocator(const size_t size)
{
	BumpAllocator bumpAllocator{};

	bumpAllocator.memory = static_cast<char*>(malloc(size));
	if (bumpAllocator.memory)
	{
		bumpAllocator.capacity = size;
		memset(bumpAllocator.memory, 0xCD, size); // Sets unused memory to CD for easier debugging
	}
	else
		SM_ASSERT(false, "Failed to allocate memory");

	return bumpAllocator;
}

inline void* bump_alloc(BumpAllocator* bumpAllocator, const size_t size)
{
	void* result = nullptr;

	// This makes the size go in increments of 8. Meaning if you give size 9 it jumps to 16
	size_t alignedSize = size + 7 & ~7;
	if (bumpAllocator->used + alignedSize <= bumpAllocator->capacity)
	{
		result = static_cast<char*>(bumpAllocator->memory) + bumpAllocator->used;
		bumpAllocator->used += alignedSize;
	}
	else
		SM_ASSERT(false, "BumpAllocator is full");

	return result;
}

inline void bump_free(const BumpAllocator* bumpAllocator)
{
	free(bumpAllocator->memory);
}


// ###############################################################
//							File - IO
// ###############################################################

inline long long get_timestamp(const char* filePath)
{
	struct stat fileStat{};
	stat(filePath, &fileStat);
	return fileStat.st_mtime;
}

inline bool file_exists(const char* filePath)
{
	SM_ASSERT(filePath, "No filepath supplied!");

	FILE* file = fopen(filePath, "rb");
	if (!file)
		return false;

	fclose(file);
	return true;
}

inline long get_file_size(const char* filePath)
{
	SM_ASSERT(filePath, "No filepath supplied!");

	FILE* file = fopen(filePath, "rb");
	if (!file)
	{
		SM_ERROR("Failed opening file: %s", filePath);
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	fclose(file);

	return fileSize;
}

inline void read_file(const char* filePath, int* fileSize, char* buffer)
{
	SM_ASSERT(filePath, "No filePath supplied!");
	SM_ASSERT(fileSize, "No fileSize supplied!");
	SM_ASSERT(buffer, "No buffer supplied!");

	*fileSize = 0;
	FILE* file = fopen(filePath, "rb");
	if (!file)
	{
		SM_ERROR("Failed opening file: %s", filePath);
		buffer = nullptr;
		return;
	}

	fseek(file, 0, SEEK_END);
	*fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	fread(buffer, sizeof(char), *fileSize, file);
	*(buffer + *fileSize) = '\0'; // set null termination character
	fclose(file);
}

inline char* read_file(const char* filePath, int* fileSize, BumpAllocator* bumpAllocator)
{
	long fileSize2 = get_file_size(filePath);

	char* buffer = nullptr;
	if (fileSize2)
	{
		buffer = static_cast<char*>(bump_alloc(bumpAllocator, fileSize2 + 1));
		read_file(filePath, fileSize, buffer);
	}

	return buffer;
}

inline void write_file(const char* filePath, const char* buffer, const int size)
{
	SM_ASSERT(filePath, "No filePath supplied!");
	SM_ASSERT(buffer, "No buffer supplied!");

	FILE* file = fopen(filePath, "wb");
	if (!file)
	{
		SM_ERROR("Failed opening file: %s", filePath);
		return;
	}

	fwrite(buffer, sizeof(char), size, file);
	fclose(file);
}

inline bool copy_file(const char* filePath, const char* outFilePath, void* buffer)
{
	SM_ASSERT(filePath, "No filePath supplied!");
	SM_ASSERT(outFilePath, "No outFilePath supplied!");
	SM_ASSERT(buffer, "no buffer specified");

	int fileSize = 0;
	read_file(filePath, &fileSize, static_cast<char*>(buffer));

	FILE* file = fopen(filePath, "wb");
	if (!file)
	{
		SM_ERROR("Couldnt open file: %s", outFilePath);
		return false;
	}

	if (!fwrite(buffer, sizeof(char), fileSize, file))
	{
		SM_ERROR("Couldn't write to file: %s", outFilePath);
		return false;
	}

	fclose(file);
	return true;
}

inline bool copy_file(const char* filePath, const char* outFilePath, BumpAllocator* bumpAllocator)
{
	if (const int fileSize = get_file_size(filePath))
	{
		char* buffer = static_cast<char*>(bump_alloc(bumpAllocator, fileSize + 1));
	
		return copy_file(filePath, outFilePath, buffer);
	}

	return false;
}