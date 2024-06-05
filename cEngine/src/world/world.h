#ifndef WORLD_H
#define WORLD_H

#include <stdlib.h>
#include <stdio.h>

#include "../object/engineObject.h"
#include "../collision/collisionSolver/collisionSolver.h"

typedef struct World {
    EngineObject** objects;
    int numObjects;
} World;

World* createWorld();
void destroyWorld(World* game);

void addEngineObjectToWorld(World* game, EngineObject* gameObject);
void removeEngineObjectFromWorld(World* game, EngineObject* gameObject);

void updateWorld(World* game);

#endif // WORLD_H