#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 colorIn;
layout (location = 2) in vec3 normal;

uniform vec3 cameraPos;
uniform mat4 MVP; // model, view, projection
uniform vec3 object_position;
out vec3 colorOut;
out float viewAngle;

void main()
{
	vec3 vertexToCamera = cameraPos - aPos - object_position;
	viewAngle = abs(dot(normalize(vertexToCamera), normalize(normal)));
	colorOut = colorIn; // * viewCos;
    gl_Position = MVP * vec4(aPos, 1.0);
}