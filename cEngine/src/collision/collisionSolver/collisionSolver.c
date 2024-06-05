#include "collisionSolver.h"

void _solveOverlapCollision(EngineObject* object1, EngineObject* object2) {
    // Check if the objects are not NULL
    if (object1 == NULL || object2 == NULL) {
        return;
    }

    // Check if the objects have collision components
    if (!(object1->collisionBox != NULL) || !(object2->collisionBox != NULL)) {
        return;
    }

    // Check if at least one of the objects has a physics component
    if (!(object1->physics != NULL) && !(object2->physics != NULL)) {
        return;
    }

    // Get the collision components of the objects
    CollisionBox* collisionBox1 = object1->collisionBox;
    CollisionBox* collisionBox2 = object2->collisionBox;

    // Calculate the absolute positions of the collision boxes in the world
    int collisionBox1X = object1->positionX + collisionBox1->offsetX;
    int collisionBox1Y = object1->positionY + collisionBox1->offsetY;

    int collisionBox2X = object2->positionX + collisionBox2->offsetX;
    int collisionBox2Y = object2->positionY + collisionBox2->offsetY;

    // Check if the objects are colliding
    if (
        collisionBox1X < collisionBox2X + collisionBox2->boxWidth &&
        collisionBox1X + collisionBox1->boxWidth > collisionBox2X &&
        collisionBox1Y < collisionBox2Y + collisionBox2->boxHeight &&
        collisionBox1Y + collisionBox1->boxHeight > collisionBox2Y
    ) {
        // The objects are colliding
        // printf("Collision detected\n");

        // Resolve the collision

        // Determine the object to be moved
        EngineObject* objectToMove = NULL;
        // Following code is written with the assumption that we are gonna move object1
        // We need to invert the values if we are gonna move object2
        int inverter = 1;

        if (object1->physics != NULL) {
            objectToMove = object1;
        }
        else {
            objectToMove = object2;
            inverter = -1;
        }

        // Calculate possible move distances
        int distanceX1 = collisionBox2X + collisionBox2->boxWidth - collisionBox1X;
        int distanceX2 = collisionBox1X + collisionBox1->boxWidth - collisionBox2X;
        int distanceY1 = collisionBox2Y + collisionBox2->boxHeight - collisionBox1Y;
        int distanceY2 = collisionBox1Y + collisionBox1->boxHeight - collisionBox2Y;

        // Find the smallest move distance
        int smallestMove = distanceX1;
        if (distanceX2 < smallestMove) {
            smallestMove = distanceX2;
        }
        if (distanceY1 < smallestMove) {
            smallestMove = distanceY1;
        }
        if (distanceY2 < smallestMove) {
            smallestMove = distanceY2;
        }

        // Move the object
        if (smallestMove == distanceX1) {
            // Move the object to the left
            objectToMove->positionX += distanceX1 * inverter;
            // Reset velocity
            objectToMove->physics->velocityX = 0;
        } 
        else if (smallestMove == distanceX2) {
            // Move the object to the right
            objectToMove->positionX -= distanceX2 * inverter;
            // Reset velocity
            objectToMove->physics->velocityX = 0;
        } 
        else if (smallestMove == distanceY1) {
            // Move the object up
            objectToMove->positionY += distanceY1 * inverter;
            // Reset velocity
            objectToMove->physics->velocityY = 0;
            // Set the onGround flag
            objectToMove->physics->onGround = true;
        } 
        else if (smallestMove == distanceY2) {
            // Move the object down
            objectToMove->positionY -= distanceY2 * inverter; 
            // Reset velocity
            objectToMove->physics->velocityY = 0;
        }
    }
}

void _solveVelocityCollision(EngineObject* object1, EngineObject* object2) {
    
}

void solveIfCollision(EngineObject* object1, EngineObject* object2) {
    // Check if the objects are not NULL
    if (object1 == NULL || object2 == NULL) {
        return;
    }

    // Check if the objects have collision components
    if (!(object1->collisionBox != NULL) || !(object2->collisionBox != NULL)) {
        return;
    }

    // Check that the objects aren't the same
    if (object1 == object2) {
        return;
    }

    _solveOverlapCollision(object1, object2);
    _solveVelocityCollision(object1, object2);
}