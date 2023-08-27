#pragma once
#include <vector>
#include "Mesh.h"
class Model {
public:
	std::vector<Mesh> meshes;
	Model();
	void Init();
	void Render(Shader shader);
	void CleanUp();
};

