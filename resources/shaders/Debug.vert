#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;

void main () 
{
	UV = vertexUV;
	gl_Position = vec4 (vertexPosition, 1.0);
}