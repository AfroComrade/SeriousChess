#pragma once

#include <SDL3/SDL.h>
#include <string>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

const int BOARD_WIDTH = SCREEN_WIDTH * 0.8;
const int BOARD_HEIGHT = SCREEN_WIDTH * 0.8;

const int TILE_X = 8;
const int TILE_Y = 8;

const int TILE_WIDTH = BOARD_WIDTH / TILE_X;
const int TILE_HEIGHT = BOARD_HEIGHT / TILE_Y;

const std::string BASE_PATH = SDL_GetBasePath();
const std::string ASSET_PATH = BASE_PATH + "assets/";
const std::string FONT_PATH = ASSET_PATH + "fonts/";
const std::string AUDIO_PATH = ASSET_PATH + "audio/";

const int MAX_PARTICLES = 20;
const int PARTICLE_LIFETIME = 30;
const float PARTICLE_SIZE[2] = {20, 20};

const SDL_Color fontColor = { 255, 255, 255, SDL_ALPHA_OPAQUE };
