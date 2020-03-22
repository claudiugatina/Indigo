#version 330 core

in float viewAngle;
out vec4 FragColor;
in vec3 colorOut;

void main()
{
	FragColor = vec4(colorOut * viewAngle, 1.0f);
};