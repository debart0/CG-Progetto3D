#pragma once
//MATERIALI DI BASE
#include "Lib.h"
glm::vec3 red_plastic_ambient = { 0.1, 0.0, 0.0 }, red_plastic_diffuse = { 0.6, 0.1, 0.1 }, red_plastic_specular = { 0.7, 0.6, 0.6 }; GLfloat red_plastic_shininess = 150.0f;
glm::vec3 brass_ambient = { 0.5, 0.06, 0.015 }, brass_diffuse = { 0.78, 0.57, 0.11 }, brass_specular = { 0.99, 0.91, 0.81 }; GLfloat brass_shininess = 27.8f;
glm::vec3 verde_ambient = { 0.53, 0.75, 0.48 }, verde_diffuse = { 0.18, 0.42, 0.12 }, verde_specular = { 0.633, 0.727811, 0.633 }; GLfloat verde_shininess = 45.8f;
glm::vec3 snow_white_ambient = { 0.2, 0.2, 0.2 }, snow_white_diffuse = { 0.95, 0.96, 0.98 }, snow_white_specular{ 0.8, 0.8, 0.8 }; GLfloat snow_white_shininess = 1.78125f;
glm::vec3 yellow_ambient = { 0.8,	0.8,	0.0 }, yellow_diffuse = { 1.0,1.0,0.6 }, yellow_specular{ 0.9,	0.9	,0.04 }; GLfloat yellow_shininess = 1.78125f;
glm::vec3 rosa_ambient = { 0.05f,0.0f,0.0f }, rosa_diffuse = { 0.5f,0.4f,0.4f }, rosa_specular{ 0.7f,0.04f,0.04f }; GLfloat rosa_shininess = 1.78125f;
glm::vec3 marrone_ambient = { 0.19125f, 0.0735f, 0.0225f }, marrone_diffuse = { 0.23, 0.16, 0.08 }, marrone_specular{ 0.256777f, 0.137622f, 0.086014f }; GLfloat marrone_shininess = 12.8f;
glm::vec3 terra_ambient = { 0.58f, 0.47f, 0.38f }, terra_diffuse = { 0.43f, 0.34f, 0.28f, }, terra_specular = { 0.256777f, 0.137622f, 0.086014f }; GLfloat terra_shininess = 2.8f;