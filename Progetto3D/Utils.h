#pragma once
#include "Strutture.h"
#include "Lib.h"
void InterpolazioneHermite(float* t, Mesh* Fig, vec4 color_top, vec4 color_bot);
BoundingBox calcolaBoundingBox(Mesh* fig);
BoundingBox calcolaBoundingBoxOBJ(vector<MeshObj> meshObj);
BoundingBox rotazioneBoundingBox(BoundingBox aabb);
bool checkCollisionCamera(vector<Mesh> Scena, vec4 cameraPosition);
void logger(string TAG, string text);
