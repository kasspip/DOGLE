#version 410

in vec2 UV;
in vec3 Normal;

uniform sampler2D skinTexture;
uniform vec3 lightPos;

out vec4 fragmentColor;

void main ()
{
	vec4 texel = texture(skinTexture, UV);
	fragmentColor = texel;
}