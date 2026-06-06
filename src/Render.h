#include <SDL3_image/SDL_image.h>
#include <time.h>
#include "Constants/GameEntities.h"
#include "Constants/Constants.h"

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_FRect rect;

extern Particle* particles[MAX_PARTICLES];

void renderBackground(float mouse_x, float mouse_y);
void renderUI();
void initParticles(SDL_Texture* texture, int posX, int posY);
void renderParticles();
bool hasPassedOneFrame(timespec lastFrameTime);
void loadMedia();
void renderFrame(float mouse_x, float mouse_y);
