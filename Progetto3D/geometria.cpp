#include "Strutture.h"
#include "Lib.h"
 


void crea_cubo(Mesh* mesh, vec2 fattori)
{

	mesh->vertici.push_back(vec3(-1.0, -1.0, 1.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, -1.0, 1.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, 1.0, 1.0));
	mesh->colori.push_back(vec4(0.0, 0.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(-1.0, 1.0, 1.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 1.0, 0.5));
	// back
	mesh->vertici.push_back(vec3(-1.0, -1.0, -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, -1.0, -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, 1.0, -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(-1.0, 1.0, -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 0.5));

	
	
	mesh->vertici.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));

	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);
	mesh->indici.push_back(2); mesh->indici.push_back(3); mesh->indici.push_back(0);
	mesh->indici.push_back(1); mesh->indici.push_back(5); mesh->indici.push_back(6);
	mesh->indici.push_back(6); mesh->indici.push_back(2); mesh->indici.push_back(1);
	mesh->indici.push_back(7); mesh->indici.push_back(6); mesh->indici.push_back(5);
	mesh->indici.push_back(5); mesh->indici.push_back(4); mesh->indici.push_back(7);
	mesh->indici.push_back(4); mesh->indici.push_back(0); mesh->indici.push_back(3);
	mesh->indici.push_back(3); mesh->indici.push_back(7); mesh->indici.push_back(4);
	mesh->indici.push_back(4); mesh->indici.push_back(5); mesh->indici.push_back(1);
	mesh->indici.push_back(1); mesh->indici.push_back(0); mesh->indici.push_back(4);
	mesh->indici.push_back(3); mesh->indici.push_back(2); mesh->indici.push_back(6);
	mesh->indici.push_back(6); mesh->indici.push_back(7); mesh->indici.push_back(3);

	mesh->normali.push_back(normalize(vec3(0, 0, 1)));
	mesh->normali.push_back(normalize(vec3(0, 0, 1)));
	mesh->normali.push_back(normalize(vec3(0, 0, 1)));
	mesh->normali.push_back(normalize(vec3(0, 0, 1)));
	mesh->normali.push_back(normalize(vec3(0, 0, -1)));
	mesh->normali.push_back(normalize(vec3(0, 0, -1)));
	mesh->normali.push_back(normalize(vec3(0, 0, -1)));
	mesh->normali.push_back(normalize(vec3(0, 0, -1)));
	int nv = mesh->vertici.size();
 
	mesh->indici.push_back(nv-1);
	
	mesh->texCoords.push_back(vec2(0.0, fattori.y));
	mesh->texCoords.push_back(vec2(fattori.x, fattori.y));
	mesh->texCoords.push_back(vec2(fattori.x, 0.0));
	mesh->texCoords.push_back(vec2(0.0, 0.0));
	mesh->texCoords.push_back(vec2(0.0, fattori.y));
	mesh->texCoords.push_back(vec2(fattori.x, fattori.y));
	mesh->texCoords.push_back(vec2(fattori.x, 0.0));
	mesh->texCoords.push_back(vec2(0.0, 0.0));


}
//NON USARE
void deprecated_cubo(Mesh* mesh, vec2 fattori) {
	mesh->vertici.push_back(vec3(-0.5f, 0.0f, 0.5f));
	mesh->vertici.push_back(vec3(0.5f, 0.0f, 0.5f));
	mesh->vertici.push_back(vec3(0.5f, 1.0f, 0.5f));
	mesh->vertici.push_back(vec3(-0.5f, 1.0f, 0.5f));
	mesh->vertici.push_back(vec3(-0.5f, 1.0f, -0.5f));
	mesh->vertici.push_back(vec3(0.5f, 1.0f, -0.5f));
	mesh->vertici.push_back(vec3(0.5f, 0.0f, -0.5f));
	mesh->vertici.push_back(vec3(-0.5f, 0.0f, -0.5f));
	mesh->vertici.push_back(vec3(0.5f, 0.0f, 0.5f));
	mesh->vertici.push_back(vec3(0.5f, 0.0f, -0.5f));
	mesh->vertici.push_back(vec3(0.5f, 1.0f, -0.5f));
	mesh->vertici.push_back(vec3(0.5f, 1.0f, 0.5f));
	mesh->vertici.push_back(vec3(-0.5f, 0.0f, -0.5f));
	mesh->vertici.push_back(vec3(-0.5f, 0.0f, 0.5f));
	mesh->vertici.push_back(vec3(-0.5f, 1.0f, 0.5f));
	mesh->vertici.push_back(vec3(-0.5f, 1.0f, -0.5f));

	for (int i = 0; i < mesh->vertici.size(); i++)
		mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 1.0));

	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2); mesh->indici.push_back(3);
	mesh->indici.push_back(4); mesh->indici.push_back(5); mesh->indici.push_back(6); mesh->indici.push_back(7);
	mesh->indici.push_back(3); mesh->indici.push_back(2); mesh->indici.push_back(5); mesh->indici.push_back(4);
	mesh->indici.push_back(7); mesh->indici.push_back(6); mesh->indici.push_back(1); mesh->indici.push_back(0);
	mesh->indici.push_back(8); mesh->indici.push_back(9); mesh->indici.push_back(10); mesh->indici.push_back(11);
	mesh->indici.push_back(12); mesh->indici.push_back(13); mesh->indici.push_back(14); mesh->indici.push_back(15);

	mesh->texCoords.push_back(vec2(0.0, 0.0));
	mesh->texCoords.push_back(vec2(1.0,0.0));
	mesh->texCoords.push_back(vec2(1.0,1.0));
	mesh->texCoords.push_back(vec2(0.0,1.0));
	mesh->texCoords.push_back(vec2(0.0,0.0));
	mesh->texCoords.push_back(vec2(1.0,0.0));
	mesh->texCoords.push_back(vec2(1.0,1.0));
	mesh->texCoords.push_back(vec2(0.0,1.0));
	mesh->texCoords.push_back(vec2(0.0,0.0));
	mesh->texCoords.push_back(vec2(1.0,0.0));
	mesh->texCoords.push_back(vec2(1.0,1.0));
	mesh->texCoords.push_back(vec2(0.0,1.0));
	mesh->texCoords.push_back(vec2(0.0,0.0));
	mesh->texCoords.push_back(vec2(1.0,0.0));
	mesh->texCoords.push_back(vec2(1.0,1.0));
	mesh->texCoords.push_back(vec2(0.0,1.0));

	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, -1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, -1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, -1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, -1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, -1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, -1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
}

