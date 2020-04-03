#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLHandler.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Direction.h"
#include "Position.h"
#include <gtx/normal.hpp>

using namespace std;

vector<vector<float> > objects;

int segmentsBig = 100;
int segmentsSmall = 20;

float R = 50.0f;
float r = 40.0f;

const int s = 100;
float mat[s][s];

float gety(float x, float z)
{
	x += 50.0f;
	z += 50.0f;
	float xtr = float(int(x));
	float ztr = float(int(z));
	if (x - xtr < 1 - z + ztr)
	{
		float w1 = 1.0 / sqrt((x - xtr) * (x - xtr) + (z - ztr) * (z - ztr));
		float w2 = 1.0 / sqrt((x - xtr - 1) * (x - xtr - 1) + (z - ztr) * (z - ztr));
		float w3 = 1.0 / sqrt((x - xtr) * (x - xtr) + (z - ztr - 1) * (z - ztr - 1));
		return (mat[int(x)][int(z)] * w1 + mat[int(x + 1)][int(z)] * w2 + mat[int(x)][int(z + 1)] * w3) / (w1 + w2 + w3) + 2.0;
	}
	else
	{
		float w1 = 1.0 / sqrt((x - xtr) * (x - xtr) + (z - ztr) * (z - ztr));
		float w2 = 1.0 / sqrt((x - xtr - 1) * (x - xtr - 1) + (z - ztr) * (z - ztr));
		float w3 = 1.0 / sqrt((x - xtr) * (x - xtr) + (z - ztr - 1) * (z - ztr - 1));
		return (mat[int(x)][int(z)] * w1 + mat[int(x + 1)][int(z)] * w2 + mat[int(x)][int(z + 1)] * w3) / (w1 + w2 + w3) + 2.0;
	}
	return mat[int(x)][int(z)] + 2.0;
}


vector<float> torrPoint(int i, int j)
{
		float angleBig = (6.283f / float(segmentsBig)) * float(i);
		float xBig = sin(angleBig) * R;
		float yBig = 25.0f;
		float zBig = cos(angleBig) * R;

		float angleSmall = (6.283f / float(segmentsSmall)) * float(j);
		float xSmall = sin(angleBig) * (R + sin(angleSmall) * r);
		float ySmall = yBig + cos(angleSmall) * r;
		float zSmall = cos(angleBig) * (R + sin(angleSmall) * r);

		vector<float> res;

		res.push_back(xSmall);
		res.push_back(ySmall);
		res.push_back(zSmall);

		return res;
}

int sphereResolution = 100;
float radius = 15.0f;

glm::vec3 spherePoint(int i, int j)
{
	float anglex = 6.28f / float(sphereResolution) * float(j);
	float angley = 6.28f / float(sphereResolution) * float(i);

	glm::vec3 res;

	res.x = radius * sin(anglex) * sin(angley);
	res.y = radius * cos(anglex);
	res.z = radius * sin(anglex) * cos(angley);

	return res;
}

void pushSquare(vector<float>& res, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 norm123, glm::vec3 norm234, glm::vec3 rgb)
{
	float ra = (rand() % 20) / 100.0;
	rgb -= ra;
	vector<float> toPush = {
		p1.x, p1.y, p1.z, rgb.x, rgb.y, rgb.z, norm123.x, norm123.y, norm123.z,
		p2.x, p2.y, p2.z, rgb.x, rgb.y, rgb.z, norm123.x, norm123.y, norm123.z,
		p3.x, p3.y, p3.z, rgb.x, rgb.y, rgb.z, norm123.x, norm123.y, norm123.z,

		p2.x, p2.y, p2.z, rgb.x, rgb.y, rgb.z, norm234.x, norm234.y, norm234.z,
		p3.x, p3.y, p3.z, rgb.x, rgb.y, rgb.z, norm234.x, norm234.y, norm234.z,
		p4.x, p4.y, p4.z, rgb.x, rgb.y, rgb.z, norm234.x, norm234.y, norm234.z,
	};

	res.insert(res.end(), toPush.begin(), toPush.end());
}

vector<float> generateSphere()
{
	vector<float> res;
	for (int i = 0; i < sphereResolution; ++i)
	{
		for (int j = 0; j < sphereResolution; ++j)
		{
			glm::vec3 p1 = spherePoint(i, j), p2 = spherePoint(i, j + 1), p3 = spherePoint(i + 1, j), p4 = spherePoint(i + 1, j + 1);
			glm::vec3 norm123 = glm::triangleNormal(p1, p2, p3);
			glm::vec3 norm234 = glm::triangleNormal(p2, p3, p4);
			glm::vec3 rgb(1.0, 0.2, 1.0);

			pushSquare(res, p1, p2, p3, p4, norm123, norm234, rgb);

		}
	}
	return res;
}

