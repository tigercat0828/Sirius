#pragma once
#include "Cube.hpp"
#include "Light.h"
class Lamp : public Cube {
public : 
	glm::vec3 lightColor;
	PointLight pointLight;

	Lamp(glm::vec3 lightColor,
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular,
		glm::vec3 position,
		glm::vec3 size
		) :
		lightColor(lightColor),
		pointLight({position, ambient, diffuse, specular}),
		Cube(Material::white_plastic, position, size) {}
	void Render(Shader shader) {
		shader.SetVec3("lightColor", lightColor);
		Cube::Render(shader);
	}
};