void crea_cubo_ridondante(Mesh* mesh, vec2 fattori) {
	//front
	mesh->vertici.push_back(vec3(-1.0, -1.0, 1.0));	//0
	mesh->vertici.push_back(vec3(1.0, -1.0, 1.0));	//1
	mesh->vertici.push_back(vec3(1.0, 1.0, 1.0));	//2
	mesh->vertici.push_back(vec3(-1.0, 1.0, 1.0));	//3
	//back
	mesh->vertici.push_back(vec3(-1.0, -1.0, -1.0));//4
	mesh->vertici.push_back(vec3(1.0, -1.0, -1.0));	//5
	mesh->vertici.push_back(vec3(1.0, 1.0, -1.0));	//6
	mesh->vertici.push_back(vec3(-1.0, 1.0, -1.0));	//7
	//top
	mesh->vertici.push_back(vec3(-1.0, 1.0, 1.0));	//8
	mesh->vertici.push_back(vec3(1.0, 1.0, 1.0));	//9
	mesh->vertici.push_back(vec3(1.0, 1.0, -1.0));	//10
	mesh->vertici.push_back(vec3(-1.0, 1.0, -1.0));	//11
	//bottom
	mesh->vertici.push_back(vec3(-1.0, -1.0, 1.0));	//12
	mesh->vertici.push_back(vec3(1.0, -1.0, 1.0));	//13
	mesh->vertici.push_back(vec3(1.0, -1.0, -1.0));	//14
	mesh->vertici.push_back(vec3(-1.0, -1.0, -1.0));//15
	//left
	mesh->vertici.push_back(vec3(-1.0, -1.0, -1.0));//16
	mesh->vertici.push_back(vec3(-1.0, -1.0, 1.0));	//17
	mesh->vertici.push_back(vec3(-1.0, 1.0, 1.0));	//18
	mesh->vertici.push_back(vec3(-1.0, 1.0, -1.0));	//19
	//right
	mesh->vertici.push_back(vec3(1.0, -1.0, 1.0));	//20
	mesh->vertici.push_back(vec3(1.0, -1.0, -1.0));	//21
	mesh->vertici.push_back(vec3(1.0, 1.0, -1.0));	//22
	mesh->vertici.push_back(vec3(1.0, 1.0, 1.0));	//23

	for (int i = 0; i < mesh->vertici.size(); i++)
		mesh->colori.push_back(vec4(1.0,0.0,0.0,1.0));

	mesh->vertici.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));

	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);//FRONT
	mesh->indici.push_back(2); mesh->indici.push_back(3); mesh->indici.push_back(0);

	mesh->indici.push_back(20); mesh->indici.push_back(21); mesh->indici.push_back(22);//RIGHT
	mesh->indici.push_back(22); mesh->indici.push_back(23); mesh->indici.push_back(20);

	mesh->indici.push_back(7); mesh->indici.push_back(6); mesh->indici.push_back(5);//BACK
	mesh->indici.push_back(5); mesh->indici.push_back(4); mesh->indici.push_back(7);

	mesh->indici.push_back(16); mesh->indici.push_back(17); mesh->indici.push_back(18);//LEFT
	mesh->indici.push_back(18); mesh->indici.push_back(19); mesh->indici.push_back(16);

	mesh->indici.push_back(15); mesh->indici.push_back(14); mesh->indici.push_back(13);//BOT
	mesh->indici.push_back(13); mesh->indici.push_back(12); mesh->indici.push_back(15);

	mesh->indici.push_back(8); mesh->indici.push_back(9); mesh->indici.push_back(10);//TOP
	mesh->indici.push_back(10); mesh->indici.push_back(11); mesh->indici.push_back(8);

	for (int i = 0; i < 4; i++) {
		mesh->normali.push_back(normalize(vec3(0, 0, 1)));	//FRONT
	}	
	for (int i = 0; i < 4; i++) {
		mesh->normali.push_back(normalize(vec3(0, 0, -1)));	//BACK
	}	
	for (int i = 0; i < 4; i++) {
		mesh->normali.push_back(normalize(vec3(0, 1, 0)));	//TOP
	}	
	for (int i = 0; i < 4; i++) {
		mesh->normali.push_back(normalize(vec3(0, -1, 0)));	//BOTTOM
	}
	for (int i = 0; i < 4; i++) {
		mesh->normali.push_back(normalize(vec3(-1, 0, 0)));	//LEFT
	}	
	for (int i = 0; i < 4; i++) {
		mesh->normali.push_back(normalize(vec3(1, 0, 0)));	//RIGHT
	}


	int nv = mesh->vertici.size();

	mesh->indici.push_back(nv - 1);

	for (int i = 0; i < 6; i++) {
		mesh->texCoords.push_back(vec2(0.0, fattori.y));
		mesh->texCoords.push_back(vec2(fattori.x, fattori.y));
		mesh->texCoords.push_back(vec2(fattori.x, 0.0));
		mesh->texCoords.push_back(vec2(0.0, 0.0));
	}
}
void crea_piramide(Mesh* mesh)
{
	mesh->vertici.push_back(vec3(-1.0, 0.0, 1.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, 0.0,  1.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, 0.0, -1.0));
	mesh->colori.push_back(vec4(0.0, 0.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(-1.0,  0.0,  -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 0.0, 0.5));
	// Apice piramide
	mesh->vertici.push_back(vec3(0.0,1.0,0.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 1.0));


	for (int i = 0; i < mesh->vertici.size(); i++)
		mesh->normali.push_back(vec3(0.0));

	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);
	mesh->indici.push_back(0); mesh->indici.push_back(2); mesh->indici.push_back(3);

	mesh->indici.push_back(0); mesh->indici.push_back(4); mesh->indici.push_back(3);
	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(4);

	mesh->indici.push_back(3); mesh->indici.push_back(2); mesh->indici.push_back(4);
	mesh->indici.push_back(1); mesh->indici.push_back(2); mesh->indici.push_back(4);

	mesh->vertici.push_back(vec3(0.0,0.3, 0.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.3, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);

	

}
void crea_piano(Mesh* mesh, vec4 color, vec2 fattori)
{

	mesh->vertici.push_back(vec3(-0.5, 0.0, 0.5));
	mesh->colori.push_back(color);
	mesh->vertici.push_back(vec3(0.5, 0.0, 0.5));
	mesh->colori.push_back(color);
	mesh->vertici.push_back(vec3(0.5, 0.0, -0.5));
	mesh->colori.push_back(color);
	mesh->vertici.push_back(vec3(-0.5, 0.0, -0.5));
	mesh->colori.push_back(color);

	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);
	mesh->indici.push_back(0); mesh->indici.push_back(2); mesh->indici.push_back(3);

	mesh->normali.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normali.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normali.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normali.push_back(vec3(0.0, 1.0, 0.0));

	mesh->texCoords.push_back(vec2(0.0, fattori.y));
	mesh->texCoords.push_back(vec2(fattori.x, fattori.y));
	mesh->texCoords.push_back(vec2(fattori.x, 0.0));
	mesh->texCoords.push_back(vec2(0.0, 0.0));


	mesh->vertici.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);
}

