#version 410

in vec2 UV;
in vec3 Normal;
in vec3 FragmentPosition;

uniform sampler2D skinTexture;
uniform vec3 lightPosition;
uniform vec3 lightColor;

out vec4 fragmentColor;

void main ()
{

	float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - FragmentPosition); 
	
	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = diffuseFactor * lightColor;
	
	fragmentColor = vec4((ambient + diffuse), 1) * texture(skinTexture, UV);
}