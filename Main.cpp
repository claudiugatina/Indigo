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
	Position a(0, 1, 0), b(1, 0, 0), c(0, 0, 1);
	Triangle t(&b, &a, &c);
	t.calcNormal();
	Direction dir = t.m_normal;
	cout << dir.x() << ' ' << dir.y() << ' ' << dir.z();
	int x;
	cin >> x;
	cout << x;
	return 0;
	generateObjects();

	GLHandler glHandler;
	glHandler.run(objects);

	return 0;
}
