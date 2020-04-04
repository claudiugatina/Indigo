#version 330 core

out vec4 FragColor;
in float viewAngleToFrag;
in vec3 colorGeomToFrag;

// TODO: repair colours changing with the direction of the camera

void main()
{
	FragColor = vec4(colorGeomToFrag * viewAngleToFrag, 1.0f);
};