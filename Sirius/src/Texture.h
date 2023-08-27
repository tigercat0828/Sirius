#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Texture {
public:
	Texture();
	Texture(const char* path, const char* name, bool defaultParams = true);

	void Generate();
	void Load(bool filp = true);
	void SetFilters(GLenum all);
	void SetFilters(GLenum mag, GLenum min);
	void SetWrap(GLenum all);
	void SetWrap(GLenum s, GLenum t);

	void Bind();
	
	GLuint tex;
	const char* name;
	int id;
private:
	static int currentId;
	const char* path;
	int width;
	int height;
	int nChannels;
};