void crea_piano_suddiviso(Mesh* mesh, vec4 color)
{

	int N = 32;

	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			mesh->vertici.push_back(vec3(-0.5+(float)i / N, 0.0, -0.5+(float)j / N));
			mesh->colori.push_back(color);
			mesh->normali.push_back(vec3(0.0, 1.0, 0.0));
			
		}
	}
	int cont = -1;


	

	for (i = 0; i <= pow(N, 2) - (N + 1); i++) {

		j = i % (N);

		if (j != N - 1)
		{
			mesh->indici.push_back(i);
			mesh->indici.push_back(i + 1);
			mesh->indici.push_back(i + N );

			mesh->indici.push_back(i + N + 1);
			mesh->indici.push_back(i+1);
			mesh->indici.push_back(i + N);
		}
		

	}
 

	mesh->vertici.push_back(vec3(0.0, 0.0, 0.0));
	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv-1);

 

}

void crea_sfera(Mesh* mesh, vec4 colore)
{
	vec3 centro = vec3(0.0, 0.0, 0.0);
	vec3 raggio = vec3(1.0, 1.0, 1.0);
	float s, t;
	int Stacks = 100;  //numero di suddivisioni sull'asse y
	int Slices = 100;  // numero di suddivisioni sull'asse x

	//Calc The Vertices

	//Stacks= suddivisioni lungo l'asse y
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float phi = V * pi <float>();

		// Loop Through Slices suddivisioni lungo l'asse x
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (pi <float>() * 2);

			// Calc The Vertex Positions
			float x = centro.x + raggio.x * (cosf(theta) * sinf(phi));
			float y = centro.y + raggio.y * cosf(phi);
			float z = centro.z + raggio.z * sinf(theta) * sinf(phi);

			mesh->vertici.push_back(vec3(x, y, z)),
			mesh->colori.push_back(colore);
			
			//Normale nel vertice
			mesh->normali.push_back(vec3(x, y, z));
			//coordinata di Texture
			s = U;
			t = V;
			mesh->texCoords.push_back(vec2(s, t));

		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indici.push_back(i);
		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i + Slices);


		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i);
		mesh->indici.push_back(i + 1);
	}

	mesh->vertici.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));

	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));

	
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);


}

