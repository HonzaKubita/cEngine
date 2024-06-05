#include "engineObject.h"

EngineObject* createEngineObject(int positionX, int positionY) {
    // Allocate memory for the object
    EngineObject* object = malloc(sizeof(EngineObject));
    if (object == NULL) {
        fprintf(stderr, "Failed to allocate memory for the object\n");
        return NULL;
    }

    // Initialize the object

    // Set the object's position
    object->positionX = positionX;
    object->positionY = positionY;

    // Initialize the default values
    object->texture = NULL;
    object->animation = NULL;
    object->animationSet = NULL;
    object->physics = NULL;
    object->collisionBox = NULL;

    return object;
}

void destroyEngineObject(EngineObject* object) {
    // Check if the object is not NULL
    if (object == NULL) {
        return;
    }

    // Destroy the texture if it exists
    if (object->texture != NULL) {
        destroyTexture(object->texture);
    }

    // Destroy the animation if it exists
    if (object->animation != NULL) {
        destroyAnimation(object->animation);
    }

    // Destroy the animation set if it exists
    if (object->animationSet != NULL) {
        destroyAnimationSet(object->animationSet);
    }

    // Destroy the physics if it exists
    if (object->physics != NULL) {
        destroyPhysics(object->physics);
    }

    // Destroy the collision box if it exists
    if (object->collisionBox != NULL) {
        destroyCollisionBox(object->collisionBox);
    }

    // Free the memory allocated for the object
    free(object);
}

void updateEngineObject(EngineObject* object) {
    // Check if the object is not NULL
    if (object == NULL) {
        return;
    }

    // Call the object's controller if it has one
    if (object->controller != NULL) {
        object->controller(object);
    }

    // Update the object's position based on physics
    if (object->physics != NULL) {
        updatePhysics(object->physics);
    }

    // Update the object's animation if it has one
    if (object->animation != NULL) {
        updateAnimation(object->animation);
    }
}

// Helper functions

void addTextureToEngineObject(SDL_Renderer* renderer, EngineObject* object, char* path) {
    // Load the object's texture
    object->texture = createTexture(renderer, path);
    if (object->texture == NULL) {
        free(object->texture);
        fprintf(stderr, "Failed to load texture\n");
        return;
    }
}

void addAnimationToEngineObject(SDL_Renderer* renderer, EngineObject* object, char* name, char* pathAndPrefix, int numFrames, int frameDuration, bool looping, bool mustFinish) {    
    // Load the object's animation
    object->animation = loadAnimation(renderer, &object->texture, name, pathAndPrefix, numFrames, frameDuration, looping, mustFinish);
    if (object->animation == NULL) {
        free(object->animation);
        fprintf(stderr, "Failed to load animation\n");
        return;
    }
}

void addAnimationToEngineObjectAnimationSet(SDL_Renderer* renderer, EngineObject* object, char* name, char* pathAndPrefix, int numFrames, int frameDuration, bool looping, bool mustFinish) {    
    // Load the animation
    Animation* animation = loadAnimation(renderer, &object->texture, name, pathAndPrefix, numFrames, frameDuration, looping, mustFinish);
    if (animation == NULL) {
        free(animation);
        fprintf(stderr, "Failed to load animation\n");
        return;
    }

    // Add the animation to the animation set
    addAnimationToAnimationSet(object->animationSet, animation);
}