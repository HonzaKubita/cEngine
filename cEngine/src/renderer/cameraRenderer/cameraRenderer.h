#ifndef CAMERARENDERER_H
#define CAMERARENDERER_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "../../config.h"
#include "../renderer.h"
#include "../../object/engineObject.h"

typedef struct CameraRenderer {
    Renderer* renderer;
    int positionX;
    int positionY;
    double scale;
} CameraRenderer;

CameraRenderer* createCameraRenderer();
void destroyCameraRenderer(CameraRenderer* renderer);

void updateCameraRenderer(CameraRenderer* renderer);
void clearCameraRenderer(CameraRenderer* renderer);

void smoothMoveCameraTo(CameraRenderer* renderer, int positionX, int positionY);

void cameraRenderEngineObject(CameraRenderer* renderer, EngineObject* object);

#endif // RENDERER_H