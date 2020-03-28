#version 330 core

in float viewAnglez;
out vec4 FragColor;
in vec3 colorOutz;

void main()
{
	FragColor = vec4(colorOutz * viewAnglez, 1.0f);
};