#ifndef RENDERER_H
#define RENDERER_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "../config.h"
#include "../object/engineObject.h"

typedef struct Renderer {
    SDL_Renderer* SDLRenderer;
    SDL_Window* SDLWindow;
    int width;
    int height;
} Renderer;

Renderer* createRenderer();
void destroyRenderer(Renderer* renderer);

void updateRenderer(Renderer* renderer);
void clearRenderer(Renderer* renderer);

void renderEngineObject(Renderer* renderer, EngineObject* object);

#endif // RENDERER_H