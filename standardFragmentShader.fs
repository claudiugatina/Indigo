#version 330 core

in float viewAngle;
in vec3 colorOut;
out vec4 FragColor;

void main()
{
	FragColor = vec4(colorOut * viewAngle, 1.0f);
};