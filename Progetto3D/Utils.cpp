#include "Utils.h"
#include "Strutture.h"

extern int pval;
extern vector<BoundingBox> BoundingBoxOBJVector;
////////////////////////////////////// Disegna geometria //////////////////////////////////////
//Per Curve di hermite
#define PHI0(t)  (2.0*t*t*t-3.0*t*t+1)
#define PHI1(t)  (t*t*t-2.0*t*t+t)
#define PSI0(t)  (-2.0*t*t*t+3.0*t*t)
#define PSI1(t)  (t*t*t-t*t)
float dx(int i, float* t, float Tens, float Bias, float Cont, Mesh* Fig)
{
	if (i == 0)
		return  0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (Fig->CP[i + 1].x - Fig->CP[i].x) / (t[i + 1] - t[i]);
	if (i == Fig->CP.size() - 1)
		return  0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (Fig->CP[i].x - Fig->CP[i - 1].x) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1 - Tens) * (1 + Bias) * (1 + Cont) * (Fig->CP.at(i).x - Fig->CP.at(i - 1).x) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (Fig->CP.at(i + 1).x - Fig->CP.at(i).x) / (t[i + 1] - t[i]);
	else
		return  0.5 * (1 - Tens) * (1 + Bias) * (1 - Cont) * (Fig->CP.at(i).x - Fig->CP.at(i - 1).x) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 + Cont) * (Fig->CP.at(i + 1).x - Fig->CP.at(i).x) / (t[i + 1] - t[i]);
}
float dy(int i, float* t, float Tens, float Bias, float Cont, Mesh* Fig)
{
	if (i == 0)
		return 0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (Fig->CP.at(i + 1).y - Fig->CP.at(i).y) / (t[i + 1] - t[i]);
	if (i == Fig->CP.size() - 1)
		return  0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (Fig->CP.at(i).y - Fig->CP.at(i - 1).y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1 - Tens) * (1 + Bias) * (1 + Cont) * (Fig->CP.at(i).y - Fig->CP.at(i - 1).y) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (Fig->CP.at(i + 1).y - Fig->CP.at(i).y) / (t[i + 1] - t[i]);
	else
		return  0.5 * (1 - Tens) * (1 + Bias) * (1 - Cont) * (Fig->CP.at(i).y - Fig->CP.at(i - 1).y) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 + Cont) * (Fig->CP.at(i + 1).y - Fig->CP.at(i).y) / (t[i + 1] - t[i]);
}

void InterpolazioneHermite(float* t, Mesh* Fig, vec4 color_top, vec4 color_bot)
{
	float p_t = 0, p_b = 0, p_c = 0, x, y;
	float passotg = 1.0 / (float)(pval - 1);
	float passotg0 = 1.0 / 10.0;
	float tg = 0, tgmapp, ampiezza;
	int i = 0;
	int is = 0; //indice dell'estremo sinistro dell'intervallo [t(i),t(i+1)] a cui il punto tg
				//appartiene

	Fig->vertici.push_back(vec3(-1.0, 5.0, 0.0));
	//Fig->colors.push_back(vec4(1.0, 1.0, 0.0, 1.0));
	Fig->colori.push_back(color_bot);




	for (tg = 0; tg <= 1; tg += passotg)
	{
		if (tg > t[is + 1]) is++;

		ampiezza = (t[is + 1] - t[is]);
		tgmapp = (tg - t[is]) / ampiezza;

		x = Fig->CP[is].x * PHI0(tgmapp) + dx(is, t, p_t, p_b, p_c, Fig) * PHI1(tgmapp) * ampiezza + Fig->CP[is + 1].x * PSI0(tgmapp) + dx(is + 1, t, p_t, p_b, p_c, Fig) * PSI1(tgmapp) * ampiezza;
		y = Fig->CP[is].y * PHI0(tgmapp) + dy(is, t, p_t, p_b, p_c, Fig) * PHI1(tgmapp) * ampiezza + Fig->CP[is + 1].y * PSI0(tgmapp) + dy(is + 1, t, p_t, p_b, p_c, Fig) * PSI1(tgmapp) * ampiezza;
		Fig->vertici.push_back(vec3(x, y, 0.0));
		Fig->colori.push_back(color_top);
	}


}


BoundingBox calcolaBoundingBox(Mesh* fig) {
	vec3 min = fig->vertici.at(0);
	vec3 max = fig->vertici.at(0);
	vec3 topLeftCorner, bottomRightCorner;
	for (vec3 vertice : fig->vertici) {
		if (min.x > vertice.x) min.x = vertice.x;
		if (min.y > vertice.y) min.y = vertice.y;
		if (min.z > vertice.z) min.z = vertice.z;
		if (max.x < vertice.x) max.x = vertice.x;
		if (max.y < vertice.y) max.y = vertice.y;
		if (max.z < vertice.z) max.z = vertice.z;
	}
	//Controllo se alcune coordinate sono identiche (nel caso di un piano, ad esempio)
	if (max.x == min.x) {
		max.x += 2.5;
		min.x -= 2.5;
	}
	if (max.y == min.y) {
		max.y += 2.5;
		min.y -= 2.5;
	}
	if (max.z == min.z) {
		max.z += 2.5;
		min.z -= 2.5;
	}
	topLeftCorner.x = min.x;
	topLeftCorner.y = max.y;
	topLeftCorner.z = max.z;

	bottomRightCorner.x = max.x;
	bottomRightCorner.y = min.y;
	bottomRightCorner.z = min.z;
	
	

	//pair<vec4, vec4> pair = make_pair(vec4(topLeftCorner, 1.0), vec4(bottomRightCorner, 1.0));
	vector<vec4> boundingBox;
	boundingBox.push_back(vec4(topLeftCorner, 1.0));
	boundingBox.push_back(vec4(bottomRightCorner, 1.0));

	BoundingBox box;
	box.TL = vec4(topLeftCorner, 1.0);
	box.BR = vec4(bottomRightCorner, 1.0);
	return box;
}

