#include "texture.h"

Texture* createTexture(SDL_Renderer* renderer, const char* path) {
    // Allocate memory for the texture struct
    Texture* texture = malloc(sizeof(Texture));
    if (texture == NULL) {
        fprintf(stderr, "Failed to allocate memory for the texture\n");
        return NULL;
    }

    // Using IMG_LoadTexture to load the texture
    SDL_Texture* SDLTexture = IMG_LoadTexture(renderer, path);
    if (SDLTexture == NULL) {
        free(texture);
        fprintf(stderr, "Failed to load texture: %s\n", path);
        return NULL;
    }

    // Assign the texture to the struct
    texture->texture = SDLTexture;

    texture->width = 0;
    texture->height = 0;

    // Get the width and height of the texture and assign it to the struct
    SDL_QueryTexture(SDLTexture, NULL, NULL, &texture->width, &texture->height);

    return texture;
}

void destroyTexture(Texture* texture) {
    // Check if the texture is not NULL
    if (texture == NULL) {
        return;
    }

    // Destroy the texture
    SDL_DestroyTexture(texture->texture);

    // Free the memory allocated for the texture
    free(texture);
}