#include "physics.h"

Physics* createPhysics(int* positionXVar, int* positionYVar) {
    // Allocate memory for the physics
    Physics* physics = malloc(sizeof(Physics));
    if (physics == NULL) {
        fprintf(stderr, "Failed to allocate memory for the physics\n");
        return NULL;
    }

    physics->positionXVar = positionXVar;
    physics->positionYVar = positionYVar;

    // Initialize the default values
    physics->velocityX = 0;
    physics->velocityY = 0;
    physics->hasGravity = false;
    physics->onGround = false;

    return physics;
}

void destroyPhysics(Physics* physics) {
    // Check if the physics is not NULL
    if (physics == NULL) {
        return;
    }

    // Free the memory allocated for the physics
    free(physics);
}

void updatePhysics(Physics* physics) {
    // Check if the physics is not NULL
    if (physics == NULL) {
        return;
    }

    // Calculate the delta time
    Uint32 now = SDL_GetTicks();
    double deltaTime = (double)(now - physics->lastUpdate) / 1000.0;

    // Apply gravity if enabled
    if (physics->hasGravity) {
        physics->velocityY -= 9.81;
    }

    // Update the position based on the velocity
    *physics->positionXVar += physics->velocityX * deltaTime;
    *physics->positionYVar += physics->velocityY * deltaTime;

    // Reset onGround flag
    physics->onGround = false;

    // Update lastUpdate time
    physics->lastUpdate = now;
}