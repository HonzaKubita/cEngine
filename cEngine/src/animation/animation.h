#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "../texture/texture.h"

typedef struct Animation {
    char* name;
    int numFrames;
    int currentFrame;
    int frameDuration;
    bool isLooping;
    bool mustFinish;
    Texture** frames;
    Uint32 _currentFrameStart;
    Texture** targetTexturePointer;
} Animation;

Animation* createAnimation(char* name, int numFrames, int frameDuration, bool isLooping, bool mustFinish, Texture** targetTexturePointer, Texture** frames);
void destroyAnimation(Animation* animation);
void updateAnimation(Animation* animation);

Animation* loadAnimation(SDL_Renderer* renderer, Texture** targetTexturePointer, char* name, char* pathAndPrefix, int numFrames, int frameDuration, bool looping, bool mustFinish);

#endif // ANIMATION_H