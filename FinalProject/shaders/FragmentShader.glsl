#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPosition;

//uniform sampler2D texture1;
//uniform sampler2D texture2;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * material.ambient;
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;
	
	// specular
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.specular;
	
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
//	FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}
