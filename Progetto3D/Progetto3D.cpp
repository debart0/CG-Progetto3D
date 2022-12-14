#include <iostream>

#include "ShaderMaker.h"
#include "Lib.h"
#include "geometria.h"
#include "gestioneTexture.h"
#include "gestione_menu.h"
#include "materiali_base.h"
#include "load_meshes_assimp.hpp"
#include "gestione_mouse.h"
#include "gestione_telecamera.h"
#include "Strutture.h"
#include "enum.h"
#include "Utils.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

 
string Meshdir = "Meshes/";
string Imagedir = "Textures/";
string SkyboxDir = "Skybox/";

bool visualizzaAncora =FALSE;
int width = 1024;
int height = 800;

//Gestione Mouse

static int last_mouse_pos_Y;
static int last_mouse_pos_X;
static bool moving_trackball = 0;
bool firstMouse = true;
float lastX = (float)width / 2;
float lastY = (float)height / 2;

 float angolo = 0.0;
//Varibili per il reshape
int w_up = width;
int h_up = height;
 
//Inizializzazione dei modelli 
static vector<MeshObj> Model3D;
vector<BoundingBox> BoundingBoxOBJVector;
vector<vector<MeshObj>> ScenaObj;
 string stringa_asse;
float cameraSpeed = 0.1;

//variabili per la comunicazione delle variabili uniformi con gli shader
static unsigned int programId, programId_text, programId1, MatrixProj, MatModel, MatView;
static unsigned int lsceltaFS, lsceltaVS,loc_texture, MatViewS, MatrixProjS;
static unsigned int loc_view_pos, MatModelR, MatViewR, MatrixProjR, loc_view_posR, loc_cubemapR;

 

unsigned int idTex, cubemapTexture, texturePiano, textureTronco, textureFoglie, textureLegno, textureRockyTrail, programIdr;

float raggio_sfera=4;

string Operazione;
vec3 asse = vec3(0.0, 1.0, 0.0);
int selected_obj = 0;
int pval = 140;

float Theta = -90.0f;
float Phi = 0.0f;
static vec4 defaultCameraPosition = glm::vec4(50.0, 20.0, 50.0, 0.0);

vector<std::string> skyBoxFaces
{
	/*"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"*/
	SkyboxDir+"posx.jpg",
	SkyboxDir+"negx.jpg",
	SkyboxDir + "posy.jpg",
	SkyboxDir + "negy.jpg",
	SkyboxDir + "posz.jpg",
	SkyboxDir + "negz.jpg"
};

vector<std::string> rockwallFaces
{
	Imagedir + "rock_wall_diff_1k.jpg",
	Imagedir + "rock_wall_diff_1k.jpg",
	Imagedir + "rock_wall_diff_1k.jpg",
	Imagedir + "rock_wall_diff_1k.jpg",
	Imagedir + "rock_wall_diff_1k.jpg",
	Imagedir + "rock_wall_diff_1k.jpg"
};


// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
//

mat4 Projection, Model, View;

point_light light;
static vector<Material> materials;
static vector<Shader> shaders;
vec4 verde = vec4(0.09, 0.20, 0.05, 1.0);
vec4 marrone = vec4(0.28, 0.15, 0.09, 1.0);


LightShaderUniform light_unif = {};

void INIT_SHADER(void)

{
	GLenum ErrorCheckValue = glGetError();

	char* vertexShader = (char*)"vertexShader_C.glsl";
	char* fragmentShader = (char*)"fragmentShader_C.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);

	 
	 
	vertexShader = (char*)"vertexShader_CubeMap.glsl";
	fragmentShader = (char*)"fragmentShader_CubeMap.glsl";

	programId1 = ShaderMaker::createProgram(vertexShader, fragmentShader);

	vertexShader = (char*)"vertexShader_riflessione.glsl";
	fragmentShader = (char*)"fragmentShader_riflessione.glsl";

	programIdr = ShaderMaker::createProgram(vertexShader, fragmentShader);
}

 
void INIT_Illuminazione()
{
	//Setup della luce
	light.position = { -7.0, 17.0, 12.0 };
	light.color = { 1.0,1.0,1.0 };
	light.power = 2.f;

	//Setup dei materiali
	// Materials setup
	materials.resize(9);
	materials[MaterialType::RED_PLASTIC].name = "Red Plastic";
	materials[MaterialType::RED_PLASTIC].ambient = red_plastic_ambient;
	materials[MaterialType::RED_PLASTIC].diffuse = red_plastic_diffuse;
	materials[MaterialType::RED_PLASTIC].specular = red_plastic_specular;
	materials[MaterialType::RED_PLASTIC].shininess = red_plastic_shininess;

	materials[MaterialType::VERDE].name = "VERDE";
	materials[MaterialType::VERDE].ambient = verde_ambient;
	materials[MaterialType::VERDE].diffuse = verde_diffuse;
	materials[MaterialType::VERDE].specular = verde_specular;
	materials[MaterialType::VERDE].shininess = verde_shininess;

	materials[MaterialType::BRASS].name = "Brass";
	materials[MaterialType::BRASS].ambient = brass_ambient;
	materials[MaterialType::BRASS].diffuse = brass_diffuse;
	materials[MaterialType::BRASS].specular = brass_specular;
	materials[MaterialType::BRASS].shininess = brass_shininess;

	materials[MaterialType::SNOW_WHITE].name = "Snow_White";
	materials[MaterialType::SNOW_WHITE].ambient = snow_white_ambient;
	materials[MaterialType::SNOW_WHITE].diffuse = snow_white_diffuse;
	materials[MaterialType::SNOW_WHITE].specular = snow_white_specular;
	materials[MaterialType::SNOW_WHITE].shininess = snow_white_shininess;

	materials[MaterialType::YELLOW].name = "Yellow";
	materials[MaterialType::YELLOW].ambient = yellow_ambient;
	materials[MaterialType::YELLOW].diffuse = yellow_diffuse;
	materials[MaterialType::YELLOW].specular = yellow_specular;
	materials[MaterialType::YELLOW].shininess = yellow_shininess;

	materials[MaterialType::ROSA].name = "ROSA";
	materials[MaterialType::ROSA].ambient = rosa_ambient;
	materials[MaterialType::ROSA].diffuse = rosa_diffuse;
	materials[MaterialType::ROSA].specular = rosa_specular;
	materials[MaterialType::ROSA].shininess = rosa_shininess;

	materials[MaterialType::MARRONE].name = "MARRONE";
	materials[MaterialType::MARRONE].ambient = marrone_ambient;
	materials[MaterialType::MARRONE].diffuse = marrone_diffuse;
	materials[MaterialType::MARRONE].specular = marrone_specular;
	materials[MaterialType::MARRONE].shininess = marrone_shininess;

	materials[MaterialType::TERRA].name = "TERRA";
	materials[MaterialType::TERRA].ambient = terra_ambient;
	materials[MaterialType::TERRA].diffuse = terra_diffuse;
	materials[MaterialType::TERRA].specular = terra_specular;
	materials[MaterialType::TERRA].shininess = terra_shininess;

	materials[MaterialType::NO_MATERIAL].name = "NO_MATERIAL";
	materials[MaterialType::NO_MATERIAL].ambient = glm::vec3(1, 1, 1);
	materials[MaterialType::NO_MATERIAL].diffuse = glm::vec3(0, 0, 0);
	materials[MaterialType::NO_MATERIAL].specular = glm::vec3(0, 0, 0);
	materials[MaterialType::NO_MATERIAL].shininess = 1.f;

	//Setup degli shader
	shaders.resize(6);
	shaders[ShaderOption::NONE].value = 0;
	shaders[ShaderOption::NONE].name = "NONE";
	shaders[ShaderOption::PHONG_INTERPL_SHADING].value = 1;
	shaders[ShaderOption::PHONG_INTERPL_SHADING].name = "PHONG + INTERPL";
	shaders[ShaderOption::BLINN_PHONG_INTERPL_SHADING].value = 2;
	shaders[ShaderOption::BLINN_PHONG_INTERPL_SHADING].name = "BLINN-PHONG + INTERPL";
	shaders[ShaderOption::PHONG_PHONG_SHADING].value = 3;
	shaders[ShaderOption::PHONG_PHONG_SHADING].name = "PHONG + PHONG";
	shaders[ShaderOption::BLINN_PHONG_PHONG_SHADING].value = 4;
	shaders[ShaderOption::BLINN_PHONG_PHONG_SHADING].name = "BLINN-PHONG + PHONG";
	shaders[ShaderOption::TOON_SHADING].value = 5;
	shaders[ShaderOption::TOON_SHADING].name = "TOON SHADING";

}

