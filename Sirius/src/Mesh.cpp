#include "Mesh.h"

std::vector<Vertex> Vertex::genList(float* vertices, int noVertices) {
	
	std::vector<Vertex> result(noVertices);

	int stride = sizeof(Vertex) / sizeof(float);
	for (int i = 0; i < noVertices; i++) {
		result[i].position = glm::vec3(
			vertices[i * stride + 0],
			vertices[i * stride + 1],
			vertices[i * stride + 2]
		);
		result[i].texCoord = glm::vec2(
			vertices[i * stride + 3],
			vertices[i * stride + 4]
		);
	}
	return result;
}

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
	vertices(vertices), indices(indices), textures(textures)
{
	Setup();
}

void Mesh::Render(Shader shader) {
	// texture
	for (unsigned int i = 0; i < textures.size(); i++) {
		shader.SetInt(textures[i].name, textures[i].id);
		glActiveTexture(GL_TEXTURE0 + i);
		textures[i].Bind();
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// unbind all
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::CleanUp() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Setup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	
	glBindVertexArray(0);
}
