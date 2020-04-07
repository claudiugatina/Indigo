#version 330 core
#define PI 3.1415926535897932384626433832795
layout (location = 0) in vec2 ind;
layout (location = 1) in vec3 colorIn;

uniform vec3 cameraPos;
uniform mat4 MVP;
uniform vec3 object_position;

uniform float resolution_big;
uniform float resolution_small;
uniform float r;
uniform float R;

out vec3 colorVerToGeom;
out vec3 aPos;

vec3 torPoint(vec2 ind)
{
	vec3 res;
	float angleBig = 2 * PI / resolution_big * ind.x;
	float xBig = sin(angleBig) * R;
	float yBig = 0.0f;
	float zBig = cos(angleBig) * R;

	float angleSmall = 2 * PI / resolution_small * ind.y;
	res.x = sin(angleBig) * (R + sin(angleSmall) * r);
	res.y = yBig + cos(angleSmall) * r;
	res.z = cos(angleBig) * (R + sin(angleSmall) * r);

	return res;
}

void main()
{
	aPos = torPoint(ind);
	vec3 vertexToCamera = cameraPos - aPos - object_position;
	colorVerToGeom = colorIn; // * viewCos;
    gl_Position = MVP * vec4(aPos, 1.0);
}