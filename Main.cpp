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

int sphereResolution = 100;
float radius = 15.0f;

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

	

	objects.push_back(map);
}

int main()
{
	
	generateObjects();
	GLHandler glHandler;
	glHandler.run(objects);

	return 0;
}
