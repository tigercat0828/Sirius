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
	std::string sName;
	Shader(std::string name ,const char* vFileName, const char* fFileName);
	void Activate();
	void SetMat4(const std::string& name, glm::mat4 value);
	void SetInt(const std::string& name, int value);
	void SetVec3(const std::string& name, glm::vec3 value);
	void SetVec4(const std::string& name, glm::vec4 value);
	void SetFloat(const std::string& name, float value);
	void SetFloat3(const std::string& name, float v1, float v2, float v3);
	void SetFloat4(const std::string& name, float v1, float v2, float v3, float v4);
	
private:
	std::string	LoadShaderSource(const char* fileName);
	GLuint CompileShader(const char* fileName, GLenum type);
	void TipUniformNotFound(const std::string& name);
};

