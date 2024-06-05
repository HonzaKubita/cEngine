#ifndef COLLISIONSOLVER_H
#define COLLISIONSOLVER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../../object/engineObject.h"

void solveIfCollision(EngineObject* object1, EngineObject* object2);

#endif // COLLISIONSOLVER_H