void crea_VAO_Vector_MeshObj(MeshObj* mesh)
{

	glGenVertexArrays(1, &mesh->VAO);
	glBindVertexArray(mesh->VAO);
	//Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &mesh->VBO_G);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_G);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertici.size() * sizeof(vec3), mesh->vertici.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Genero , rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &mesh->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, mesh->colori.size() * sizeof(vec4), mesh->colori.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	//Genero , rendo attivo, riempio il VBO delle normali
	glGenBuffers(1, &mesh->VBO_normali);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_normali);
	glBufferData(GL_ARRAY_BUFFER, mesh->normali.size() * sizeof(vec3), mesh->normali.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO delle NORMALI nel layer 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);



	//EBO di tipo indici
	glGenBuffers(1, &mesh->EBO_indici);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO_indici);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indici.size() * sizeof(GLuint), mesh->indici.data(), GL_STATIC_DRAW);


}


void crea_VAO_Vector(Mesh* mesh)
{

	glGenVertexArrays(1, &mesh->VAO);
	glBindVertexArray(mesh->VAO);
	//Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &mesh->VBO_G);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_G);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertici.size() * sizeof(vec3), mesh->vertici.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Genero , rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &mesh->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, mesh->colori.size() * sizeof(vec4), mesh->colori.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	//Genero , rendo attivo, riempio il VBO delle normali
	glGenBuffers(1, &mesh->VBO_normali);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_normali);
	glBufferData(GL_ARRAY_BUFFER, mesh->normali.size() * sizeof(vec3), mesh->normali.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO delle NORMALI nel layer 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &mesh->VBO_coord_texture);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_coord_texture);
	glBufferData(GL_ARRAY_BUFFER, mesh->texCoords.size() * sizeof(vec2), mesh->texCoords.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO delle NORMALI nel layer 2
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(3);

	//EBO di tipo indici
	glGenBuffers(1, &mesh->EBO_indici);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO_indici);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indici.size() * sizeof(GLuint), mesh->indici.data(), GL_STATIC_DRAW);


}


void collegaMesh() {
	printf("\nCollegamesh\n");
	printf("Dimensione Scena %d\n", Scena.size());
	Scena[3].linkedMesh = &Scena[4];
	Scena[4].linkedMesh = &Scena[3];

	Scena[5].linkedMesh = &Scena[6];
	Scena[6].linkedMesh = &Scena[5];

	Scena[7].linkedMesh = &Scena[8];
	Scena[8].linkedMesh = &Scena[7];

	//printf("%s linked: %s\n", Scena[3].nome.c_str(), Scena[3].linkedMesh->nome.c_str());
	//printf("%s linked: %s\n", Scena[4].nome.c_str(), Scena[4].linkedMesh->nome.c_str());
}