void crea_toro(Mesh* mesh, vec4 colore)
{
	int Stacks = 30;  //numero di suddivisioni sull'asse x
	int Slices = 30;  // numero di suddivisioni sull'asse y
	float R = 1, r = 0.5;
	float s, t;


	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float phi = V * glm::pi <float>() * 2;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = (R + r * cosf(phi)) * cosf(theta);
			float y = r * sinf(phi);
			float z = (R + r * cosf(phi)) * sinf(theta);


			// Push Back Vertex Data
			mesh->vertici.push_back(vec3(x, y, z));
			mesh->colori.push_back(colore);
			//Normale nel vertice
			mesh->normali.push_back(vec3(normalize(vec3(sin(phi) * cos(theta), cos(phi), sin(theta) * sin(phi)))));

			//Coordinata di Texture
			s = U;
			t = V;
			mesh->texCoords.push_back(vec2(s, t));
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indici.push_back(i);
		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i + Slices);


		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i);
		mesh->indici.push_back(i + 1);
	}



}

void crea_cono(Mesh* mesh, vec4 colore, int Stacks, int Slices, vec2 fattori)
{
	float s, t;


	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = h * cosf(theta);
			float y = h;
			float z = h * sinf(theta);


			// Push Back Vertex Data
			mesh->vertici.push_back(vec3(x, y, z));
			mesh->colori.push_back(colore);
			//Normale nel vertice
			mesh->normali.push_back(normalize(vec3(cos(theta) / sqrt(2.0f), -1 / sqrt(2.0f), sin(theta) / sqrt(2.0f))));

			//coordinata di texture
			s = U * fattori.x;
			t = V * fattori.y;
			mesh->texCoords.push_back(vec2(s, t));

		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indici.push_back(i);
		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i + Slices);


		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i);
		mesh->indici.push_back(i + 1);
	}
	mesh->vertici.push_back(vec3(0.0, 0.3, 0.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.3, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);




}
void crea_cilindro(Mesh* mesh, vec4 colore, int Stacks, int Slices, vec2 fattori)
{

	float s, t;
	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(theta);
			float y = h;
			float z = sinf(theta);


			// Push Back Vertex Data
			mesh->vertici.push_back(vec3(x, y, z));
			mesh->colori.push_back(colore);
			//Normale nel vertice
			mesh->normali.push_back(vec3(normalize(vec3(cos(theta), 0, sin(theta)))));

			//Coordinata di texture
			s = U * fattori.x;
			t = V * fattori.y;
			mesh->texCoords.push_back(vec2(s, t));
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indici.push_back(i);
		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i + Slices);


		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i);
		mesh->indici.push_back(i + 1);
	}
	mesh->vertici.push_back(vec3(0.0, 0.3, 0.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.3, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);
}


