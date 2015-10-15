#version 410

uniform sampler2D skinTexture;

in vec2 UV;

out vec4 fragmentColor;

void main ()
{
	vec4 texel = texture(skinTexture, UV);
	fragmentColor = texel;
}