#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLHandler.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<float> > objects;

void generateObjects()
{
	vector<float> obj, obj2;

	obj.push_back(-0.8);
	obj.push_back(0.0);
	obj.push_back(1.0);

	obj.push_back(0.8);
	obj.push_back(0.0);
	obj.push_back(1.0);

	obj.push_back(0.0);
	obj.push_back(-0.8);
	obj.push_back(10.0);



	obj2.push_back(-0.8);
	obj2.push_back(-0.8);
	obj2.push_back(1.0);

	obj2.push_back(0.8);
	obj2.push_back(-0.8);
	obj2.push_back(1.0);

	obj2.push_back(0.0);
	obj2.push_back(0.0);
	obj2.push_back(10.0);

	objects.push_back(obj);
	objects.push_back(obj2);


}

int main()
{
	generateObjects();

	GLHandler glHandler;
	glHandler.run(objects);

	return 0;
}
