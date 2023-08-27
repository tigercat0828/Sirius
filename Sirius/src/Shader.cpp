#include <spdlog/spdlog.h>
#include "Shader.h"

Shader::Shader(const char* vFileName, const char* fFileName) {
	int success;
	char infoLog[512];
	GLuint vertexShader = CompileShader(vFileName, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fFileName, GL_FRAGMENT_SHADER);
	Id = glCreateProgram();
	glAttachShader(Id, vertexShader);
	glAttachShader(Id, fragmentShader);
	glLinkProgram(Id);

	glGetProgramiv(Id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(Id, 512, nullptr, infoLog);
		spdlog::error("Failed to link program {} : {}", Id, infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(Id);
}

std::string Shader::LoadShaderSource(const char* fileName) {
	std::ifstream file;
	std::stringstream buf;
	std::string src = "";
	file.open(fileName);
	if (file.is_open()) {
		buf << file.rdbuf();
		src = buf.str();
	}
	else {
		spdlog::error("Failed to open {}", fileName);
	}
	file.close();
	return src;
}

GLuint Shader::CompileShader(const char* fileName, GLenum type) {
	int success;
	char infoLog[512];
	GLuint id = glCreateShader(type);
	std::string fragStr = LoadShaderSource(fileName);
	const GLchar* fSrc = fragStr.c_str();
	glShaderSource(id, 1, &fSrc, nullptr);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		spdlog::error("Failed to compile shader {}", fileName);
	}
	return id;
}

void Shader::SetMat4(const std::string& para_name, glm::mat4 value) {
	int location = glGetUniformLocation(Id, para_name.c_str());
#ifdef DEBUG
	if (location == -1) TipUniformNotFound(para_name);
#endif // DEBUG

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::SetInt(const std::string& para_name, int value) {
	int location = glGetUniformLocation(Id, para_name.c_str());
#ifdef DEBUG
	if (location == -1) TipUniformNotFound(para_name);
#endif // DEBUG
	glUniform1i(location, value);
}
void Shader::SetFloat(const std::string& para_name, float value) {
	int location = glGetUniformLocation(Id, para_name.c_str());
#ifdef DEBUG
	if (location == -1) TipUniformNotFound(para_name);
#endif // DEBUG
	glUniform1f(location, value);
}
void Shader::SetVec3(const std::string& para_name, glm::vec3 value) {
	int location = glGetUniformLocation(Id, para_name.c_str());
#ifdef DEBUG
	if (location == -1) TipUniformNotFound(para_name);
#endif // DEBUG
	glUniform3fv(location, 1,glm::value_ptr(value));
}
void Shader::TipUniformNotFound(const std::string& name) {
	spdlog::error("Program({}) \"{}\" uniform not found in shader", Id, name);
}

