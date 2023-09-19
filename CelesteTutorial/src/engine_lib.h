#pragma once

#include <cstdio>

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
	sprintf_s(formatBuffer, "%s %s %s \033[0m", textColorTable[textColor], prefix, msg);

	char textBuffer[8192]{};
	sprintf_s(textBuffer, formatBuffer, args...);

	puts(textBuffer);
}


#define SM_TRACE(msg, ...) _log("TRACE: ", msg, text_Color_Green ##__VA_ARGS__)
#define SM_WARN(msg, ...) _log("WARNING: ", msg, text_Color_Yellow ##__VA_ARGS__)
#define SM_ERROR(msg, ...) _log("ERROR: ", msg, text_Color_Red ##__VA_ARGS__)

#define SM_ASSERT(condition, msg, ...)		\
{											\
	if (!(condition))						\
	{										\
		SM_ERROR(msg ##__VA_ARGS__);		\
		DEBUG_BREAK;						\
	}										\
}