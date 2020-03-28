#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 colorIn;
layout (location = 2) in vec3 normal;

//uniform vec3 cameraDir;
//uniform vec3 cameraRot;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
out vec3 colorOut;

void main()
{
	vec3 wavedPos = vec3(aPos.x, aPos.y + 2 * sin(time + 0.1 * aPos.x * aPos.y), aPos.z);
	colorOut = colorIn; 
    gl_Position = projection * view * model * vec4(wavedPos, 1.0);
}