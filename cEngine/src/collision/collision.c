#include "collision.h"

CollisionBox* createCollisionBox(int boxWidth, int boxHeight, int offsetX, int offsetY) {
    // Allocate memory for a CollisionBox struct
    CollisionBox* collisionBox = malloc(sizeof(CollisionBox));
    if (collisionBox == NULL) {
        fprintf(stderr, "Failed to allocate memory for the collision\n");
        return NULL;
    }

    // Initialize the CollisionBox struct
    collisionBox->boxWidth = boxWidth;
    collisionBox->boxHeight = boxHeight;
    collisionBox->offsetX = offsetX;
    collisionBox->offsetY = offsetY;

    return collisionBox;
}

void destroyCollisionBox(CollisionBox* collisionBox) {
    // Check if the collisionBox is not NULL
    if (collisionBox == NULL) {
        return;
    }

    // Free the memory allocated for the collisionBox
    free(collisionBox);
}