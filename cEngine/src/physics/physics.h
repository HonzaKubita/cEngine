#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>

typedef struct Physics {
    // Velocity
    float velocityX;
    float velocityY;

    // Position
    int* positionXVar;
    int* positionYVar;

    // Flags
    bool hasGravity;
    
    bool onGround;

    // Time
    Uint32 lastUpdate;
} Physics;

Physics* createPhysics(int* positionXVar, int* positionYVar);
void destroyPhysics(Physics* physics);

void updatePhysics(Physics* physics);

#endif // PHYSICS_H