void crea_casa(Mesh * mesh, vec4 colore_top, vec4 colore_bot) {
		mesh->vertici.push_back(vec3(2.0, -1.0, 2.0));//0
		mesh->colori.push_back(colore_top);

		mesh->vertici.push_back(vec3(2, -1, -2));//1
		mesh->colori.push_back(colore_bot);

		mesh->vertici.push_back(vec3(2, 1, -2));//2
		mesh->colori.push_back(colore_top);

		mesh->vertici.push_back(vec3(2, 1, 2));//3
		mesh->colori.push_back(colore_top);

		mesh->vertici.push_back(vec3(1.5, 1.5, 0));//4
		mesh->colori.push_back(colore_top);

		mesh->vertici.push_back(vec3(-1.5, 1.5, 0));//5
		mesh->colori.push_back(colore_top);

		mesh->vertici.push_back(vec3(-2, -1, 2));//6
		mesh->colori.push_back(colore_top);

		mesh->vertici.push_back(vec3(-2, 1, 2));//7
		mesh->colori.push_back(colore_top);

		mesh->vertici.push_back(vec3(-2, 1, -2));//8
		mesh->colori.push_back(colore_top);

		mesh->vertici.push_back(vec3(-2, -1, -2));//9
		mesh->colori.push_back(colore_bot);
		//È importante definire i vertici in senso antiorario, perchè la normale deve puntare all'esterno
		mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);
		mesh->indici.push_back(2); mesh->indici.push_back(3); mesh->indici.push_back(0);
		mesh->indici.push_back(3); mesh->indici.push_back(2); mesh->indici.push_back(4);
		mesh->indici.push_back(7); mesh->indici.push_back(3); mesh->indici.push_back(4);
		mesh->indici.push_back(4); mesh->indici.push_back(5); mesh->indici.push_back(7);

		mesh->indici.push_back(2); mesh->indici.push_back(8); mesh->indici.push_back(5);
		mesh->indici.push_back(5); mesh->indici.push_back(4); mesh->indici.push_back(2);
		mesh->indici.push_back(5); mesh->indici.push_back(8); mesh->indici.push_back(7);
		mesh->indici.push_back(0); mesh->indici.push_back(3); mesh->indici.push_back(7);
		mesh->indici.push_back(7); mesh->indici.push_back(6); mesh->indici.push_back(0);
		mesh->indici.push_back(0); mesh->indici.push_back(9); mesh->indici.push_back(6);
		mesh->indici.push_back(2); mesh->indici.push_back(9); mesh->indici.push_back(1);

		mesh->indici.push_back(9); mesh->indici.push_back(8); mesh->indici.push_back(1);

		mesh->indici.push_back(6); mesh->indici.push_back(7); mesh->indici.push_back(8);

		mesh->indici.push_back(6); mesh->indici.push_back(9); mesh->indici.push_back(8);


}

