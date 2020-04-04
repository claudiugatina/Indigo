#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 colorIn;

uniform mat4 MVP; // model, view, projecion
uniform float time;
out vec3 colorVerToGeom;
out vec3 wavedPos;

void main()
{
	wavedPos = vec3(aPos.x, aPos.y + 1.0 * sin(-time*10 + 0.3 * sqrt(2000 * aPos.x * aPos.x + 2000 * aPos.z * aPos.z)), aPos.z);
	colorVerToGeom = colorIn; 
    gl_Position = MVP * vec4(wavedPos, 1.0);
}