#include "game.h"

#include "assets.h"
#include "render_interface.h"
#include "engine_lib.h"

// ###############################################################
//							Game Constants
// ###############################################################

// ###############################################################
//							Game Structs
// ###############################################################

// ###############################################################
//							Game Functions
// ###############################################################


void update_game()
{
	for (size_t column = 0; column < 20; ++column)
	{
		for (size_t row = 0; row < 20; ++row)
		{
			draw_sprite(SPRITE_DICE, { static_cast<float>(column * 100), static_cast<float>(row * 100) }, { 50, 50 });
			
		}
	}
}
