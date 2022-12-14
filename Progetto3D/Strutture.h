#pragma once
#pragma once
#include "Lib.h"

#include <string>



struct {
	vec4 position;
	vec4 target;
	vec4 upVector;
	vec4 direction;
} ViewSetup;

struct {
	float fovY, aspect, near_plane, far_plane;
} PerspectiveSetup;

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

typedef struct {
	string name;
	int value;
} Shader;



typedef struct {
	glm::vec3 position;
	glm::vec3 color;
	GLfloat power;
} point_light;

typedef struct {
	GLuint light_position_pointer;
	GLuint light_color_pointer;
	GLuint light_power_pointer;
	GLuint material_diffuse;
	GLuint material_ambient;
	GLuint material_specular;
	GLuint material_shininess;
} LightShaderUniform;

typedef struct {
	vec4 TL;
	vec4 BR;
}BoundingBox;

typedef enum {
	RED_PLASTIC,
	VERDE,
	BRASS,
	SNOW_WHITE,
	YELLOW,
	ROSA,
	MARRONE,
	TERRA,
	NO_MATERIAL
} MaterialType;

typedef enum {
	NONE,
	PHONG_INTERPL_SHADING,
	PHONG_PHONG_SHADING,
	BLINN_PHONG_INTERPL_SHADING,
	BLINN_PHONG_PHONG_SHADING,
	TOON_SHADING
} ShaderOption;

typedef struct {
	string name;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat shininess;
} Material;

typedef enum {
	GOURAUD,
	PHONG,
	BLINN,
	TOON
} ShadingType;

typedef enum {
	SENZA,
	TRONCO,
	ERBA,
	FOGLIE,
	MURO,
	SENTIERO,
	LEGNO
} TextureType;
typedef struct Mesh Mesh;
struct Mesh{
	vector<vec3> vertici;
	vector<vec3> CP;
	vector<vec4> colori;
	vector <GLuint>  indici;
	vector<vec3> normali;
	vector<vec2> texCoords;
	mat4 ModelM;
	int sceltaVS;
	int sceltaFS;
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	GLuint VBO_normali;
	GLuint EBO_indici;
	GLuint VBO_coord_texture;
	ShadingType shading;
	MaterialType material;
	TextureType texture;
	string nome;
	vec4 ancora_obj;
	vec4 ancora_world;
	BoundingBox BBOriginale;	//La bounding box con le coordinate di modellazione
	BoundingBox AABB;	//La bounding box post-trasformazioni
	int hp;
	bool alive;
	bool killable;
	Mesh *linkedMesh;
};

typedef struct {
	vector<vec3> vertici;
	vector<vec4> colori;
	vector <GLuint>  indici;
	vector<vec3> normali;
	vector<vec2> texCoords;
	mat4 ModelM;
	int sceltaVS;
	int sceltaFS;
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	GLuint VBO_normali;
	GLuint EBO_indici;
	GLuint VBO_coord_texture;
	ShadingType shading;
	Material materiale;
	string nome;
	vec4 ancora_obj;
	vec4 ancora_world;
} MeshObj;

static vector<Mesh> Scena;