void crea_albero(Mesh* mesh, vec4 colore_top, vec4 colore_bot) {
	int Stacks_cono = 8;  //numero di suddivisioni sull'asse x
	int Slices_cono = 8;  // numero di suddivisioni sull'asse y
	int nVertici_piramide;

	int Stacks_cilindro = 15;  //numero di suddivisioni sull'asse x
	int Slices_cilindro = 15;  // numero di suddivisioni sull'asse y
	float s, t,h_base;
	h_base = 1;

	//Foglie
	/*for (int i = 0; i <= Stacks_cono; ++i) {

		float V = i / (float)Stacks_cono;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= Slices_cono; ++j) {

			float U = j / (float)Slices_cono;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = h * cosf(theta);
			float y = h;
			float z = h * sinf(theta);


			// Push Back Vertex Data
			mesh->vertici.push_back(vec3(x, y, z));
			mesh->colori.push_back(colore_top);
			//Normale nel vertice
			mesh->normali.push_back(normalize(vec3(cos(theta) / sqrt(2.0f), -1 / sqrt(2.0f), sin(theta) / sqrt(2.0f))));

			//coordinata di texture
			s = U;
			t = V;
			mesh->texCoords.push_back(vec2(s, t));

		}
	}

	for (int i = 0; i < Slices_cono * Stacks_cono + Slices_cono; ++i) {

		mesh->indici.push_back(i);
		mesh->indici.push_back(i + Slices_cono + 1);
		mesh->indici.push_back(i + Slices_cono);


		mesh->indici.push_back(i + Slices_cono + 1);
		mesh->indici.push_back(i);
		mesh->indici.push_back(i + 1);
	}*/


	//Tronco
	for (int i = 0; i <= Stacks_cilindro; ++i) {

		float V = i / (float)Stacks_cilindro;
		float h = V + 1;

		// Loop Through Slices
		for (int j = 0; j <= Slices_cilindro; ++j) {

			float U = j / (float)Slices_cilindro;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(theta);
			float y = h;
			float z = sinf(theta);


			// Push Back Vertex Data
			mesh->vertici.push_back(vec3(x, y, z));
			mesh->colori.push_back(colore_bot);
			//Normale nel vertice
			mesh->normali.push_back(vec3(normalize(vec3(cos(theta), 0, sin(theta)))));

			//Coordinata di texture
			s = U;
			t = V;
			mesh->texCoords.push_back(vec2(s, t));
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices_cilindro * Stacks_cono + Slices_cilindro; ++i) {

		mesh->indici.push_back(i);
		mesh->indici.push_back(i + Slices_cilindro + 1);
		mesh->indici.push_back(i + Slices_cilindro);


		mesh->indici.push_back(i + Slices_cilindro + 1);
		mesh->indici.push_back(i);
		mesh->indici.push_back(i + 1);
	}

	//mesh->vertici.push_back(vec3(0.0, 0.3, 0.0));
	//mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.3, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);
}

void crea_albero(Mesh* mesh) {
	vec4 colore_top = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 colore_bot = vec4(0.0, 0.0, 1.0, 1.0);
	int Stacks_cono = 8;  //numero di suddivisioni sull'asse x
	int Slices_cono = 8;  // numero di suddivisioni sull'asse y
	int nVertici_piramide;

	int Stacks_cilindro = 15;  //numero di suddivisioni sull'asse x
	int Slices_cilindro = 15;  // numero di suddivisioni sull'asse y
	float s, t, h_base;
	h_base = 1;


	//Parte della piramide
	mesh->vertici.push_back(vec3(-1.0, 0.0, 1.0));
	mesh->colori.push_back(colore_top);
	mesh->vertici.push_back(vec3(1.0, 0.0, 1.0));
	mesh->colori.push_back(colore_top);
	mesh->vertici.push_back(vec3(1.0, 0.0, -1.0));
	mesh->colori.push_back(colore_top);
	mesh->vertici.push_back(vec3(-1.0, 0.0, -1.0));
	mesh->colori.push_back(colore_top);
	// Apice piramide
	mesh->vertici.push_back(vec3(0.0, 1.0, 0.0));
	mesh->colori.push_back(colore_top);

	for (int i = 0; i < mesh->vertici.size(); i++)
		mesh->normali.push_back(vec3(0.0));

	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);
	mesh->indici.push_back(0); mesh->indici.push_back(2); mesh->indici.push_back(3);

	mesh->indici.push_back(0); mesh->indici.push_back(4); mesh->indici.push_back(3);
	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(4);

	mesh->indici.push_back(3); mesh->indici.push_back(2); mesh->indici.push_back(4);
	mesh->indici.push_back(1); mesh->indici.push_back(2); mesh->indici.push_back(4);

	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, -1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, -1.0));
	mesh->normali.push_back(vec3(0.0, 0.0, 1.0));

	mesh->texCoords.push_back(vec2(0.0, 10.0));
	mesh->texCoords.push_back(vec2(10.0, 10.0));
	mesh->texCoords.push_back(vec2(10.0, 0.0));
	mesh->texCoords.push_back(vec2(0.0, 0.0));
	mesh->texCoords.push_back(vec2(0.0, 10.0));

	//mesh->vertici.push_back(vec3(0.0, 0.3, 0.0));
	//mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.3, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);
}
