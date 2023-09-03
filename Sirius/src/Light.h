#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

struct PointLight {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	void Render(Shader shader) {
		std::string name = "pointLight";
		shader.SetVec3(name + ".position", position);
		shader.SetVec3(name + ".ambient", ambient);
		shader.SetVec3(name + ".diffuse", diffuse);
		shader.SetVec3(name + ".specular", specular);
	}
};

