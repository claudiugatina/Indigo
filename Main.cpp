#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLHandler.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Direction.h"
#include "Position.h"
#include "Triangle.h"

using namespace std;

vector<vector<float> > objects;

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
	vector<float> map;
	for (float z = -15.0; z <= 15.0; z += 0.5)
	{
		for (float x = -15; x <= 15.0; x += 0.5)
		{
			float y = float(rand() % 100) * 0.005 - 0.5;

			map.push_back(x);
			map.push_back(y);
			map.push_back(z);
			map.push_back(x);
			map.push_back(y);
			map.push_back(z);
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
