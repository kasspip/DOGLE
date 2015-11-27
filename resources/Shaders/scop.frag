#version 410

uniform int texture_mode;
uniform sampler2D basic_texture;
uniform mat4 matrix_view;
uniform float blend_coef;

in vec3 vert_color;
in vec2 texture_coordinates;
in vec3 position_eye;
in vec3 normal_eye;

out vec4 frag_color;

// light properties
vec3 L_pos_world  = vec3(0.0, 0.0, 5.0);
vec3 L_spec = vec3(1.0, 1.0, 1.0);
vec3 L_diff = vec3(0.7, 0.7, 0.7);
vec3 L_amb = vec3(0.5, 0.5, 0.5);

// surface material
vec3 M_spec = vec3(0.5, 0.5, 0.5);
vec3 M_diff = vert_color;
vec3 M_amb = vec3(1, 1, 1);
float spec_power = 100.0;
vec4 material;

void main()
{
	// calculate ambiant intensity
	vec3 I_amb = L_amb * M_amb;

	// calculate diffuse intensity
	vec3 light_position_eye = vec3 (matrix_view * vec4 (L_pos_world, 1.0));
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	vec3 direction_to_light_eye = normalize (distance_to_light_eye);
	float dot_prod = dot (direction_to_light_eye, normal_eye);
	dot_prod = max(dot_prod, 0.0);
	vec3 I_diff = L_diff * M_diff * dot_prod;

	// calculate specular intensity
	vec3 reflection_eye = reflect (-direction_to_light_eye, normal_eye);
	vec3 surface_to_viewer_eye = normalize (-position_eye);
	float dot_prod_specular = dot (reflection_eye, surface_to_viewer_eye);
	dot_prod_specular = max(dot_prod_specular, 0.0);
	float specular_factor = pow(dot_prod_specular, spec_power);
	vec3 I_spec = L_spec * M_spec * specular_factor;

	material = vec4(I_spec + I_diff + I_amb, 1.0);
	
	vec4 texel = texture(basic_texture, texture_coordinates);
	frag_color = mix(vec4(vert_color, 1.0), texel, blend_coef) * material;
}
