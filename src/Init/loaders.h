#pragma once

#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../Constants/Constants.h"
#include "../Constants/GameEntities.h"


extern SDL_Texture* black_tile;
extern SDL_Texture* white_tile;
extern SDL_Texture* hover_tile;

extern SDL_Texture* black_bishop;
extern SDL_Texture* black_king;
extern SDL_Texture* black_knight;
extern SDL_Texture* black_pawn;
extern SDL_Texture* black_queen;
extern SDL_Texture* black_rook;

extern SDL_Texture* white_bishop;
extern SDL_Texture* white_king;
extern SDL_Texture* white_knight;
extern SDL_Texture* white_pawn;
extern SDL_Texture* white_queen;
extern SDL_Texture* white_rook;

extern TTF_Font* font;

extern MIX_Mixer* gMixer;

extern MIX_Track* gMusicTrack;

extern MIX_Audio* gScratchAudio;
extern MIX_Audio* gHighAudio;
extern MIX_Audio* gMediumAudio;
extern MIX_Audio* gLowAudio;

extern MIX_Track* gEffectTrack;

extern Tile* tiles[TILE_Y][TILE_X];


Tile* loadTile(int tileX, int tileY, int tile_y_start, SDL_Texture* tileTexture, SDL_Texture* hoverTexture);
GameObject* loadGameObject(SDL_Texture* objTexture, PieceType pieceType, Owner owner);
void loadTexture(SDL_Texture** texture, std::string imagePath, SDL_Renderer* renderer);

void loadTextures(SDL_Renderer* renderer);
void loadAudio();
void loadTiles();
void loadObjects();
