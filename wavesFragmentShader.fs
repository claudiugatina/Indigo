#version 330 core

in float viewAngleToFrag;
out vec4 FragColor;
in vec3 colorGeomToFrag;

// TODO: repair colours changing with the direction of the camera

void main()
{
	FragColor = vec4(colorGeomToFrag * viewAngleToFrag, 1.0f);
};