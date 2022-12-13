#pragma once
#include "materiali_base.h"
#include "Strutture.h"
#include "enum.h"
extern int selected_obj;
extern  vector<Mesh> Scena;
extern vector<Material> materials;
extern  vector<Shader> shaders;

void main_menu_func(int option)
{
	switch (option)
	{
	case MenuOption::WIRE_FRAME: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		printf("Polygon mode\n");
		break;
	case MenuOption::FACE_FILL: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;


	default:
		break;
	}
}
void material_menu_function(int option)
{
	if (selected_obj > -1)
		Scena[selected_obj].material = (MaterialType)option;
}

void shader_menu_function(int option) {
	if (selected_obj > -1) {
		Scena[selected_obj].sceltaVS = shaders[option].value;
		if (shaders[option].value == 3 || shaders[option].value == 4) {
			Scena[selected_obj].sceltaFS = 3;
		}
		else if(shaders[option].value == 0) {
			Scena[selected_obj].sceltaFS = 5;
		}
		else {
			Scena[selected_obj].sceltaFS = 1;
		}
	}
}
void buildOpenGLMenu()
{
	int materialSubMenu = glutCreateMenu(material_menu_function);

	glutAddMenuEntry(materials[MaterialType::RED_PLASTIC].name.c_str(), MaterialType::RED_PLASTIC);
	glutAddMenuEntry(materials[MaterialType::VERDE].name.c_str(), MaterialType::VERDE);
	glutAddMenuEntry(materials[MaterialType::BRASS].name.c_str(), MaterialType::BRASS);
	glutAddMenuEntry(materials[MaterialType::SNOW_WHITE].name.c_str(), MaterialType::SNOW_WHITE);
	glutAddMenuEntry(materials[MaterialType::YELLOW].name.c_str(), MaterialType::YELLOW);
	glutAddMenuEntry(materials[MaterialType::ROSA].name.c_str(), MaterialType::ROSA);
	glutAddMenuEntry(materials[MaterialType::MARRONE].name.c_str(), MaterialType::MARRONE);
	glutAddMenuEntry(materials[MaterialType::TERRA].name.c_str(), MaterialType::TERRA);
	glutAddMenuEntry(materials[MaterialType::NO_MATERIAL].name.c_str(), MaterialType::NO_MATERIAL);

	int shaderSubMenu = glutCreateMenu(shader_menu_function);
	glutAddMenuEntry(shaders[ShaderOption::NONE].name.c_str(), ShaderOption::NONE);
	glutAddMenuEntry(shaders[ShaderOption::PHONG_INTERPL_SHADING].name.c_str(), ShaderOption::PHONG_INTERPL_SHADING);
	glutAddMenuEntry(shaders[ShaderOption::BLINN_PHONG_INTERPL_SHADING].name.c_str(), ShaderOption::BLINN_PHONG_INTERPL_SHADING);
	glutAddMenuEntry(shaders[ShaderOption::PHONG_PHONG_SHADING].name.c_str(), ShaderOption::PHONG_PHONG_SHADING);
	glutAddMenuEntry(shaders[ShaderOption::BLINN_PHONG_PHONG_SHADING].name.c_str(), ShaderOption::BLINN_PHONG_PHONG_SHADING);
	glutAddMenuEntry(shaders[ShaderOption::TOON_SHADING].name.c_str(), ShaderOption::TOON_SHADING);


	glutCreateMenu(main_menu_func); // richiama main_menu_func() alla selezione di una voce menu
	glutAddMenuEntry("Opzioni", -1); //-1 significa che non si vuole gestire questa riga
	glutAddMenuEntry("", -1);
	glutAddMenuEntry("Wireframe", MenuOption::WIRE_FRAME);
	glutAddMenuEntry("Face fill", MenuOption::FACE_FILL);
	glutAddSubMenu("Material", materialSubMenu);
	glutAddSubMenu("Shader", shaderSubMenu);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}