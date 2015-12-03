#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

out vec2 UV;
out vec3 FragmentPosition;
out vec3 Normal;

void main () 
{
	gl_Position = Projection * View * Transform * vec4 (vertexPosition, 1.0);

	UV = vertexUV;
	Normal = mat3(transpose(inverse(Transform))) * vertexNormal;
	FragmentPosition = vec3(Transform * vec4(vertexPosition, 1.0f));
}