BoundingBox calcolaBoundingBoxOBJ(vector<MeshObj> meshObjVector) {
	string LOG_TAG = "calcolaBoundingBoxOBJ";
	vec3 min = meshObjVector.at(0).vertici.at(0);
	vec3 max = meshObjVector.at(0).vertici.at(0);

	vec3 topLeftCorner, bottomRightCorner;
	for (MeshObj fig : meshObjVector) {
		for (vec3 vertice : fig.vertici) {
			if (min.x > vertice.x) min.x = vertice.x;
			if (min.y > vertice.y) min.y = vertice.y;
			if (min.z > vertice.z) min.z = vertice.z;
			if (max.x < vertice.x) max.x = vertice.x;
			if (max.y < vertice.y) max.y = vertice.y;
			if (max.z < vertice.z) max.z = vertice.z;
		}
		//Controllo se alcune coordinate sono identiche (nel caso di un piano, ad esempio)
		if (abs(max.x - min.x)<5) {
			logger(LOG_TAG, "X troppo piccole\n");
			max.x += 2.5;
			min.x -= 2.5;
		}
		if (abs(max.y- min.y)<5) {
			logger(LOG_TAG, "Y troppo piccole\n");
			max.y += 2.5;
			min.y -= 2.5;
		}
		if (abs(max.z - min.z)<5) {
			logger(LOG_TAG, "Z troppo piccole\n");
			max.z += 2.5;
			min.z -= 2.5;
		}
		topLeftCorner.x = min.x;
		topLeftCorner.y = max.y;
		topLeftCorner.z = max.z;

		bottomRightCorner.x = max.x;
		bottomRightCorner.y = min.y;
		bottomRightCorner.z = min.z;

	}



	//pair<vec4, vec4> pair = make_pair(vec4(topLeftCorner, 1.0), vec4(bottomRightCorner, 1.0));
	vector<vec4> boundingBox;
	boundingBox.push_back(vec4(topLeftCorner, 1.0));
	boundingBox.push_back(vec4(bottomRightCorner, 1.0));

	BoundingBox box;
	box.TL = vec4(topLeftCorner, 1.0);
	box.BR = vec4(bottomRightCorner, 1.0);
	return box;
}

//TODO fare che parta dalla posizione di scena 1 invece che 2  (togliere quella sfera)
bool checkCollisionCamera(vector<Mesh> Scena, vec4 cameraPosition) {
	Mesh mesh;
	bool collisionX, collisionY, collisionZ;
	//printf("Coordinate di telecamera %f %f %f\n", cameraPosition.x, cameraPosition.y, cameraPosition.z);
	for (int i = 1; i < Scena.size(); i++) {
		mesh = Scena[i];
		//printf("Controllo hitbox di %s\n", mesh.nome.c_str());
		collisionX = mesh.AABB.BR.x >= cameraPosition.x &&
			mesh.AABB.TL.x <= cameraPosition.x;
		collisionY = mesh.AABB.BR.y <= cameraPosition.y &&
			mesh.AABB.TL.y >= cameraPosition.y;
		collisionZ = mesh.AABB.BR.z <= cameraPosition.z &&
			mesh.AABB.TL.z >= cameraPosition.z;
		if (collisionX && collisionY && collisionZ) {
		printf("\n----------------------COLLISIONE------------------------\n");
		printf("%s  : %f, %f, %f--- %f, %f, %f\n", mesh.nome.c_str(), mesh.AABB.TL.x, mesh.AABB.TL.y, mesh.AABB.TL.z, mesh.AABB.BR.x, mesh.AABB.BR.y, mesh.AABB.BR.z);
		printf("CAMERA  : %f, %f, %f\n", cameraPosition.x, cameraPosition.y, cameraPosition.z);
		return true;
		}
	}
	for (BoundingBox bbobj : BoundingBoxOBJVector) {
		//printf("BBOBJ: : %f, %f, %f--- %f, %f, %f\n", bbobj.TL.x, bbobj.TL.y, bbobj.TL.z, bbobj.BR.x, bbobj.BR.y, bbobj.BR.z);
		//printf("Controllo hitbox di %s\n", mesh.nome.c_str());
		collisionX = bbobj.BR.x >= cameraPosition.x &&
			bbobj.TL.x <= cameraPosition.x;
		collisionY = bbobj.BR.y <= cameraPosition.y &&
			bbobj.TL.y >= cameraPosition.y;
		collisionZ = bbobj.BR.z <= cameraPosition.z &&
			bbobj.TL.z >= cameraPosition.z;
		if (collisionX && collisionY && collisionZ) {
			printf("\n----------------------COLLISIONE con OBJ------------------------\n");
			printf("MESH  : %f, %f, %f--- %f, %f, %f\n", bbobj.TL.x, bbobj.TL.y, bbobj.TL.z, bbobj.BR.x, bbobj.BR.y, bbobj.BR.z);
			printf("CAMERA  : %f, %f, %f\n", cameraPosition.x, cameraPosition.y, cameraPosition.z);
			return true;
			break;
		}
	}
	
	//return collisionX && collisionY && collisionZ;
	return false;
}

void logger(string TAG, string text) {
	printf("LOG\t%s:\t%s\n", TAG.c_str(), text.c_str());
}