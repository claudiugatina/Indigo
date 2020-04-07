#version 330 core

in float viewAngleToFrag;
in vec3 colorGeomToFrag;
out vec4 FragColor;

void main()
{
	FragColor = vec4(colorGeomToFrag * viewAngleToFrag, 1.0f);
};