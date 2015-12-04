#version 410

in vec2 			UV;
in vec3 			Normal;
in vec3 			FragmentPosition;

struct 				Material
{
    vec3 			ambient;
    vec3 			diffuse;
    vec3 			specular;
    float 			shininess;
}; 
 
struct 				Light
{
	vec3 			position;
  
	vec3 			ambient;
	vec3 			diffuse;
	vec3 			specular;
};

uniform Material 	material;
uniform Light 		light;

uniform vec3 		viewPosition;
uniform sampler2D 	skinTexture;
uniform vec3 		lightPosition;

out vec4 			fragmentColor;

void main ()
{
	// ambient
    vec3 ambient = light.ambient * material.ambient;

    //diffuse
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - FragmentPosition); 
	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = light.diffuse * (diffuseFactor * material.diffuse);

	// specular
	vec3 viewDir = normalize(viewPosition - FragmentPosition);
	vec3 reflectDir = reflect(-lightDirection, normal);
	float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular =  light.specular * (material.specular * specularFactor);

	fragmentColor = vec4((ambient + diffuse + specular), 1) * texture(skinTexture, UV);
}