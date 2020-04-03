#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 colorIn;

uniform mat4 MVP; // model, view, projecion
uniform float time;
out vec3 colorVerToGeom;

void main()
{
	vec3 wavedPos = vec3(aPos.x, aPos.y + 5.0 * sin(-time*10 + 0.3 * sqrt(aPos.x * aPos.x + aPos.z * aPos.z)), aPos.z);
	colorVerToGeom = colorIn; 
    gl_Position = MVP * vec4(wavedPos, 1.0);
}