
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "../Constants/GameEntities.h"
#include "../Constants/Constants.h"
#include "loaders.h"

SDL_Texture* black_tile = nullptr;
SDL_Texture* white_tile = nullptr;
SDL_Texture* hover_tile = nullptr;

SDL_Texture* black_bishop = nullptr;
SDL_Texture* black_king = nullptr;
SDL_Texture* black_knight = nullptr;
SDL_Texture* black_pawn = nullptr;
SDL_Texture* black_queen = nullptr;
SDL_Texture* black_rook = nullptr;

SDL_Texture* white_bishop = nullptr;
SDL_Texture* white_king = nullptr;
SDL_Texture* white_knight = nullptr;
SDL_Texture* white_pawn = nullptr;
SDL_Texture* white_queen = nullptr;
SDL_Texture* white_rook = nullptr;

TTF_Font* font = nullptr;

MIX_Mixer* gMixer = nullptr;

MIX_Track* gMusicTrack = nullptr;

MIX_Audio* gScratchAudio = nullptr;
MIX_Audio* gHighAudio = nullptr;
MIX_Audio* gMediumAudio = nullptr;
MIX_Audio* gLowAudio = nullptr;
MIX_Track* gEffectTrack = nullptr;

Tile* tiles[TILE_Y][TILE_X] = {};


Tile* loadTile(int tileX, int tileY, int tile_y_start, SDL_Texture* tileTexture, SDL_Texture* hoverTexture)
{
    Tile* tile = new Tile();
    tile->tileTexture = tileTexture;
    tile->tileRect.x = tileX * TILE_WIDTH;
    tile->tileRect.y = tile_y_start;

    tile->tileRect.h = TILE_HEIGHT;
    tile->tileRect.w = TILE_WIDTH;
    tile->hoverTexture = hoverTexture;

    return tile;
}

GameObject* loadGameObject(SDL_Texture* objTexture, PieceType pieceType, Owner owner)
{
    GameObject* obj = new GameObject();
    obj->objTexture = objTexture;
    obj->pieceType = pieceType;
    obj->owner = owner;

    return obj;
}

void loadTexture(SDL_Texture** texture, std::string imagePath, SDL_Renderer* renderer)
{
    SDL_Surface* tempSurface;
    tempSurface = IMG_Load(imagePath.c_str());
    if (!tempSurface)
    {
        SDL_Log("IMG_Load failed: %s\n", SDL_GetError());
    }

    *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (!(*texture))
    {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
    }

    SDL_DestroySurface(tempSurface);
}

void loadTextures(SDL_Renderer* renderer)
{
    std::string tileLoc;

    tileLoc = ASSET_PATH + "" + "board_square_black.png";
    loadTexture(&black_tile, tileLoc, renderer);

    tileLoc = ASSET_PATH + "" + "board_square_white.png";
    loadTexture(&white_tile, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "Square.png";
    loadTexture(&hover_tile, tileLoc, renderer);

    tileLoc = ASSET_PATH + "" + "black_bishop.png";
    loadTexture(&black_bishop, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "black_king.png";
    loadTexture(&black_king, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "black_knight.png";
    loadTexture(&black_knight, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "black_pawn.png";
    loadTexture(&black_pawn, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "black_queen.png";
    loadTexture(&black_queen, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "black_rook.png";
    loadTexture(&black_rook, tileLoc, renderer);

    tileLoc = ASSET_PATH + "" + "white_bishop.png";
    loadTexture(&white_bishop, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "white_king.png";
    loadTexture(&white_king, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "white_knight.png";
    loadTexture(&white_knight, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "white_pawn.png";
    loadTexture(&white_pawn, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "white_queen.png";
    loadTexture(&white_queen, tileLoc, renderer);
    tileLoc = ASSET_PATH + "" + "white_rook.png";
    loadTexture(&white_rook, tileLoc, renderer);
}

void loadAudio()
{
    std::string fileString = std::string(FONT_PATH) + "Roboto-Medium.ttf";
    const char* filePath = fileString.c_str();
    font = TTF_OpenFont(filePath, 16.0f);

    std::string audioString = std::string(AUDIO_PATH) + "scratch.wav";
    const char* audioPath = audioString.c_str();

    if( gScratchAudio = MIX_LoadAudio( gMixer, audioPath, true ); gScratchAudio == nullptr )
        SDL_Log( "Unable to load scratch sound! SDL_mixer error: %s\n", SDL_GetError() );

    audioString = std::string(AUDIO_PATH) + "high.wav";
    audioPath = audioString.c_str();
    if( gHighAudio = MIX_LoadAudio( gMixer, audioPath, true ); gScratchAudio == nullptr )
        SDL_Log( "Unable to load high sound! SDL_mixer error: %s\n", SDL_GetError() );

    audioString = std::string(AUDIO_PATH) + "low.wav";
    audioPath = audioString.c_str();
    if( gLowAudio = MIX_LoadAudio( gMixer, audioPath, true ); gScratchAudio == nullptr )
        SDL_Log( "Unable to load low sound! SDL_mixer error: %s\n", SDL_GetError() );

    if( gEffectTrack = MIX_CreateTrack( gMixer ); gEffectTrack == nullptr )
        SDL_Log( "Failed to create sound effect track! SDL_mixer Error: %s\n", SDL_GetError() );

    audioString = std::string(AUDIO_PATH) + "genesis.wav";
    audioPath = audioString.c_str();
    SDL_Log(audioPath);
    MIX_Audio* musicAudio = MIX_LoadAudio( gMixer, audioPath, false );
    if( musicAudio == nullptr )
        SDL_Log( "Unable to load music! SDL_mixer error: %s\n", SDL_GetError() );

    gMusicTrack = MIX_CreateTrack( gMixer );

    if( gMusicTrack == nullptr )
        SDL_Log( "Failed to create music track! SDL_mixer Error: %s\n", SDL_GetError() );

    MIX_SetTrackAudio( gMusicTrack, musicAudio );

    MIX_DestroyAudio( musicAudio );
}

void loadTiles()
{
    for (int i = 0; i < TILE_Y; i++)
    {
        int tile_y_start = (i)*TILE_HEIGHT;

        for (int j = 0; j < TILE_X; j++)
        {
            SDL_Texture* tileTexture = (i + j) % 2 == 1 ? black_tile : white_tile;
            tiles[i][j] = loadTile(j, i, tile_y_start, tileTexture, hover_tile);
        }
    }
}


void loadObjects()
{
    PieceType pieceTypes[] = {
        ROOK, KNIGHT, BISHOP, QUEEN,
        KING, BISHOP, KNIGHT, ROOK
    };

    SDL_Texture* blackTextures[] = {
        black_rook, black_knight, black_bishop, black_queen,
        black_king, black_bishop, black_knight, black_rook
    };

    SDL_Texture* whiteTextures[] = {
        white_rook, white_knight, white_bishop, white_queen,
        white_king, white_bishop, white_knight, white_rook
    };

    for (int col = 0; col < TILE_X; ++col)
    {
        tiles[0][col]->obj = loadGameObject(blackTextures[col], pieceTypes[col], BLACK);
        tiles[1][col]->obj = loadGameObject(black_pawn, PAWN, BLACK);
        tiles[6][col]->obj = loadGameObject(white_pawn, PAWN, WHITE);
        tiles[7][col]->obj = loadGameObject(whiteTextures[col], pieceTypes[col], WHITE);
    }
}
