#include "world.h"

World* createWorld() {
    // Allocate memory for the game
    World* game = malloc(sizeof(World));
    if (game == NULL) {
        fprintf(stderr, "Failed to allocate memory for the game\n");
        return NULL;
    }

    game->objects = malloc(sizeof(EngineObject*));
    if (game->objects == NULL) {
        free(game);
        fprintf(stderr, "Failed to allocate memory for the game objects\n");
        return NULL;
    }

    return game;
}

void destroyWorld(World* game) {
    if (game == NULL) {
        return;
    }

    if (game->objects != NULL) {
        free(game->objects);
    }

    free(game);
}

void addEngineObjectToWorld(World* game, EngineObject* gameObject) {
    // Check if the game and game object are not NULL
    if (game == NULL || gameObject == NULL) {
        return;
    }

    // Reallocate memory for the game objects
    game->objects = realloc(game->objects, sizeof(EngineObject*) * (game->numObjects + 1));
    if (game->objects == NULL) {
        fprintf(stderr, "Failed to reallocate memory for the game objects\n");
        return;
    }

    // Add the game object to the array
    game->objects[game->numObjects] = gameObject;
    game->numObjects++;
}

void removeEngineObjectFromWorld(World* game, EngineObject* gameObject) {
    // Check if the game and game object are not NULL
    if (game == NULL || gameObject == NULL) {
        return;
    }

    // Find the game object in the array
    int index = -1;
    for (int i = 0; i < game->numObjects; i++) {
        if (game->objects[i] == gameObject) {
            index = i;
            break;
        }
    }

    // Check if the game object was found
    if (index == -1) {
        return;
    }


    // Remove the game object from the array by shifting the elements
    for (int i = index; i < game->numObjects - 1; i++) {
        game->objects[i] = game->objects[i + 1];
    }

    game->numObjects--;

    // Reallocate memory for the game objects
    game->objects = realloc(game->objects, sizeof(EngineObject*) * game->numObjects);
    if (game->objects == NULL && game->numObjects > 0) {
        fprintf(stderr, "Failed to reallocate memory for the game objects\n");
        return;
    }

    // Free the memory of the game object
    free(gameObject);
}

void updateWorld(World* game) {
    // Check if the game is not NULL
    if (game == NULL) {
        return;
    }

    // Update each game object
    for (int i = 0; i < game->numObjects; i++) {
        updateEngineObject(game->objects[i]);
    }

    // Resolve collisions
    for (int i = 0; i < game->numObjects; i++) {
        for (int j = i + 1; j < game->numObjects; j++) {
            solveIfCollision(game->objects[i], game->objects[j]);
        }
    }
}