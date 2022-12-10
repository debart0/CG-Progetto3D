#pragma once
#include "Strutture.h"
void InterpolazioneHermite(float* t, Mesh* Fig, vec4 color_top, vec4 color_bot);
BoundingBox calcolaBoundingBox(Mesh* fig);
bool checkCollisionCamera(Mesh mesh, vec4 cameraPosition);
