#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

uniform vec3 cameraPos;
uniform vec3 object_position;
in vec3 colorVerToGeom[];
in vec3 wavedPos[];
out vec3 colorGeomToFrag;
out float viewAngleToFrag;

void main()
{
	// cross product for triangle normal
	
	vec3 V = wavedPos[0] - wavedPos[1];
	vec3 W = wavedPos[0] - wavedPos[2];
	vec3 normal = normalize(vec3(
		V.y * W.z - V.z * W.y,
		V.z * W.x - V.x * W.z,
		V.x * W.y - V.y * W.x
	));
	
	for(int i = 0; i < 3; ++i)
	{
		gl_Position = gl_in[i].gl_Position;
		vec3 vertexToCamera = cameraPos - wavedPos[i] - object_position;
		viewAngleToFrag = abs(dot(normalize(vertexToCamera), normal));
		colorGeomToFrag = colorVerToGeom[i];
		EmitVertex();
	}
	EndPrimitive();

};