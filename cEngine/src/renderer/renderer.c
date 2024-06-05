#include "renderer.h"

#include <SDL.h>
#include <stdio.h>

// Function for initializing the renderer
Renderer* createRenderer() {
    // Allocate memory for the renderer
    Renderer* renderer = malloc(sizeof(Renderer));
    if (renderer == NULL) {
        fprintf(stderr, "Failed to allocate memory for the renderer\n");
        return NULL;
    }
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return NULL;
    }

    // Create a fullscreen window
    SDL_Window* SDLWindow = SDL_CreateWindow(CONFIG_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (SDLWindow == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }
    // Assign the window to the renderer
    renderer->SDLWindow = SDLWindow;
    // Get the width and height of the window
    SDL_GetWindowSize(SDLWindow, &renderer->width, &renderer->height);

    // Create a renderer
    SDL_Renderer* SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (SDLRenderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(SDLWindow);
        SDL_Quit();
        return NULL;
    }
    // Assign the SDL renderer to the renderer
    renderer->SDLRenderer = SDLRenderer;

    // Set the program's icon
    SDL_Surface* icon = IMG_Load("assets/icon.png");
    SDL_SetWindowIcon(renderer->SDLWindow, icon);

    return renderer;
}

void updateRenderer(Renderer* renderer) {
    // Check if the renderer is not NULL
    if (renderer == NULL) {
        return;
    }

    // Update the screen
    SDL_RenderPresent(renderer->SDLRenderer);
}

void clearRenderer(Renderer* renderer) {
    // Check if the renderer is not NULL
    if (renderer == NULL) {
        return;
    }

    // Clear the screen
    SDL_RenderClear(renderer->SDLRenderer);
}

// Function for destroying the renderer
void destroyRenderer(Renderer* renderer) {
    // Check if the renderer is not NULL
    if (renderer == NULL) {
        return;
    }

    // Destroy the renderer and window
    SDL_DestroyRenderer(renderer->SDLRenderer);
    SDL_DestroyWindow(renderer->SDLWindow);
    // Quit SDL
    SDL_Quit();
    // Free the memory allocated for the renderer
    free(renderer);
}

void renderEngineObject(Renderer* renderer, EngineObject* object) {
    // Check if the renderer and object are not NULL
    if (renderer == NULL || object == NULL) {
        return;
    }

    // Check if object has a texture
    if (object->texture == NULL) {
        return;
    }

    // Translate the object's Y position to match the renderer's coordinate system
    int translatedY = renderer->height - object->positionY - object->texture->height;

    // Set the position and dimensions of the object
    SDL_Rect destRect = {object->positionX, translatedY, object->texture->width, object->texture->height};
    // Render the object's texture
    SDL_RenderCopy(renderer->SDLRenderer, object->texture->texture, NULL, &destRect);
}