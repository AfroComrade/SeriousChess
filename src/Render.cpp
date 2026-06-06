#include <SDL3_image/SDL_image.h>
#include <time.h>
#include "Constants/GameEntities.h"
#include "Constants/Constants.h"
#include "Init/loaders.h"
#include "Logic/GameLogic.h"

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_FRect rect = SDL_FRect();
Owner current_player = WHITE;

Particle* particles[MAX_PARTICLES] = {};

void renderBackground(float mouse_x, float mouse_y)
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
    SDL_RenderClear(renderer);

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            SDL_RenderTexture(renderer, tiles[x][y]->tileTexture, nullptr, &tiles[x][y]->tileRect);
            if (tiles[x][y]->obj != nullptr)
            {
                SDL_RenderTexture(renderer, tiles[x][y]->obj->objTexture, nullptr, &tiles[x][y]->tileRect);
            }

            if ((mouse_x > x * TILE_WIDTH)
                && (mouse_x < (x + 1) * TILE_WIDTH)
                && (mouse_y > y * TILE_HEIGHT)
                && (mouse_y < (y + 1) * TILE_HEIGHT)
                && (tiles[x][y]->hoverTexture != nullptr))
            {
                //SDL_RenderTexture(renderer, tiles[x][y]->hoverTexture, nullptr, &tiles[x][y]->tileRect);
            }

            if (tiles[x][y]->toMove)
            {
                SDL_RenderTexture(renderer, tiles[x][y]->hoverTexture, nullptr, &tiles[x][y]->tileRect);
            }
        }
    }

    if ((mouse_x < BOARD_WIDTH)
        && (mouse_y < BOARD_HEIGHT))
    {
        int highlight_x = mouse_x / TILE_WIDTH;
        int highlight_y = mouse_y / TILE_HEIGHT;
        SDL_RenderTexture(renderer, tiles[highlight_y][highlight_x]->hoverTexture, nullptr, &tiles[highlight_y][highlight_x]->tileRect);
    }
}

void renderUI()
{
    std::string current_player_text = "White";
    if (current_player == BLACK)
        current_player_text = "Black";

    const char* currentText = current_player_text.c_str();
    SDL_FRect textRect = SDL_FRect();
    textRect.h = TILE_HEIGHT;
    textRect.w = TILE_WIDTH * 2;
    textRect.x = 10;
    textRect.y = BOARD_HEIGHT + 10;
    SDL_Texture* textTexture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, currentText, 0, fontColor);
    if (textSurface)
    {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_DestroySurface(textSurface);

    }

    if (!textTexture)
        SDL_Log("Couldn't create text: %s\n", SDL_GetError());

    SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
}

void initParticles(SDL_Texture* texture, int posX, int posY)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i] = new Particle();
        particles[i]->particleTexture = texture;
        particles[i]->particleRect = SDL_FRect();
        particles[i]->particleRect.x = posX + ((rand() % 11)-5);
        particles[i]->particleRect.y = posY + ((rand() % 11)-5);
        particles[i]->particleRect.h = PARTICLE_SIZE[0];
        particles[i]->particleRect.w = PARTICLE_SIZE[1];
        particles[i]->velocity[0] = ((rand() % 11)-5);
        particles[i]->velocity[1] = ((rand() % 11)-5);
        particles[i]->aliveTime = 0;
    }
}

void renderParticles()
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i] == nullptr)
            continue;

        if (particles[i]->aliveTime >= PARTICLE_LIFETIME)
        {
            particles[i] = nullptr;
            continue;
        }

        particles[i]->aliveTime += 1;
        SDL_RenderTexture(renderer, particles[i]->particleTexture, NULL, &particles[i]->particleRect);

        particles[i]->particleRect.x += particles[i]->velocity[0];
        particles[i]->particleRect.y += particles[i]->velocity[1];
    }
}

// Handles frametime. Basic frametime to throttle frames to 60 fps
bool hasPassedOneFrame(timespec lastFrameTime)
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);

    long long now_ms = now.tv_sec * 1000LL + now.tv_nsec / 1000000;
    long long last_ms = lastFrameTime.tv_sec * 1000LL + lastFrameTime.tv_nsec / 1000000;

    if ((last_ms + 17) < now_ms)
    {
        return true;
    }

    return false;
}

void loadMedia()
{
    loadTextures(renderer);
    loadAudio();
    loadTiles();
}

void renderFrame(float mouse_x, float mouse_y)
{
    renderBackground(mouse_x, mouse_y);
    if (selected_object != nullptr)
    {
        SDL_FRect rect = SDL_FRect();
        rect.h = TILE_HEIGHT;
        rect.w = TILE_WIDTH;
        rect.x = mouse_x - (TILE_WIDTH / 2);
        rect.y = mouse_y - (TILE_HEIGHT / 2);
        SDL_RenderTexture(renderer, selected_object->objTexture, nullptr, &rect);
    }
    renderUI();
    renderParticles();
    SDL_RenderPresent(renderer);
}
