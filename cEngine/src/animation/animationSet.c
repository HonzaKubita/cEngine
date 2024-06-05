#include "animationSet.h"

AnimationSet* createAnimationSet(int numAnimations, Animation** targetAnimationPointer, Animation** animations) {
    // Allocate memory for an Animation struct
    AnimationSet* animationSet = malloc(sizeof(AnimationSet));
    if (animationSet == NULL) {
        fprintf(stderr, "Failed to allocate memory for the animation set\n");
        return NULL;
    }

    animationSet->animations = animations;
    animationSet->numAnimations = numAnimations;
    animationSet->targetAnimationPointer = targetAnimationPointer;

    return animationSet;
}

void destroyAnimationSet(AnimationSet* animationSet) {
    // Check if the animationSet is not NULL
    if (animationSet == NULL) {
        return;
    }

    // Free the memory allocated for the animations
    for (int i = 0; i < animationSet->numAnimations; i++) {
        destroyAnimation(animationSet->animations[i]);
    }

    // Free the memory allocated for the animations array
    free(animationSet->animations);

    // Free the memory allocated for the animationSet
    free(animationSet);
}

void addAnimationToAnimationSet(AnimationSet* animationSet, Animation* animation) {
    if (animationSet == NULL || animation == NULL) {
        return;
    }

    // Reallocate memory for the animations
    animationSet->animations = realloc(animationSet->animations, sizeof(Animation*) * (animationSet->numAnimations + 1));
    if (animationSet->animations == NULL) {
        fprintf(stderr, "Failed to reallocate memory for the animations\n");
        return;
    }

    // Add the animation to the array
    animationSet->animations[animationSet->numAnimations] = animation;
    animationSet->numAnimations++;
}

void selectAnimation(AnimationSet* animationSet, char* name) {
    if (animationSet == NULL) {
        return;
    }

    // Check if the current animation must finish and it's not finished
    if (
        (*animationSet->targetAnimationPointer) != NULL &&
        (*animationSet->targetAnimationPointer)->mustFinish && 
        (*animationSet->targetAnimationPointer)->currentFrame < (*animationSet->targetAnimationPointer)->numFrames - 1
    ) 
    {
        return;
    }

    // Find the animation with the name
    for (int i = 0; i < animationSet->numAnimations; i++) {
        if (strcmp(animationSet->animations[i]->name, name) == 0) {
            // Animation found
            
            if (*animationSet->targetAnimationPointer == animationSet->animations[i]) {
                // The animation is already selected
                return;
            }

            // Reset the animation
            animationSet->animations[i]->currentFrame = 0;

            // Update the target animation pointer
            *animationSet->targetAnimationPointer = animationSet->animations[i];
        }
    }
}