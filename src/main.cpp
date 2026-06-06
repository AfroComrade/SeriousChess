//Using SDL and standard IO
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Constants/Constants.h"
#include "Constants/GameEntities.h"
#include "Logic/GameLogic.h"
#include "Init/loaders.h"
#include "Render.h"

void close()
{
	SDL_DestroyTexture(black_tile);
	black_tile = nullptr;
	SDL_DestroyTexture(white_tile);
	white_tile = nullptr;
	SDL_DestroyTexture(hover_tile);
	hover_tile = nullptr;
	
	SDL_DestroyTexture(black_bishop);
	SDL_DestroyTexture(black_king);
	SDL_DestroyTexture(black_knight);
	SDL_DestroyTexture(black_pawn);
	SDL_DestroyTexture(black_queen);
	SDL_DestroyTexture(black_rook);
	
    black_bishop = nullptr;
    black_king = nullptr;
    black_knight = nullptr;
    black_pawn = nullptr;
    black_queen = nullptr;
    black_rook = nullptr;

    SDL_DestroyTexture(white_bishop);
    SDL_DestroyTexture(white_king);
    SDL_DestroyTexture(white_knight);
    SDL_DestroyTexture(white_pawn);
    SDL_DestroyTexture(white_queen);
    SDL_DestroyTexture(white_rook);
	
	white_bishop = nullptr;
	white_king = nullptr;
	white_knight = nullptr;
	white_pawn = nullptr;
	white_queen = nullptr;
	white_rook = nullptr;

    MIX_DestroyTrack( gMusicTrack );
    gMusicTrack = nullptr;

    MIX_DestroyTrack( gEffectTrack );
    gEffectTrack = nullptr;

    MIX_DestroyAudio( gScratchAudio );
    gScratchAudio = nullptr;
    MIX_DestroyAudio( gHighAudio );
    gHighAudio = nullptr;
    MIX_DestroyAudio( gMediumAudio );
    gMediumAudio = nullptr;
    MIX_DestroyAudio( gLowAudio );
    gLowAudio = nullptr;

    MIX_DestroyMixer( gMixer );
    gMixer = nullptr;
	
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

int initialize()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		SDL_Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}

	//Create window
	window = SDL_CreateWindow( "SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if( window == NULL )
	{
		SDL_Log( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}

	//Create renderer in window
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("Renderer could not initialize!: %s\n", SDL_GetError() );
		return 0;
	}

	if (!TTF_Init())
		SDL_Log("Error occurred with TTFL %s\n", SDL_GetError());

	if (!MIX_Init())
		SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());

	if( gMixer = MIX_CreateMixerDevice( SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr ); gMixer == nullptr )
		SDL_Log( "SDL_mixer could not create mixer! SDL_mixer Error: %s\n", SDL_GetError() );

	std::string fileString = std::string(FONT_PATH) + "Roboto-Medium.ttf";
	const char* filePath = fileString.c_str();
	font = TTF_OpenFont(filePath, 16.0f);

	SDL_Log("Current video driver: %s\n", SDL_GetCurrentVideoDriver() );
	SDL_Log("Renderer picked: %s\n", SDL_GetRendererName(renderer) );

	loadMedia();
	loadTiles();
	loadObjects();
	renderBackground(0, 0);

	SDL_PropertiesID props = SDL_CreateProperties();
	SDL_SetNumberProperty( props, MIX_PROP_PLAY_LOOPS_NUMBER, -1 );
	MIX_SetTrackGain( gMusicTrack, 0.5f);
	MIX_PlayTrack( gMusicTrack, props );
	SDL_DestroyProperties( props );
	return 1;
}

int main( int argc, char* args[] )
{
	if (initialize() == 0)
		return 0;

	SDL_Event E;
	bool quit{ false };
	struct timespec lastFrameTime;
	timespec_get(&lastFrameTime, TIME_UTC);
	float mouse_x = 0;
	float mouse_y = 0;
	while (quit == false)
	{

		while (SDL_PollEvent(&E) == true)
		{			
			if (E.type == SDL_EVENT_MOUSE_MOTION) {
				mouse_x = E.motion.x;
				mouse_y = E.motion.y;
			}
			else if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				int tile_x = mouse_x / TILE_WIDTH;
				int tile_y = mouse_y / TILE_HEIGHT;

				selected_object = detectObject(mouse_x, mouse_y, current_player);
				if (selected_object != nullptr)
				{
					SelectedTile[0] = tile_y;
					SelectedTile[1] = tile_x;
					setMovableTiles(selected_object->pieceType);
					MIX_SetTrackAudio( gEffectTrack, gLowAudio );
					MIX_PlayTrack( gEffectTrack, 0 );
				}
			}
			else if (E.type == SDL_EVENT_MOUSE_BUTTON_UP)
			{
				if (selected_object != nullptr)
				{
					int tile_x = mouse_x / TILE_WIDTH;
					int tile_y = mouse_y / TILE_HEIGHT;
					if (tiles[tile_y][tile_x]->toMove)
					{
						if (tiles[tile_y][tile_x]->obj != nullptr)
						{
							initParticles(tiles[tile_y][tile_x]->obj->objTexture, mouse_x, mouse_y);
							MIX_SetTrackAudio( gEffectTrack, gHighAudio );
							MIX_PlayTrack( gEffectTrack, 0 );
						} else {
							MIX_SetTrackAudio( gEffectTrack, gLowAudio );
							MIX_PlayTrack( gEffectTrack, 0 );
						}
						
						tiles[tile_y][tile_x]->obj = selected_object;
						current_player = (current_player == WHITE) ? BLACK : WHITE;
					}
					else
					{
						tiles[SelectedTile[0]][SelectedTile[1]]->obj = selected_object;
					}
					selected_object = nullptr;
					removeMovableTiles();
					if (checkWinCondition())
						quit = true;
				}
			}
			else if ((E.type == SDL_EVENT_KEY_DOWN) && (E.key.key == SDLK_ESCAPE))
			{
				quit = true;
			}
		}
		
		if (hasPassedOneFrame(lastFrameTime))
		{
			renderFrame(mouse_x, mouse_y);
			timespec_get(&lastFrameTime, TIME_UTC);
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	close();

	SDL_Quit();

	return 0;
}
