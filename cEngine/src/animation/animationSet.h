#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "./animation.h"

typedef struct AnimationSet {
    Animation** animations;
    int numAnimations;

    Animation** targetAnimationPointer;
} AnimationSet;

AnimationSet* createAnimationSet(int numAnimations, Animation** targetAnimationPointer, Animation** animations);
void destroyAnimationSet(AnimationSet* animationSet);

void addAnimationToAnimationSet(AnimationSet* animationSet, Animation* animation);
void selectAnimation(AnimationSet* animationSet, char* name);

#endif // ANIMATIONSET_H