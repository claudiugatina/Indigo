#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 colorIn;
layout (location = 2) in vec3 normal;

uniform vec3 cameraPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 colorOut;
out float viewAngle;

void main()
{
	vec3 vertexToCamera = cameraPos - aPos;
	viewAngle = abs(dot(normalize(vertexToCamera), normalize(normal)));
	colorOut = colorIn; // * viewCos;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}