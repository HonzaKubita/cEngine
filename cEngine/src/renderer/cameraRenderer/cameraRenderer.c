#include "cameraRenderer.h"

CameraRenderer* createCameraRenderer() {
    // Allocate memory for the camera renderer
    CameraRenderer* renderer = malloc(sizeof(CameraRenderer));
    if (renderer == NULL) {
        fprintf(stderr, "Failed to allocate memory for the camera renderer\n");
        return NULL;
    }

    // Create a renderer
    renderer->renderer = createRenderer();
    if (renderer->renderer == NULL) {
        free(renderer);
        fprintf(stderr, "Failed to create the renderer for camera renderer\n");
        return NULL;
    }

    renderer->positionX = 0;
    renderer->positionY = 0;
    renderer->scale = 1;

    return renderer;
}

void updateCameraRenderer(CameraRenderer* renderer) {
    // Check if the renderer is not NULL
    if (renderer == NULL) {
        return;
    }

    updateRenderer(renderer->renderer);
}

void clearCameraRenderer(CameraRenderer* renderer) {
    // Check if the renderer is not NULL
    if (renderer == NULL) {
        return;
    }

    clearRenderer(renderer->renderer);
}

// Function for destroying the renderer
void destroyCameraRenderer(CameraRenderer* renderer) {
    // Check if the renderer is not NULL
    if (renderer == NULL) {
        return;
    }

    destroyRenderer(renderer->renderer);
}

void smoothMoveCameraTo(CameraRenderer* renderer, int positionX, int positionY) {
    // Check if the renderer is not NULL
    if (renderer == NULL) {
        return;
    }

    const float smoothFactor = 0.03;

    // Smooth the camera movement
    int smoothedX = (positionX * smoothFactor) + (renderer->positionX * (1 - smoothFactor));
    int smoothedY = (positionY * smoothFactor) + (renderer->positionY * (1 - smoothFactor));

    // Update the position of the camera
    renderer->positionX = smoothedX;
    renderer->positionY = smoothedY;

    // Update the camera scale based on the change in position (zoom out when moving fast)
    double newScale = 1 - (abs(positionX - renderer->positionX) + abs(positionY - renderer->positionY)) * 0.001;
    // Clamp the scale to a minimum of 0.2
    if (newScale < 0.2) {
        newScale = 0.2;
    }
    // Clamp the scale to a maximum of 0.8
    if (newScale > 0.8) {
        newScale = 0.8;
    }
    renderer->scale = newScale;
}

void cameraRenderEngineObject(CameraRenderer* renderer, EngineObject* object) {
    // Check if the renderer and object are not NULL
    if (renderer == NULL || object == NULL) {
        return;
    }

    // Check if object has a texture
    if (object->texture == NULL) {
        return;
    }

    int finalX = (object->positionX - (renderer->positionX - (renderer->renderer->width * (1 / renderer->scale)) / 2)) * renderer->scale;
    int finalY = (object->positionY - (renderer->positionY - (renderer->renderer->height * (1 / renderer->scale)) / 2)) * renderer->scale;

    // Translate the object's Y position to match the renderer's coordinate system
    int translatedY = renderer->renderer->height - finalY - (object->texture->height * renderer->scale);

    // Set the position and dimensions of the object
    SDL_Rect destRect;
    destRect.x = finalX; 
    destRect.y = translatedY;
    destRect.w = object->texture->width * renderer->scale;
    destRect.h = object->texture->height * renderer->scale;
    // Render the object's texture
    SDL_RenderCopyEx(renderer->renderer->SDLRenderer, object->texture->texture, NULL, &destRect, object->angle, NULL, object->flip);
}