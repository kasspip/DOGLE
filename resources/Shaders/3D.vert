#version 410

uniform mat4 matrix_local;
uniform mat4 matrix_world;
uniform mat4 matrix_view;
uniform mat4 matrix_projection;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec2 vertex_texture;

out vec2 texture_coordinates;
out vec3 vert_color;
out vec3 position_eye;
out vec3 normal_eye;

void main()
{
	texture_coordinates = vertex_texture;
	vert_color = vertex_color;

	position_eye = vec3(matrix_view * matrix_world * matrix_local * vec4 (vertex_position, 1.0));	
	normal_eye = vec3(matrix_view * matrix_world * matrix_local * vec4(vertex_normal, 0.0));

	gl_Position = matrix_projection * matrix_view * matrix_world * matrix_local * vec4 (vertex_position, 1.0);
}