void generateObjects()
{
	vector<float> obj, obj2;
	vector<float> obj3 = { 
		-0.5, 0.0, 0.0, 1.0, 1.0, 1.0,
		0.5, 0.0, 0.0, 1.0, 1.0, 1.0,
		0.0, 0.5, -5.0, 1.0, 1.0, 1.0,
	};

	vector<float> obj4 = {
		-0.5, 0.5, 0.0, 0.0, 0.0, 0.0,
		0.5, 0.5, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, -5.0, 0.0, 0.0, 0.0,
	};

	obj.push_back(-0.8);
	obj.push_back(0.0);
	obj.push_back(0.0);

	obj.push_back(0.8);
	obj.push_back(0.0);
	obj.push_back(0.0);

	obj.push_back(0.0);
	obj.push_back(-0.8);
	obj.push_back(0.0);



	obj2.push_back(-0.8);
	obj2.push_back(-0.8);
	obj2.push_back(0.0);

	obj2.push_back(0.8);
	obj2.push_back(-0.8);
	obj2.push_back(0.0);

	obj2.push_back(0.0);
	obj2.push_back(0.0);
	obj2.push_back(0.0);

	//objects.push_back(obj);
	//objects.push_back(obj2);
	//objects.push_back(obj4);
	//objects.push_back(obj3);
	mat[0][0] = -0.5;
	for (int i = 1; i < s; ++i)
	{
		mat[i][0] = mat[i - 1][0] + float(rand() % 10) * 0.1f - 0.45f;
	}
	for (int j = 1; j < s; ++j)
	{
		mat[0][j] = mat[0][j - 1] + float(rand() % 10) * 0.1f - 0.45f;
	}
	for (int i = 1; i < s; ++i)
	{
		for (int j = 1; j < s; ++j)
		{
			mat[i][j] = (mat[i - 1][j] + mat[i][j - 1]) / 2.0f + float(rand() % 10) * 0.1f - 0.45f;
		}
	}

	vector<float> map;
	double peak = 2.0;
	for (int i = 0; i < s - 1; ++i)
	{
		for (int j = 0; j < s - 1; ++j)
		{
			float y1 = mat[i][j], y2 = mat[i][j + 1], y3 = mat[i + 1][j], y4 = mat[i + 1][j + 1];
			
			i -= s / 2;
			j -= s / 2;
			float x1 = i, x2 = i, x3 = i + 1, x4 = i + 1;
			float z1 = j, z2 = j + 1, z3 = j, z4 = j + 1;
			i += s / 2;
			j += s / 2;
			float r = 1.0, g = 0.2, b = 1.0;
			glm::vec3 normal123 = glm::triangleNormal(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2), glm::vec3(x3, y3, z3));
			if (normal123.y < 0.0)
				normal123 = -normal123;
			glm::vec3 normal234 = glm::triangleNormal(glm::vec3(x4, y4, z4), glm::vec3(x2, y2, z2), glm::vec3(x3, y3, z3));
			if (normal234.y < 0.0)
				normal234 = -normal234;
			vector<float> toPush = {
				x1, y1, z1, r, g, b, normal123.x, normal123.y, normal123.z,
				x2, y2, z2, r, g, b, normal123.x, normal123.y, normal123.z,
				x3, y3, z3, r, g, b, normal123.x, normal123.y, normal123.z,
				x2, y2, z2, r, g, b, normal234.x, normal234.y, normal234.z,
				x3, y3, z3, r, g, b, normal234.x, normal234.y, normal234.z,
				x4, y4, z4, r, g, b, normal234.x, normal234.y, normal234.z,
			};
			
			map.insert(map.end(), toPush.begin(), toPush.end());
		}
	}

	vector<float> torrus;

	for (int i = 0; i < segmentsBig; ++i)
	{
		
		for (int j = 0; j < segmentsSmall; ++j)
		{
			vector<vector<float> > v;
			v.push_back(torrPoint(i, j));
			v.push_back(torrPoint(i, j + 1));
			v.push_back(torrPoint(i + 1, j));
			v.push_back(torrPoint(i + 1, j + 1));

			float r = 1.0, g = 0.2, b = 1.0;

			glm::vec3 normal123 = glm::triangleNormal(glm::vec3(v[0][0], v[0][1], v[0][2]), glm::vec3(v[1][0], v[1][1], v[1][2]), glm::vec3(v[2][0], v[2][1], v[2][2]));
			//if (normal123.y > 0.0)
				//normal123 = -normal123;

			glm::vec3 normal234 = glm::triangleNormal(glm::vec3(v[2][0], v[2][1], v[2][2]), glm::vec3(v[1][0], v[1][1], v[1][2]), glm::vec3(v[3][0], v[3][1], v[3][2]));
		//	if (normal234.y > 0.0)
			//	normal234 = -normal234;

			for (auto& vec : v)
			{
				vec.push_back(r);
				vec.push_back(g);
				vec.push_back(b);
			}

			for (int k = 0; k < 3; ++k)
			{
				torrus.insert(torrus.end(), v[k].begin(), v[k].end());
				torrus.push_back(normal123.x);
				torrus.push_back(normal123.y);
				torrus.push_back(normal123.z);
			}

			for (int k = 1; k < 4; ++k)
			{
				torrus.insert(torrus.end(), v[k].begin(), v[k].end());
				torrus.push_back(normal234.x);
				torrus.push_back(normal234.y);
				torrus.push_back(normal234.z);
			}

		}
	}

	objects.push_back(map);
	objects.push_back(torrus);
	objects.push_back(generateSphere());

}

int main()
{
	
	generateObjects();

	GLHandler glHandler;
	glHandler.run(objects);

	return 0;
}
