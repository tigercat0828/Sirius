#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define DEBUG


class Shader {

public:
	GLuint Id;
	Shader(const char* vFileName, const char* fFileName);
	void Activate();
	void SetMat4(const std::string& para_name, glm::mat4 value);
	void SetInt(const std::string& para_name, int value);
	void SetFloat(const std::string& para_name, float value);
	void SetVec3(const std::string& para_name, glm::vec3 value);
	
private:
	std::string	LoadShaderSource(const char* fileName);
	GLuint CompileShader(const char* fileName, GLenum type);
	void TipUniformNotFound(const std::string& para_name);
};

