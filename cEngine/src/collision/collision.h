#ifndef COLLISION_H
#define COLLISION_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct CollisionBox {
    int boxWidth;
    int boxHeight;
    int offsetX;
    int offsetY;
} CollisionBox;

CollisionBox* createCollisionBox(int boxWidth, int boxHeight, int boxX, int boxY);
void destroyCollisionBox(CollisionBox* collisionBox);

#endif // COLLISION_H