void INIT_VAO(void)
{
	string TAG = "INIT_VAO";
	Mesh Strada, Sfondo, Sfera, Cono, Cilindro, Toro, Sky, Piano, Sfera1, Sfera2;
	Mesh Tronco, Foglie, Tronco2, Foglie2, Tronco3, Foglie3;
	Mesh Muretto, Gamba1, Gamba2, Gamba3, Gamba4, Gamba5;
	Mesh Muretto2, Muretto3, Gamba6, Gamba7, Gamba8, Gamba9, Gamba10;
	//vector<Mesh> Muretto;
	caricaTexture();
	//Sky
	crea_cubo(&Sky, vec2(10.0, 10.0));
	crea_VAO_Vector(&Sky);
	Scena.push_back(Sky);

	//Piano che fa da prato
	crea_piano(&Piano, vec4(1.0, 0.0, 0.0, 1.0), vec2(10.0, 10.0));
	crea_VAO_Vector(&Piano);
	Piano.nome = "Terreno";
	Piano.BBOriginale = calcolaBoundingBox(&Piano);
	Piano.ModelM = mat4(1.0);
	Piano.ModelM = translate(Piano.ModelM, vec3(0.0, -10.0, 0.0));
	Piano.ModelM = scale(Piano.ModelM, vec3(60.0f, 1.0f, 60.0f));
	//Piano.ModelM = rotate(Piano.ModelM, radians(-90.0f), vec3(0.0, 1.0, 0.0));
	Piano.sceltaVS = 1;
	Piano.sceltaFS = 1;
	Piano.AABB = Piano.BBOriginale;
	Piano.AABB.TL = Piano.ModelM * Piano.AABB.TL;
	Piano.AABB.BR = Piano.ModelM * Piano.AABB.BR;
	Piano.AABB = adjustBoundingBox(Piano.AABB);
	Piano.material = MaterialType::VERDE;
	Piano.texture = TextureType::ERBA;
	Piano.alive = true;
	Piano.killable = false;
	Scena.push_back(Piano);

	//STRADINA
	crea_piano(&Strada, vec4(0.2, 0.2, 0.9, 1.0), vec2(1.0, 12.5));
	crea_VAO_Vector(&Strada);
	Strada.nome = "STRADA";
	Strada.ModelM = mat4(1.0);
	Strada.ModelM = translate(Strada.ModelM, vec3(0.0, -9.9, 0.0));
	Strada.ModelM = scale(Strada.ModelM, vec3(5.0f, 5.0f, 60.0f));
	//Strada.ModelM = rotate(Strada.ModelM, radians(90.0f), vec3(1.0, 0.0, 0.0));
	Strada.sceltaVS = 1;
	Strada.sceltaFS = 1;
	Strada.material = MaterialType::TERRA;
	Strada.texture = TextureType::SENTIERO;
	Strada.killable = false;
	Strada.alive = true;
	Scena.push_back(Strada);

	//Albero 1
	crea_cilindro(&Tronco, marrone, 8, 8, vec2(4.0, 1.0));
	crea_VAO_Vector(&Tronco);
	Tronco.nome = "Tronco";
	Tronco.BBOriginale = calcolaBoundingBox(&Tronco);

	Tronco.ModelM = mat4(1.0);
	Tronco.ModelM = translate(Tronco.ModelM, vec3(11.0, -5.0, 20.0));
	Tronco.ModelM = scale(Tronco.ModelM, vec3(1.5f, 5.0f, 1.5f));
	Tronco.ModelM = rotate(Tronco.ModelM, radians(180.0f), vec3(1.0, 0.0, 0.0));

	Tronco.sceltaVS = 1;
	Tronco.sceltaFS = 1;
	Tronco.AABB = Tronco.BBOriginale;
	Tronco.AABB.TL = Tronco.ModelM * Tronco.AABB.TL;
	Tronco.AABB.BR = Tronco.ModelM * Tronco.AABB.BR;
	//Tronco.AABB.TL += vec4(0.2, 0.2, 0.2, 0.0) * Tronco.AABB.TL;
	//Tronco.AABB.BR += vec4(0.2, 0.2, 0.2, 0.0) * Tronco.AABB.BR;
	Tronco.AABB = rotateBoundingBox(Tronco.AABB);
	Tronco.AABB = adjustBoundingBox(Tronco.AABB);
	Tronco.material = MaterialType::MARRONE;
	Tronco.texture = TextureType::TRONCO;
	Tronco.killable = true;
	/*printf("Vertici albero: %d\n", Tronco.vertici.size());
	for (int i = 0; i < Tronco.vertici.size(); i++) {
		printf("[%d] = %f, %f, %f\n", i, Tronco.vertici[i].x, Tronco.vertici[i].y, Tronco.vertici[i].z);
	}*/

	crea_cono(&Foglie, verde, 8, 8, vec2(3.0, 1.5));
	crea_VAO_Vector(&Foglie);
	Foglie.nome = "Foglie";
	Foglie.BBOriginale = calcolaBoundingBox(&Foglie);
	Foglie.ModelM = mat4(1.0);
	Foglie.ModelM = translate(Foglie.ModelM, vec3(11.0, 3.0, 20.0));
	Foglie.ModelM = scale(Foglie.ModelM, vec3(4.0f, 8.0f, 4.0f));
	Foglie.ModelM = rotate(Foglie.ModelM, radians(180.0f), vec3(1.0, 0.0, 0.0));
	Foglie.sceltaVS = 1;
	Foglie.sceltaFS = 1;
	Foglie.AABB = Foglie.BBOriginale;
	Foglie.AABB.TL = Foglie.ModelM * Foglie.AABB.TL;
	Foglie.AABB.BR = Foglie.ModelM * Foglie.AABB.BR;
	//Foglie.AABB.TL += vec4(0.2, 0.2, 0.2, 0.0) * Foglie.AABB.TL;
	//Foglie.AABB.BR += vec4(0.2, 0.2, 0.2, 0.0) * Foglie.AABB.BR;
	Foglie.AABB = adjustBoundingBox(Foglie.AABB);
	Foglie.material = MaterialType::VERDE;
	Foglie.texture = TextureType::FOGLIE;	
	Foglie.killable = true;
	Tronco.hp = 3;
	Tronco.alive = true;
	Tronco.linkedMesh = &Foglie;
	Foglie.hp = 3;
	Foglie.alive = true;
	Foglie.linkedMesh = &Tronco;
	/*printf("Hitbox di Tronco Originali: : %f, %f, %f--- %f, %f, %f\n", Tronco.BBOriginale.TL.x, Tronco.BBOriginale.TL.y, Tronco.BBOriginale.TL.z, Tronco.BBOriginale.BR.x, Tronco.BBOriginale.BR.y, Tronco.BBOriginale.BR.z);
	printf("Hitbox di Tronco: : %f, %f, %f--- %f, %f, %f\n", Tronco.AABB.TL.x, Tronco.AABB.TL.y, Tronco.AABB.TL.z, Tronco.AABB.BR.x, Tronco.AABB.BR.y, Tronco.AABB.BR.z);*/
	Scena.push_back(Tronco);
	Scena.push_back(Foglie);

	//Albero 2
	crea_cilindro(&Tronco2, vec4(1.0, 0.0, 0.0, 1.0), 8, 8, vec2(4.0, 2.0));
	crea_VAO_Vector(&Tronco2);
	Tronco2.nome = "Tronco 2";
	Tronco2.BBOriginale = calcolaBoundingBox(&Tronco2);
	Tronco2.ModelM = mat4(1.0);
	Tronco2.ModelM = translate(Tronco2.ModelM, vec3(20.0, -4.0, -20.0));
	Tronco2.ModelM = scale(Tronco2.ModelM, vec3(1.5f, 6.0f, 1.5f));
	Tronco2.ModelM = rotate(Tronco2.ModelM, radians(180.0f), vec3(1.0, 0.0, 0.0));
	Tronco2.sceltaVS = 1;
	Tronco2.sceltaFS = 1;
	Tronco2.AABB = Tronco2.BBOriginale;
	Tronco2.AABB.TL = Tronco2.ModelM * Tronco2.AABB.TL;
	Tronco2.AABB.BR = Tronco2.ModelM * Tronco2.AABB.BR;
	Tronco2.AABB = rotateBoundingBox(Tronco2.AABB);
	Tronco2.AABB = adjustBoundingBox(Tronco2.AABB);
	Tronco2.material = MaterialType::MARRONE;
	Tronco2.texture = TextureType::TRONCO;
	Tronco2.killable = true;
	crea_cono(&Foglie2, vec4(1.0, 0.0, 0.0, 1.0), 8, 8, vec2(3.0, 3.0));
	crea_VAO_Vector(&Foglie2);
	Foglie2.nome = "Foglie 2";
	Foglie2.BBOriginale = calcolaBoundingBox(&Foglie2);
	Foglie2.ModelM = mat4(1.0);
	Foglie2.ModelM = translate(Foglie2.ModelM, vec3(20.0, 8.0, -20.0));
	Foglie2.ModelM = scale(Foglie2.ModelM, vec3(4.0f, 14.0f, 4.0f));
	Foglie2.ModelM = rotate(Foglie2.ModelM, radians(180.0f), vec3(1.0, 0.0, 0.0));
	Foglie2.sceltaVS = 1;
	Foglie2.sceltaFS = 1;
	Foglie2.AABB = Foglie2.BBOriginale;
	Foglie2.AABB.TL = Foglie2.ModelM * Foglie2.AABB.TL;
	Foglie2.AABB.BR = Foglie2.ModelM * Foglie2.AABB.BR;
	Foglie2.AABB = adjustBoundingBox(Foglie2.AABB);
	Foglie2.material = MaterialType::VERDE;
	Foglie2.texture = TextureType::FOGLIE;
	Foglie2.killable = true;
	Tronco2.hp = 3;
	Tronco2.alive = true;
	Tronco2.linkedMesh = &Foglie2;
	Foglie2.hp = 3;
	Foglie2.alive = true;
	Foglie2.linkedMesh = &Tronco2;
	/*printf("Hitbox di Tronco2 Originali: : %f, %f, %f--- %f, %f, %f\n", Tronco2.BBOriginale.TL.x, Tronco2.BBOriginale.TL.y, Tronco2.BBOriginale.TL.z, Tronco2.BBOriginale.BR.x, Tronco2.BBOriginale.BR.y, Tronco2.BBOriginale.BR.z);
	printf("Hitbox di Tronco2: : %f, %f, %f--- %f, %f, %f\n", Tronco2.AABB.TL.x, Tronco2.AABB.TL.y, Tronco2.AABB.TL.z, Tronco2.AABB.BR.x, Tronco2.AABB.BR.y, Tronco2.AABB.BR.z);*/
	Scena.push_back(Tronco2);
	Scena.push_back(Foglie2);

	//Albero 3
	crea_cilindro(&Tronco3, vec4(1.0, 0.0, 0.0, 1.0), 8, 8, vec2(4.0, 2.0));
	crea_VAO_Vector(&Tronco3);
	Tronco3.nome = "Tronco 3";
	Tronco3.BBOriginale = calcolaBoundingBox(&Tronco3);
	Tronco3.ModelM = mat4(1.0);
	Tronco3.ModelM = translate(Tronco3.ModelM, vec3(-19.0, -2.0, -4.0));
	Tronco3.ModelM = scale(Tronco3.ModelM, vec3(1.5f, 8.0f, 1.5f));
	Tronco3.ModelM = rotate(Tronco3.ModelM, radians(180.0f), vec3(1.0, 0.0, 0.0));
	Tronco3.sceltaVS = 1;
	Tronco3.sceltaFS = 1;
	Tronco3.AABB = Tronco3.BBOriginale;
	Tronco3.AABB.TL = Tronco3.ModelM * Tronco3.AABB.TL;
	Tronco3.AABB.BR = Tronco3.ModelM * Tronco3.AABB.BR;
	Tronco3.AABB = rotateBoundingBox(Tronco3.AABB);
	Tronco3.AABB = adjustBoundingBox(Tronco3.AABB);
	Tronco3.material = MaterialType::MARRONE;
	Tronco3.texture = TextureType::TRONCO;
	Tronco3.killable = true;
	crea_cono(&Foglie3, vec4(1.0, 0.0, 0.0, 1.0), 8, 8, vec2(3.0, 3.0));
	crea_VAO_Vector(&Foglie3);
	Foglie3.nome = "Foglie 3";
	Foglie3.BBOriginale = calcolaBoundingBox(&Foglie3);
	Foglie3.ModelM = mat4(1.0);
	Foglie3.ModelM = translate(Foglie3.ModelM, vec3(-19.0, 11.0, -4.0));
	Foglie3.ModelM = scale(Foglie3.ModelM, vec3(4.5f, 14.0f, 4.5f));
	Foglie3.ModelM = rotate(Foglie3.ModelM, radians(180.0f), vec3(1.0, 0.0, 0.0));
	Foglie3.sceltaVS = 1;
	Foglie3.sceltaFS = 1;
	Foglie3.AABB = Foglie3.BBOriginale;
	Foglie3.AABB.TL = Foglie3.ModelM * Foglie3.AABB.TL;
	Foglie3.AABB.BR = Foglie3.ModelM * Foglie3.AABB.BR;
	Foglie3.AABB = adjustBoundingBox(Foglie3.AABB);
	Foglie3.material = MaterialType::VERDE;
	Foglie3.texture = TextureType::FOGLIE;
	Foglie3.killable = true;
	Tronco3.hp = 3;
	Tronco3.alive = true;
	Tronco3.linkedMesh = &Foglie3;
	Foglie3.hp = 3;
	Foglie3.alive = true;
	Foglie3.linkedMesh = &Tronco3;
	/*printf("Hitbox di Tronco3 Originali: : %f, %f, %f--- %f, %f, %f\n", Tronco3.BBOriginale.TL.x, Tronco3.BBOriginale.TL.y, Tronco3.BBOriginale.TL.z, Tronco3.BBOriginale.BR.x, Tronco3.BBOriginale.BR.y, Tronco3.BBOriginale.BR.z);
	printf("Hitbox di Tronco3: : %f, %f, %f--- %f, %f, %f\n", Tronco3.AABB.TL.x, Tronco3.AABB.TL.y, Tronco3.AABB.TL.z, Tronco3.AABB.BR.x, Tronco3.AABB.BR.y, Tronco3.AABB.BR.z);*/
	Scena.push_back(Tronco3);
	Scena.push_back(Foglie3);

	//MURETTO
	//crea_cubo(&Muretto, vec2(2.0, 1.0));
	crea_cubo_ridondante(&Muretto, vec2(5.0, 1.0));
	crea_VAO_Vector(&Muretto);
	Muretto.nome = "Muretto";	
	Muretto.BBOriginale = calcolaBoundingBox(&Muretto);
	Muretto.ModelM = mat4(1.0);
	Muretto.ModelM = translate(Muretto.ModelM, vec3(-28, -7, 0.0));
	Muretto.ModelM = scale(Muretto.ModelM, vec3(1.0,1.0, 28.5));
	Muretto.AABB = Muretto.BBOriginale;
	Muretto.AABB.TL = Muretto.ModelM * Muretto.AABB.TL;
	Muretto.AABB.BR = Muretto.ModelM * Muretto.AABB.BR;
	Muretto.AABB = adjustBoundingBox(Muretto.AABB);
	Muretto.sceltaVS = 1;
	Muretto.sceltaFS = 1;
	Muretto.material = MaterialType::MARRONE;
	Muretto.texture = TextureType::LEGNO;
	Muretto.killable = false;
	Muretto.alive = true;
	/*printf("Hitbox di Muretto Originali: : %f, %f, %f--- %f, %f, %f\n", Muretto.BBOriginale.TL.x, Muretto.BBOriginale.TL.y, Muretto.BBOriginale.TL.z, Muretto.BBOriginale.BR.x, Muretto.BBOriginale.BR.y, Muretto.BBOriginale.BR.z);
	printf("Hitbox di Muretto: : %f, %f, %f--- %f, %f, %f\n", Muretto.AABB.TL.x, Muretto.AABB.TL.y, Muretto.AABB.TL.z, Muretto.AABB.BR.x, Muretto.AABB.BR.y, Muretto.AABB.BR.z);*/
	Scena.push_back(Muretto);

	//Gambe
	crea_cubo_ridondante(&Gamba1, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba1);
	Gamba1.nome = "Gamba 1";
	Gamba1.BBOriginale = calcolaBoundingBox(&Gamba1);
	Gamba1.ModelM = mat4(1.0);
	Gamba1.ModelM = translate(Gamba1.ModelM, vec3(-28, -9, 0.0));
	Gamba1.ModelM = scale(Gamba1.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba1.AABB = Gamba1.BBOriginale;
	Gamba1.AABB.TL = Gamba1.ModelM * Gamba1.AABB.TL;
	Gamba1.AABB.BR = Gamba1.ModelM * Gamba1.AABB.BR;
	Gamba1.AABB = adjustBoundingBox(Gamba1.AABB);
	Gamba1.sceltaVS = 1;
	Gamba1.sceltaFS = 1;
	Gamba1.material = MaterialType::MARRONE;
	Gamba1.texture = TextureType::LEGNO;
	Gamba1.killable = false;
	Gamba1.alive = true;
	Scena.push_back(Gamba1);

	crea_cubo_ridondante(&Gamba2, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba2);
	Gamba2.nome = "Gamba 2";
	Gamba2.BBOriginale = calcolaBoundingBox(&Gamba2);
	Gamba2.ModelM = mat4(1.0);
	Gamba2.ModelM = translate(Gamba2.ModelM, vec3(-28, -9, 12.5));
	Gamba2.ModelM = scale(Gamba2.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba2.AABB = Gamba2.BBOriginale;
	Gamba2.AABB.TL = Gamba2.ModelM * Gamba2.AABB.TL;
	Gamba2.AABB.BR = Gamba2.ModelM * Gamba2.AABB.BR;
	Gamba2.AABB = adjustBoundingBox(Gamba2.AABB);

	Gamba2.sceltaVS = 1;
	Gamba2.sceltaFS = 1;
	Gamba2.material = MaterialType::MARRONE;
	Gamba2.texture = TextureType::LEGNO;
	Gamba2.killable = false;
	Gamba2.alive = true;
	Scena.push_back(Gamba2);

	crea_cubo_ridondante(&Gamba3, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba3);
	Gamba3.nome = "Gamba 3";
	Gamba3.BBOriginale = calcolaBoundingBox(&Gamba3);
	Gamba3.ModelM = mat4(1.0);
	Gamba3.ModelM = translate(Gamba3.ModelM, vec3(-28, -9, 25.0));
	Gamba3.ModelM = scale(Gamba3.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba3.AABB = Gamba3.BBOriginale;
	Gamba3.AABB.TL = Gamba3.ModelM * Gamba3.AABB.TL;
	Gamba3.AABB.BR = Gamba3.ModelM * Gamba3.AABB.BR;
	Gamba3.AABB = adjustBoundingBox(Gamba3.AABB);

	Gamba3.sceltaVS = 1;
	Gamba3.sceltaFS = 1;
	Gamba3.material = MaterialType::MARRONE;
	Gamba3.texture = TextureType::LEGNO;
	Gamba3.killable = false;
	Gamba3.alive = true;
	Scena.push_back(Gamba3);

	crea_cubo_ridondante(&Gamba4, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba4);
	Gamba4.nome = "Gamba 4";
	Gamba4.BBOriginale = calcolaBoundingBox(&Gamba4);
	Gamba4.ModelM = mat4(1.0);
	Gamba4.ModelM = translate(Gamba4.ModelM, vec3(-28, -9, -12.5));
	Gamba4.ModelM = scale(Gamba4.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba4.AABB = Gamba4.BBOriginale;
	Gamba4.AABB.TL = Gamba4.ModelM * Gamba4.AABB.TL;
	Gamba4.AABB.BR = Gamba4.ModelM * Gamba4.AABB.BR;
	Gamba4.AABB = adjustBoundingBox(Gamba4.AABB);
	Gamba4.sceltaVS = 1;
	Gamba4.sceltaFS = 1;
	Gamba4.material = MaterialType::MARRONE;
	Gamba4.texture = TextureType::LEGNO;
	Gamba4.killable = false;
	Gamba4.alive = true;
	Scena.push_back(Gamba4);

	crea_cubo_ridondante(&Gamba5, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba5);
	Gamba5.nome = "Gamba 5";
	Gamba5.BBOriginale = calcolaBoundingBox(&Gamba5);
	Gamba5.ModelM = mat4(1.0);
	Gamba5.ModelM = translate(Gamba5.ModelM, vec3(-28, -9, -25.0));
	Gamba5.ModelM = scale(Gamba5.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba5.AABB = Gamba5.BBOriginale;
	Gamba5.AABB.TL = Gamba5.ModelM * Gamba5.AABB.TL;
	Gamba5.AABB.BR = Gamba5.ModelM * Gamba5.AABB.BR;
	Gamba5.AABB = adjustBoundingBox(Gamba5.AABB);
	Gamba5.sceltaVS = 1;
	Gamba5.sceltaFS = 1;
	Gamba5.material = MaterialType::MARRONE;
	Gamba5.texture = TextureType::LEGNO;
	Gamba5.killable = false;
	Gamba5.alive = true;
	Scena.push_back(Gamba5);

	//MURETTO 2
	crea_cubo_ridondante(&Muretto2, vec2(5.0, 1.0));
	crea_VAO_Vector(&Muretto2);
	Muretto2.nome = "Muretto 2";
	Muretto2.BBOriginale = calcolaBoundingBox(&Muretto2);
	Muretto2.ModelM = mat4(1.0);
	Muretto2.ModelM = translate(Muretto2.ModelM, vec3(-17.0, -7, -28.0));
	Muretto2.ModelM = scale(Muretto2.ModelM, vec3(12.0, 1.0, 1.0));

	Muretto2.AABB = Muretto2.BBOriginale;
	Muretto2.AABB.TL = Muretto2.ModelM * Muretto2.AABB.TL;
	Muretto2.AABB.BR = Muretto2.ModelM * Muretto2.AABB.BR;
	Muretto2.AABB = adjustBoundingBox(Muretto2.AABB);
	Muretto2.sceltaVS = 1;
	Muretto2.sceltaFS = 1;
	Muretto2.material = MaterialType::MARRONE;
	Muretto2.texture = TextureType::LEGNO;
	Muretto2.killable = false;
	Muretto2.alive = true;
	//printf("Hitbox di Muretto2: : %f, %f, %f--- %f, %f, %f\n", Muretto2.AABB.TL.x, Muretto2.AABB.TL.y, Muretto2.AABB.TL.z, Muretto2.AABB.BR.x, Muretto2.AABB.BR.y, Muretto2.AABB.BR.z);
	Scena.push_back(Muretto2);
	
	//MURETTO 3
	crea_cubo_ridondante(&Muretto3, vec2(5.0, 1.0));
	crea_VAO_Vector(&Muretto3);
	Muretto3.nome = "Muretto 3";
	Muretto3.BBOriginale = calcolaBoundingBox(&Muretto3);
	Muretto3.ModelM = mat4(1.0);
	Muretto3.ModelM = translate(Muretto3.ModelM, vec3(17.0, -7, -28.0));
	Muretto3.ModelM = scale(Muretto3.ModelM, vec3(12.0, 1.0, 1.0));

	Muretto3.AABB = Muretto3.BBOriginale;
	Muretto3.AABB.TL = Muretto3.ModelM * Muretto3.AABB.TL;
	Muretto3.AABB.BR = Muretto3.ModelM * Muretto3.AABB.BR;
	Muretto3.AABB = adjustBoundingBox(Muretto3.AABB);
	Muretto3.sceltaVS = 1;
	Muretto3.sceltaFS = 1;
	Muretto3.material = MaterialType::MARRONE;
	Muretto3.texture = TextureType::LEGNO;
	Muretto3.killable = false;
	Muretto3.alive = true;
	//printf("Hitbox di Muretto3: : %f, %f, %f--- %f, %f, %f\n", Muretto3.AABB.TL.x, Muretto3.AABB.TL.y, Muretto3.AABB.TL.z, Muretto3.AABB.BR.x, Muretto3.AABB.BR.y, Muretto3.AABB.BR.z);
	Scena.push_back(Muretto3);


	//Gambe per il secondo muretto
	crea_cubo_ridondante(&Gamba6, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba6);
	Gamba6.nome = "Gamba 6";
	Gamba6.BBOriginale = calcolaBoundingBox(&Gamba6);
	Gamba6.ModelM = mat4(1.0);
	Gamba6.ModelM = translate(Gamba6.ModelM, vec3(0.0, -9, -28.0));
	Gamba6.ModelM = scale(Gamba6.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba6.AABB = Gamba6.BBOriginale;
	Gamba6.AABB.TL = Gamba6.ModelM * Gamba6.AABB.TL;
	Gamba6.AABB.BR = Gamba6.ModelM * Gamba6.AABB.BR;
	Gamba6.AABB = adjustBoundingBox(Gamba6.AABB);
	Gamba6.sceltaVS = 1;
	Gamba6.sceltaFS = 1;
	Gamba6.material = MaterialType::MARRONE;
	Gamba6.texture = TextureType::LEGNO;
	Gamba6.killable = false;
	Gamba6.alive = true;
	//Scena.push_back(Gamba6);	//La gamba 6 sta in mezzo al vialetto quindi non la uso

	crea_cubo_ridondante(&Gamba7, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba7);
	Gamba7.nome = "Gamba 7";
	Gamba7.BBOriginale = calcolaBoundingBox(&Gamba7);
	Gamba7.ModelM = mat4(1.0);
	Gamba7.ModelM = translate(Gamba7.ModelM, vec3(11.0, -9, -28.5));
	Gamba7.ModelM = scale(Gamba7.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba7.AABB = Gamba7.BBOriginale;
	Gamba7.AABB.TL = Gamba7.ModelM * Gamba7.AABB.TL;
	Gamba7.AABB.BR = Gamba7.ModelM * Gamba7.AABB.BR;
	Gamba7.AABB = adjustBoundingBox(Gamba7.AABB);
	Gamba7.sceltaVS = 1;
	Gamba7.sceltaFS = 1;
	Gamba7.material = MaterialType::MARRONE;
	Gamba7.texture = TextureType::LEGNO;
	Gamba7.killable = false;
	Gamba7.alive = true;
	Scena.push_back(Gamba7);

	crea_cubo_ridondante(&Gamba8, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba8);
	Gamba8.nome = "Gamba 8";
	Gamba8.BBOriginale = calcolaBoundingBox(&Gamba8);
	Gamba8.ModelM = mat4(1.0);
	Gamba8.ModelM = translate(Gamba8.ModelM, vec3(-22.0, -9, -28.0));
	Gamba8.ModelM = scale(Gamba8.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba8.AABB = Gamba8.BBOriginale;
	Gamba8.AABB.TL = Gamba8.ModelM * Gamba8.AABB.TL;
	Gamba8.AABB.BR = Gamba8.ModelM * Gamba8.AABB.BR;
	Gamba8.AABB = adjustBoundingBox(Gamba8.AABB);
	Gamba8.sceltaVS = 1;
	Gamba8.sceltaFS = 1;
	Gamba8.material = MaterialType::MARRONE;
	Gamba8.texture = TextureType::LEGNO;
	Gamba8.killable = false;
	Gamba8.alive = true;
	Scena.push_back(Gamba8);

	crea_cubo_ridondante(&Gamba9, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba9);
	Gamba9.nome = "Gamba 9";
	Gamba9.BBOriginale = calcolaBoundingBox(&Gamba9);
	Gamba9.ModelM = mat4(1.0);
	Gamba9.ModelM = translate(Gamba9.ModelM, vec3(-11, -9, -28.0));
	Gamba9.ModelM = scale(Gamba9.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba9.AABB = Gamba9.BBOriginale;
	Gamba9.AABB.TL = Gamba9.ModelM * Gamba9.AABB.TL;
	Gamba9.AABB.BR = Gamba9.ModelM * Gamba9.AABB.BR;
	Gamba9.AABB = adjustBoundingBox(Gamba9.AABB);
	Gamba9.sceltaVS = 1;
	Gamba9.sceltaFS = 1;
	Gamba9.material = MaterialType::MARRONE;
	Gamba9.texture = TextureType::LEGNO;
	Gamba9.killable = false;
	Gamba9.alive = true;
	Scena.push_back(Gamba9);

	crea_cubo_ridondante(&Gamba10, vec2(2.0, 1.0));
	crea_VAO_Vector(&Gamba10);
	Gamba10.nome = "Gamba 10";
	Gamba10.BBOriginale = calcolaBoundingBox(&Gamba10);
	Gamba10.ModelM = mat4(1.0);
	Gamba10.ModelM = translate(Gamba10.ModelM, vec3(22.0, -9, -28.0));
	Gamba10.ModelM = scale(Gamba10.ModelM, vec3(0.5, 1.0, 0.5));
	Gamba10.AABB = Gamba10.BBOriginale;
	Gamba10.AABB.TL = Gamba10.ModelM * Gamba10.AABB.TL;
	Gamba10.AABB.BR = Gamba10.ModelM * Gamba10.AABB.BR;	
	Gamba10.AABB = adjustBoundingBox(Gamba10.AABB);
	Gamba10.sceltaVS = 1;
	Gamba10.sceltaFS = 1;
	Gamba10.material = MaterialType::MARRONE;
	Gamba10.texture = TextureType::LEGNO;
	Gamba10.killable = false;
	Gamba10.alive = true;
	Scena.push_back(Gamba10);
	collegaMesh();


	bool obj;
	int nmeshes;
	string name;
	string path;
	BoundingBox bbobj;
	
	name = "waterWell.obj";
	path = Meshdir + name;
	obj = loadAssImp(path.c_str(), Model3D);

	nmeshes = Model3D.size();
	//printf("Model3D size: %d\n", nmeshes);

	for (int i = 0; i < nmeshes; i++)
	{
		crea_VAO_Vector_MeshObj(&Model3D[i]);
		Model3D[i].ModelM = mat4(1.0);
		Model3D[i].ModelM = translate(Model3D[i].ModelM, vec3(-15.0, -10, 15.0));
		Model3D[i].ModelM = scale(Model3D[i].ModelM, vec3(1, 1, 1));
		Model3D[i].ModelM = rotate(Model3D[i].ModelM, radians(-21.0f), vec3(0.0, 1.0, 0.0));
		Model3D[i].nome = "Pozzo";

		Model3D[i].sceltaVS = 1;
		Model3D[i].sceltaFS = 6;
	}
	bbobj = calcolaBoundingBoxOBJ(Model3D);
	bbobj.TL = Model3D[0].ModelM * bbobj.TL;
	bbobj.BR = Model3D[0].ModelM * bbobj.BR;
	bbobj = rotateBoundingBox(bbobj);
	//printf("Hitbox di Pozzo: : %f, %f, %f--- %f, %f, %f\n", bbobj.TL.x, bbobj.TL.y, bbobj.TL.z, bbobj.BR.x, bbobj.BR.y, bbobj.BR.z);
	BoundingBoxOBJVector.push_back(bbobj);

	ScenaObj.push_back(Model3D);

	Model3D.clear();
	
	name = "LProck2.obj";
	path = Meshdir + name;
	obj = loadAssImp(path.c_str(), Model3D);
	nmeshes = Model3D.size();
	//printf("Model3D size: %d\n", nmeshes);
	for (int i = 0; i < nmeshes; i++)
	{
		crea_VAO_Vector_MeshObj(&Model3D[i]);
		Model3D[i].ModelM = mat4(1.0);
		Model3D[i].ModelM = translate(Model3D[i].ModelM, vec3(-22.0, -7.5, -20.0));
		Model3D[i].ModelM = scale(Model3D[i].ModelM, vec3(2.3, 2.5, 3));
		Model3D[i].ModelM = rotate(Model3D[i].ModelM, radians(-21.0f), vec3(0.0, 1.0, 0.0));
		Model3D[i].nome = "Roccia 1";
		Model3D[i].sceltaVS = 1;
		Model3D[i].sceltaFS = 6;
	}
	bbobj = calcolaBoundingBoxOBJ(Model3D);
	bbobj.TL = Model3D[0].ModelM * bbobj.TL;
	bbobj.BR = Model3D[0].ModelM * bbobj.BR;
	bbobj = rotateBoundingBox(bbobj);
	//printf("Hitbox di Roccia: : %f, %f, %f--- %f, %f, %f\n", bbobj.TL.x, bbobj.TL.y, bbobj.TL.z, bbobj.BR.x, bbobj.BR.y, bbobj.BR.z);
	BoundingBoxOBJVector.push_back(bbobj);
	ScenaObj.push_back(Model3D);
	Model3D.clear();
	name = "LProck1.obj";
	path = Meshdir + name;
	obj = loadAssImp(path.c_str(), Model3D);
	nmeshes = Model3D.size();
	//printf("Model3D size: %d\n", nmeshes);
	for (int i = 0; i < nmeshes; i++)
	{
		crea_VAO_Vector_MeshObj(&Model3D[i]);
		Model3D[i].ModelM = mat4(1.0);
		Model3D[i].ModelM = translate(Model3D[i].ModelM, vec3(-18.0, -8.5, -18.0));
		Model3D[i].ModelM = scale(Model3D[i].ModelM, vec3(4, 1.5, 3));
		Model3D[i].ModelM = rotate(Model3D[i].ModelM, radians(33.0f), vec3(0.0, 1.0, 0.0));
		Model3D[i].nome = "Roccia 1";
		Model3D[i].sceltaVS = 1;
		Model3D[i].sceltaFS = 6;
	}
	bbobj = calcolaBoundingBoxOBJ(Model3D);
	bbobj.TL = Model3D[0].ModelM * bbobj.TL;
	bbobj.BR = Model3D[0].ModelM * bbobj.BR;
	BoundingBoxOBJVector.push_back(bbobj);
	ScenaObj.push_back(Model3D);
	Model3D.clear();

	name = "LProck2.obj";
	path = Meshdir + name;
	obj = loadAssImp(path.c_str(), Model3D);
	nmeshes = Model3D.size();
	//printf("Model3D size: %d\n", nmeshes);
	for (int i = 0; i < nmeshes; i++)
	{
		crea_VAO_Vector_MeshObj(&Model3D[i]);
		Model3D[i].ModelM = mat4(1.0);
		Model3D[i].ModelM = translate(Model3D[i].ModelM, vec3(17.0, -6.0, 11.0));
		Model3D[i].ModelM = scale(Model3D[i].ModelM, vec3(5.3, 4.0, 3.1));
		Model3D[i].ModelM = rotate(Model3D[i].ModelM, radians(20.0f), vec3(0.0, 1.0, 0.0));
		Model3D[i].nome = "Roccia 3";
		Model3D[i].sceltaVS = 1;
		Model3D[i].sceltaFS = 6;
	}
	bbobj = calcolaBoundingBoxOBJ(Model3D);
	bbobj.TL = Model3D[0].ModelM * bbobj.TL;
	bbobj.BR = Model3D[0].ModelM * bbobj.BR;
	bbobj = rotateBoundingBox(bbobj);
	BoundingBoxOBJVector.push_back(bbobj);
	ScenaObj.push_back(Model3D);
	Model3D.clear();
	name = "LProck2.obj";
	path = Meshdir + name;
	obj = loadAssImp(path.c_str(), Model3D);
	nmeshes = Model3D.size();
	//printf("Model3D size: %d\n", nmeshes);
	for (int i = 0; i < nmeshes; i++)
	{
		crea_VAO_Vector_MeshObj(&Model3D[i]);
		Model3D[i].ModelM = mat4(1.0);
		Model3D[i].ModelM = translate(Model3D[i].ModelM, vec3(21.0, -8.0, 5.0));
		Model3D[i].ModelM = scale(Model3D[i].ModelM, vec3(3.3, 2.0, 4.1));
		Model3D[i].ModelM = rotate(Model3D[i].ModelM, radians(0.0f), vec3(0.0, 1.0, 0.0));
		Model3D[i].nome = "Roccia 4";
		Model3D[i].sceltaVS = 1;
		Model3D[i].sceltaFS = 6;
	}
	bbobj = calcolaBoundingBoxOBJ(Model3D);
	bbobj.TL = Model3D[0].ModelM * bbobj.TL;
	bbobj.BR = Model3D[0].ModelM * bbobj.BR;
	bbobj = rotateBoundingBox(bbobj);
	BoundingBoxOBJVector.push_back(bbobj);
	ScenaObj.push_back(Model3D);
	Model3D.clear();

	name = "LProck3.obj";
	path = Meshdir + name;
	obj = loadAssImp(path.c_str(), Model3D);
	nmeshes = Model3D.size();
	for (int i = 0; i < nmeshes; i++)
	{
		crea_VAO_Vector_MeshObj(&Model3D[i]);
		Model3D[i].ModelM = mat4(1.0);
		Model3D[i].ModelM = translate(Model3D[i].ModelM, vec3(24.0, -7.0, 24.0));
		Model3D[i].ModelM = scale(Model3D[i].ModelM, vec3(3.7, 3.0, 2.5));
		Model3D[i].ModelM = rotate(Model3D[i].ModelM, radians(20.0f), vec3(0.0, 1.0, 0.0));
		Model3D[i].nome = "Roccia 4";
		Model3D[i].sceltaVS = 1;
		Model3D[i].sceltaFS = 6;
	}
	bbobj = calcolaBoundingBoxOBJ(Model3D);
	bbobj.TL = Model3D[0].ModelM * bbobj.TL;
	bbobj.BR = Model3D[0].ModelM * bbobj.BR;
	bbobj = rotateBoundingBox(bbobj);
	BoundingBoxOBJVector.push_back(bbobj);
	ScenaObj.push_back(Model3D);
	Model3D.clear();
	//Animali
	name = "pigeon.obj";
	path = Meshdir + name;
	obj = loadAssImp(path.c_str(), Model3D);
	nmeshes = Model3D.size();
	for (int i = 0; i < nmeshes; i++)
	{
		crea_VAO_Vector_MeshObj(&Model3D[i]);
		Model3D[i].ModelM = mat4(1.0);
		Model3D[i].ModelM = translate(Model3D[i].ModelM, vec3(11.0, -9.7, -15.0));
		Model3D[i].ModelM = scale(Model3D[i].ModelM, vec3(0.3, 0.3, 0.3));
		Model3D[i].ModelM = rotate(Model3D[i].ModelM, radians(20.0f), vec3(0.0, 1.0, 0.0));
		Model3D[i].nome = "Piccione";
		Model3D[i].sceltaVS = 1;
		Model3D[i].sceltaFS = 6;
	}
	bbobj = calcolaBoundingBoxOBJ(Model3D);
	bbobj.TL = Model3D[0].ModelM * bbobj.TL;
	bbobj.BR = Model3D[0].ModelM * bbobj.BR;
	bbobj = rotateBoundingBox(bbobj);
	BoundingBoxOBJVector.push_back(bbobj);
	ScenaObj.push_back(Model3D);
	Model3D.clear();

	name = "pigeon.obj";
	path = Meshdir + name;
	obj = loadAssImp(path.c_str(), Model3D);
	nmeshes = Model3D.size();
	for (int i = 0; i < nmeshes; i++)
	{
		crea_VAO_Vector_MeshObj(&Model3D[i]);
		Model3D[i].ModelM = mat4(1.0);
		Model3D[i].ModelM = translate(Model3D[i].ModelM, vec3(17.0, -1.6, 11.0));
		Model3D[i].ModelM = scale(Model3D[i].ModelM, vec3(0.4, 0.4, 0.4));
		Model3D[i].ModelM = rotate(Model3D[i].ModelM, radians(60.0f), vec3(0.0, 1.0, 0.0));
		Model3D[i].nome = "Piccione 2";
		Model3D[i].sceltaVS = 1;
		Model3D[i].sceltaFS = 6;
	}
	bbobj = calcolaBoundingBoxOBJ(Model3D);
	bbobj.TL = Model3D[0].ModelM * bbobj.TL;
	bbobj.BR = Model3D[0].ModelM * bbobj.BR;
	bbobj = rotateBoundingBox(bbobj);
	BoundingBoxOBJVector.push_back(bbobj);
	ScenaObj.push_back(Model3D);
	Model3D.clear();

	//Queste due sfere sono "di debug" per vedere gli angoli della bounding box di un modello caricato via OBJ
	/*crea_sfera(&Sfera1, vec4(1.0, 0.0, 0.0, 1.0));
	crea_VAO_Vector(&Sfera1);
	Sfera1.ModelM = mat4(1.0);
	Sfera1.ModelM = translate(Sfera1.ModelM, vec3(bbobj.TL.x, bbobj.TL.y, bbobj.TL.z));
	Sfera1.ModelM = scale(Sfera1.ModelM, vec3(1.0f, 1.0f, 1.0f));
	Sfera1.sceltaVS = 1;
	Sfera1.sceltaFS = 1;
	Sfera1.material = MaterialType::EMERALD;
	Sfera1.texture = TextureType::SENZA;
	Scena.push_back(Sfera1);

	crea_sfera(&Sfera2, vec4(1.0, 0.0, 0.0, 1.0));
	crea_VAO_Vector(&Sfera2);
	Sfera2.ModelM = mat4(1.0);
	Sfera2.ModelM = translate(Sfera2.ModelM, vec3(bbobj.BR.x, bbobj.BR.y, bbobj.BR.z));
	Sfera.ModelM = scale(Sfera2.ModelM, vec3(1.0f, 1.0f, 1.0f));
	Sfera2.sceltaVS = 1;
	Sfera2.sceltaFS = 1;
	Sfera2.material = MaterialType::EMERALD;
	Sfera2.texture = TextureType::SENZA;
	Scena.push_back(Sfera2);*/

}





	
void keyboardReleasedEvent(unsigned char key, int x, int y)
{
	{
		switch (key)
		{
		case 'v':
			visualizzaAncora = FALSE;
			break;
		default:
			break;
		}
	}
	glutPostRedisplay();
}
	
void INIT_CAMERA_PROJECTION(void)
{
	//Imposto la telecamera

	ViewSetup = {};
	resettaCamera();


	//Imposto la proiezione prospettica
	PerspectiveSetup = {};
	PerspectiveSetup.aspect = (GLfloat)width / (GLfloat)height;
	PerspectiveSetup.fovY = 45.0f;
	PerspectiveSetup.far_plane = 2000.0f;
	PerspectiveSetup.near_plane = 0.1f;
}


void resize(int w, int h)
{
	//Imposto la matrice di Proiezione per il rendering del testo

	 
	//Imposto la matrice di proiezione per la scena da diegnare
	Projection = perspective(radians(PerspectiveSetup.fovY), PerspectiveSetup.aspect, PerspectiveSetup.near_plane, PerspectiveSetup.far_plane);

	float AspectRatio_mondo = (float)(width) / (float)(height); //Rapporto larghezza altezza di tutto ci? che ? nel mondo
	 //Se l'aspect ratio del mondo ? diversa da quella della finestra devo mappare in modo diverso 
	 //per evitare distorsioni del disegno
	if (AspectRatio_mondo > w / h)   //Se ridimensioniamo la larghezza della Viewport
	{
		glViewport(0, 0, w, w / AspectRatio_mondo);
		w_up = (float)w;
		h_up = w / AspectRatio_mondo;
	}
	else {  //Se ridimensioniamo la larghezza della viewport oppure se l'aspect ratio tra la finestra del mondo 
			//e la finestra sullo schermo sono uguali
		glViewport(0, 0, h * AspectRatio_mondo, h);
		w_up = h * AspectRatio_mondo;
		h_up = (float)h;
	}
}



void drawScene(void)
{

	glUniformMatrix4fv(MatrixProj, 1, GL_FALSE, value_ptr(Projection));
	View = lookAt(vec3(ViewSetup.position), vec3(ViewSetup.target), vec3(ViewSetup.upVector));
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Disegno Sky box
 	 
	glDepthMask(GL_FALSE);
	glUseProgram(programId1);
	glUniform1i(glGetUniformLocation(programId1, "skybox"), 0);
	glUniformMatrix4fv(MatrixProjS, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(MatViewS, 1, GL_FALSE, value_ptr(View));
	// skybox cube
	glBindVertexArray(Scena[0].VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawElements(GL_TRIANGLES, Scena[0].indici.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
 
	 
	//Costruisco la matrice di Vista che applicata ai vertici in coordinate del mondo li trasforma nel sistema di riferimento della camera.
	
	//Passo al Vertex Shader il puntatore alla matrice View, che sar? associata alla variabile Uniform mat4 Projection
   //all'interno del Vertex shader. Uso l'identificatio MatView
	glPointSize(10.0);

	//Uso il program shader per gestire la riflessione della sfera (oggetto in posizione 1 di Scena)
	/*glUseProgram(programIdr);

	glUniformMatrix4fv(MatrixProjR, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(MatModelR, 1, GL_FALSE, value_ptr(Scena[1].ModelM));
	glUniformMatrix4fv(MatViewR, 1, GL_FALSE, value_ptr(View));
	glUniform3f(loc_view_posR, ViewSetup.position.x, ViewSetup.position.y, ViewSetup.position.z);
	glBindVertexArray(Scena[1].VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawElements(GL_TRIANGLES, (Scena[1].indici.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);*/
	//Cambio program per renderizzare tutto il resto della scena
	
	glUseProgram(programId);
	glUniformMatrix4fv(MatView, 1, GL_FALSE, value_ptr(View));


	//Passo allo shader il puntatore a  colore luce, posizione ed intensit?
	 
	//glUniform3f(light_unif.light_position_pointer, light.position.x + 10 * cos(radians(angolo)), light.position.y, light.position.z + 10 * sin(radians(angolo)));
	 glUniform3f(light_unif.light_position_pointer, light.position.x  , light.position.y, light.position.z);

	glUniform3f(light_unif.light_color_pointer, light.color.r, light.color.g, light.color.b);
	glUniform1f(light_unif.light_power_pointer, light.power);
 
	//Passo allo shader il puntatore alla posizione della camera
	glUniform3f(loc_view_pos, ViewSetup.position.x, ViewSetup.position.y, ViewSetup.position.z);

	for (int k =1; k < Scena.size(); k++)
	{
		if (Scena[k].alive) {
			//Trasformazione delle coordinate dell'ancora dal sistema di riferimento dell'oggetto in sistema
			//di riferimento del mondo premoltiplicando per la matrice di Modellazione.

			Scena[k].ancora_world = Scena[k].ancora_obj;
			Scena[k].ancora_world = Scena[k].ModelM * Scena[k].ancora_world;
			//Passo al Vertex Shader il puntatore alla matrice Model dell'oggetto k-esimo della Scena, che sar? associata alla variabile Uniform mat4 Projection
			//all'interno del Vertex shader. Uso l'identificativo MatModel
		 
			glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[k].ModelM));
			glUniform1i(lsceltaVS, Scena[k].sceltaVS);
			glUniform1i(lsceltaFS, Scena[k].sceltaFS);
			//Passo allo shader il puntatore ai materiali
			glUniform3fv(light_unif.material_ambient, 1, glm::value_ptr(materials[Scena[k].material].ambient));
			glUniform3fv(light_unif.material_diffuse, 1, glm::value_ptr(materials[Scena[k].material].diffuse));
			glUniform3fv(light_unif.material_specular, 1, glm::value_ptr(materials[Scena[k].material].specular));
			glUniform1f(light_unif.material_shininess, materials[Scena[k].material].shininess);
	 
			glBindVertexArray(Scena[k].VAO);
		
	 		if (visualizzaAncora==TRUE)
			{
				//Visualizzo l'ancora dell'oggetto
				int ind = Scena[k].indici.size() - 1;

		
				glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, BUFFER_OFFSET(ind * sizeof(GLuint)));
			}
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//Fare questo switch con un altra propriet? dell'oggetto Scena[k] e compararlo con delle costanti definite
			switch (Scena[k].texture) {
				case TextureType::ERBA: 
					glUniform1i(loc_texture, 0);
					glBindTexture(GL_TEXTURE_2D, texturePiano);
					break;
				case TextureType::TRONCO:
					glUniform1i(loc_texture, 0);
					glBindTexture(GL_TEXTURE_2D, textureTronco);
					break;
				case TextureType::FOGLIE:
					glUniform1i(loc_texture, 0);
					glBindTexture(GL_TEXTURE_2D, textureFoglie);
					break;
				case TextureType::LEGNO:
					glUniform1i(loc_texture, 0);
					glBindTexture(GL_TEXTURE_2D, textureLegno);
					break;
				case TextureType::SENTIERO:
					glUniform1i(loc_texture, 0);
					glBindTexture(GL_TEXTURE_2D, textureRockyTrail);
					break;
				default: 
					glUniform1i(loc_texture, 0);
					glBindTexture(GL_TEXTURE_2D, 0);
					break;
			}
			glDrawElements(GL_TRIANGLES, (Scena[k].indici.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	 
			glBindVertexArray(0);
	 
		}
	}
	//Visualizzo gli oggetti di tipo Mesh Obj caricati dall'esterno: 
	//la j-esima Mesh ? costituita da ScenaObj[j].size() mesh. 
	for (int j = 0; j < ScenaObj.size() ; j++)
	{

		for (int k = 0; k < ScenaObj[j].size(); k++)
		{

			//Trasformazione delle coordinate dell'ancora dal sistema di riferimento dell'oggetto in sistema
			//di riferimento del mondo premoltiplicando per la matrice di Modellazione.

			//Passo al Vertex Shader il puntatore alla matrice Model dell'oggetto k-esimo della Scena, che sar? associata alla variabile Uniform mat4 Projection
			//all'interno del Vertex shader. Uso l'identificatio MatModel


			glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ScenaObj[j][k].ModelM));
			glUniform1i(lsceltaVS, ScenaObj[j][k].sceltaVS);
			glUniform1i(lsceltaFS, ScenaObj[j][k].sceltaFS);
			//Passo allo shader il puntatore ai materiali
			glUniform3fv(light_unif.material_ambient, 1, value_ptr(ScenaObj[j][k].materiale.ambient));
			glUniform3fv(light_unif.material_diffuse, 1, value_ptr(ScenaObj[j][k].materiale.diffuse));
			glUniform3fv(light_unif.material_specular, 1, value_ptr(ScenaObj[j][k].materiale.specular));
			glUniform1f(light_unif.material_shininess, ScenaObj[j][k].materiale.shininess);

			glBindVertexArray(ScenaObj[j][k].VAO);

			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glDrawElements(GL_TRIANGLES, (ScenaObj[j][k].indici.size()) * sizeof(GLuint), GL_UNSIGNED_INT, 0);


			glBindVertexArray(0);
		}

	}

	 
	 
	glutSwapBuffers();

}
void update(int a)
{
	angolo += 1;
	glutTimerFunc(10, update, 0);
	glutPostRedisplay();

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	//Inizializzo finestra per il rendering della scena 3d con tutti i suoi eventi le sue inizializzazioni e le sue impostazioni

	glutInitWindowSize(width, height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Progetto OpenGL3D");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardPressedEvent);
	glutKeyboardUpFunc(keyboardReleasedEvent);
	//glutPassiveMotionFunc(my_passive_mouse);

	
	glutMotionFunc(mouseActiveMotion); // Evento tasto premuto
	glutTimerFunc(10, update, 0);
	glewExperimental = GL_TRUE;
	glewInit();


	//Inizializzazione setup illuminazione, materiali
	INIT_Illuminazione();
	//Inizializzazione setup Shader
	INIT_SHADER();
	//Inizializzazione VAO
	INIT_VAO();
	//Inizializzazione setup telecamera
	INIT_CAMERA_PROJECTION();

	//Menu collegato al tasto centrale
	buildOpenGLMenu();

	

	//Abilita l'uso del Buffer di Profondit? per la gestione dell'eliminazione dlele superifici nascoste
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
 
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Projection (in vertex shader).
	//QUesto identificativo sar? poi utilizzato per il trasferimento della matrice Projection al Vertex Shader
	MatrixProj = glGetUniformLocation(programId, "Projection");
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Model (in vertex shader)
	//QUesto identificativo sar? poi utilizzato per il trasferimento della matrice Model al Vertex Shader
	MatModel = glGetUniformLocation(programId, "Model");
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 View (in vertex shader)
	//QUesto identificativo sar? poi utilizzato per il trasferimento della matrice View al Vertex Shader
	MatView = glGetUniformLocation(programId, "View");
 	lsceltaVS = glGetUniformLocation(programId, "sceltaVS");
	lsceltaFS= glGetUniformLocation(programId, "sceltaFS");
	loc_view_pos = glGetUniformLocation(programId, "ViewPos");
	loc_texture= glGetUniformLocation(programId, "id_tex");
	 //location delle variabili uniformi per la gestione della luce
	light_unif.light_position_pointer = glGetUniformLocation(programId, "light.position");
	light_unif.light_color_pointer = glGetUniformLocation(programId, "light.color");
	light_unif.light_power_pointer = glGetUniformLocation(programId, "light.power");

	//location delle variabili uniformi per la gestione dei materiali
	light_unif.material_ambient = glGetUniformLocation(programId, "material.ambient");
	light_unif.material_diffuse = glGetUniformLocation(programId, "material.diffuse");
	light_unif.material_specular = glGetUniformLocation(programId, "material.specular");
	light_unif.material_shininess = glGetUniformLocation(programId, "material.shininess");
 
	//location variabili uniformi per lo shader della gestione della cubemap
	MatrixProjS = glGetUniformLocation(programId1, "Projection");
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Model (in vertex shader)
	//QUesto identificativo sar? poi utilizzato per il trasferimento della matrice Model al Vertex Shader


	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Model (in vertex shader)
	//QUesto identificativo sar? poi utilizzato per il trasferimento della matrice Model al Vertex Shader
	MatViewS = glGetUniformLocation(programId1, "View");

 
	MatModelR = glGetUniformLocation(programIdr, "Model");
	MatViewR = glGetUniformLocation(programIdr, "View");
	MatrixProjR = glGetUniformLocation(programIdr, "Projection");
	loc_view_posR = glGetUniformLocation(programIdr, "ViewPos");
	loc_cubemapR = glGetUniformLocation(programIdr, "cubemap");
	glutMainLoop();
}

