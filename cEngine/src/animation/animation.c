#include "animation.h"

Animation* createAnimation(char* name, int numFrames, int frameDuration, bool isLooping, bool mustFinish, Texture** targetTexturePointer, Texture** frames) {
    // Allocate memory for an Animation struct
    Animation* animation = malloc(sizeof(Animation));
    if (animation == NULL) {
        fprintf(stderr, "Failed to allocate memory for the animation\n");
        return NULL;
    }

    // Initialize the Animation struct
    animation->name = name;
    animation->numFrames = numFrames;
    animation->currentFrame = 0;
    animation->frameDuration = frameDuration;
    animation->isLooping = isLooping;
    animation->mustFinish = mustFinish;
    animation->frames = frames;
    animation->targetTexturePointer = targetTexturePointer;
    animation->_currentFrameStart = clock();

    return animation;
}

void destroyAnimation(Animation* animation) {
    // Check if the animation is not NULL
    if (animation == NULL) {
        return;
    }

    // Free the memory allocated for the frames
    for (int i = 0; i < animation->numFrames; i++) {
        destroyTexture(animation->frames[i]);
    }
    free(animation->frames);

    // Free the memory allocated for the animation
    free(animation);
}

void updateAnimation(Animation* animation) {
    // Check if the animation is not NULL
    if (animation == NULL) {
        return;
    }

    // Calculate the elapsed time since the last frame change
    Uint32 currentTime = SDL_GetTicks();
    float elapsedTimeMs = (float)(currentTime - animation->_currentFrameStart);

    // Check if it's time to change to the next frame
    if (elapsedTimeMs >= animation->frameDuration) {
        // Update the current frame
        animation->currentFrame++;
        if (animation->currentFrame >= animation->numFrames) {
            // Reset the animation if it's looping
            if (animation->isLooping) {
                animation->currentFrame = 0;
            } else {
                // Stop the animation if it's not looping
                animation->currentFrame = animation->numFrames - 1;
            }
        }

        // printf("Updating target texture with frame: %d\n", animation->currentFrame);

        // Update the target texture with the new frame
        *animation->targetTexturePointer = animation->frames[animation->currentFrame];

        // Update the current frame start time
        animation->_currentFrameStart = currentTime;
    }
}

Animation* loadAnimation(SDL_Renderer* renderer, Texture** targetTexturePointer, char* name, char* pathAndPrefix, int numFrames, int frameDuration, bool looping, bool mustFinish) {
    // Allocate the memory for the frames
    Texture** textures = malloc(sizeof(Texture) * numFrames);

    for (int i = 0; i < numFrames; i++) {
        // Convert i to string and append it to pathAndPrefix
        char framePath[200];
        sprintf(framePath, "%s%d.png", pathAndPrefix, i);
        textures[i] = createTexture(renderer, framePath);
    }
    
    Animation* animation = createAnimation(name, numFrames, frameDuration, looping, mustFinish, targetTexturePointer, textures);

    return animation;
}