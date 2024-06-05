#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "../texture/texture.h"
#include "../animation/animation.h"
#include "../animation/animationSet.h"
#include "../physics/physics.h"
#include "../collision/collision.h"

typedef struct EngineObject EngineObject;

struct EngineObject {
    int positionX;
    int positionY;

    double angle;
    SDL_RendererFlip flip;

    Texture* texture;

    Animation* animation;
    AnimationSet* animationSet;

    Physics* physics;

    CollisionBox* collisionBox;

    void (*controller)(EngineObject* object);
    void* objectData;
};

EngineObject* createEngineObject(int positionX, int positionY);
void destroyEngineObject(EngineObject* object);
void updateEngineObject(EngineObject* object);

void addTextureToEngineObject(SDL_Renderer* renderer, EngineObject* object, char* path);
void addAnimationToEngineObject(SDL_Renderer* renderer, EngineObject* object, char* name, char* pathAndPrefix, int numFrames, int frameDuration, bool looping, bool mustFinish);
void addAnimationToEngineObjectAnimationSet(SDL_Renderer* renderer, EngineObject* object, char* name, char* pathAndPrefix, int numFrames, int frameDuration, bool looping, bool mustFinish);

#endif // ENGINEOBJECT_H