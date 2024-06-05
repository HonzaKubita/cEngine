#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

typedef struct Texture {
    SDL_Texture* texture;
    int width;
    int height;
} Texture;

Texture* createTexture(SDL_Renderer* renderer, const char* path);
void destroyTexture(Texture* texture);

#endif // TEXTURE_H