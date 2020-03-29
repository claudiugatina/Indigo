#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

uniform vec3 cameraPos;
in vec3 colorVerToGeom[];
out vec3 colorGeomToFrag;
out float viewAngleToFrag;

void main()
{
	// cross product for triangle normal
	vec3 V = gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz;
	vec3 W = gl_in[0].gl_Position.xyz - gl_in[2].gl_Position.xyz;
	vec3 normal = normalize(vec3(
		V.y * W.z - V.z * W.y,
		V.z * W.x - V.x * W.z,
		V.x * W.y - V.y * W.x
	));
	
	for(int i = 0; i < 3; ++i)
	{
		gl_Position = gl_in[i].gl_Position;
		vec3 vertexToCamera = cameraPos - gl_Position.xyz;
		viewAngleToFrag = abs(dot(normalize(vertexToCamera), normal));
		colorGeomToFrag = colorVerToGeom[i];
		EmitVertex();
	}
	EndPrimitive();

};