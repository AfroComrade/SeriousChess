#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

enum Owner {
	BLACK,
	WHITE
};

enum PieceType {
	KING,
	QUEEN,
	PAWN,
	BISHOP,
	KNIGHT,
	ROOK
};

struct GameObject {
	SDL_Texture* objTexture;
	Owner owner;
	PieceType pieceType;
};

struct Tile {
	SDL_FRect tileRect;
	SDL_Texture* tileTexture;
	GameObject* obj;
	SDL_Texture* hoverTexture;
	bool toMove;
};

struct Particle{
	SDL_Texture* particleTexture;
	SDL_FRect particleRect;
	int velocity[2];
	int aliveTime;
};
