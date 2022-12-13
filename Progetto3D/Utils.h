#pragma once
#include "Strutture.h"
#include "Lib.h"
void InterpolazioneHermite(float* t, Mesh* Fig, vec4 color_top, vec4 color_bot);
BoundingBox calcolaBoundingBox(Mesh* fig);
BoundingBox calcolaBoundingBoxOBJ(vector<MeshObj> meshObj);
BoundingBox rotateBoundingBox(BoundingBox aabb);
BoundingBox resizeBoundingBox(BoundingBox aabb);
BoundingBox adjustBoundingBox(BoundingBox aabb);
bool checkCollisionCamera(vector<Mesh> Scena, vec4 cameraPosition);
void logger(string TAG, string text);
