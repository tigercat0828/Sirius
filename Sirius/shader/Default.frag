#version 330 core

struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
struct PointLight{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fFragPos;
in vec3 fNormal;
in vec2 fTexCoord;
out vec4 FragColor;

uniform Material material;
uniform PointLight pointLight;
uniform vec3 ViewPos;

vec3 CalcPointLight(vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap){ 
	// ambient
	//vec3 ambient = light.ambient * material.ambient;
	vec3 ambient = pointLight.ambient * diffuseMap;
	// diffuse
	vec3 norm = normalize(fNormal);
	vec3 lightDir = normalize(pointLight.position - fFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = pointLight.diffuse * (diff * diffuseMap);

	// specular
	// vec3 viewDir = normalize(ViewPos - fFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128 );
	vec3 specular = pointLight.specular * ( spec * specularMap);

	return vec3(ambient + diffuse + specular);

}

void main() {
	vec3 norm = normalize(fNormal);
	vec3 viewDir = normalize(ViewPos - fFragPos);
	vec3 diffuseMap = vec3(texture(material.diffuse, fTexCoord));
	vec3 specularMap = vec3(texture(material.specular, fTexCoord));

	FragColor = vec4(CalcPointLight(norm, viewDir, diffuseMap, specularMap), 1.0f);
}