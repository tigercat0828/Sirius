#include "Model.h"

Model::Model() {
}

void Model::Init() {
}

void Model::Render(Shader shader) {
	for (Mesh mesh : meshes) {
		mesh.Render(shader);
	}
}

void Model::CleanUp() {
	for (Mesh mesh : meshes) {
		mesh.CleanUp();
	}
}
