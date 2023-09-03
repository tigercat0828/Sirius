#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 
#include "Shader.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "Screen.h"
#include "Texture.h"
#include "Cube.hpp"
#include "Material.h"
#include "Lamp.hpp"
using namespace glm;


void WindowResize(GLFWwindow* window, int width, int height);
void ProcessInput(float deltaTime);

void SetEventCallBack(GLFWwindow * window) {
	glfwSetFramebufferSizeCallback(window, WindowResize);
	glfwSetKeyCallback(window, Keyboard::KeyCallback);
	glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
	glfwSetCursorPosCallback(window, Mouse::CursorPositionCallback);
	glfwSetScrollCallback(window, Mouse::MouseWheelCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
float mixVal = 0.8f;
int SCR_WIDTH = 1000;
int SCR_HEIGHT = 1000;
Camera camera(vec3(0 ,0.0f, 3));
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Screen screen;


int main() {
	spdlog::info("Welcome to spdlog!");
	
	stbi_set_flip_vertically_on_load(true);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

	if (!screen.Init()) {
		spdlog::error("Failed to create window");
		glfwTerminate();
		return -1;
	}
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		spdlog::error("Failed to init GLAD");
		return -1;
	}

	screen.SetParameter();

	Shader shader("Default","shader/Default.vert", "shader/Default.frag");
	Shader lampShader("Lamp", "shader/Default.vert", "shader/Lamp.frag");

	Cube cube(Material::emerald ,vec3(0, 0, -1), vec3(1.0));
	cube.Init();

	Lamp lamp(vec3(1.0f), vec3(1.0f), vec3(1.0f), vec3(1.0f), vec3(-1.0f, -0.5f, -0.5f), vec3(0.25f));
	lamp.Init();
	while (!screen.ShouldClose()) {
		
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		ProcessInput(deltaTime);
		screen.Update();

		shader.Activate();
		shader.SetVec3("ViewPos", camera.cameraPos);

		lamp.pointLight.Render(shader);
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		mat4 view = camera.GetViewMatrix();
		mat4 projection = perspective(radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		cube.Render(shader);

		lampShader.Activate();
		lampShader.SetMat4("view", view);
		lampShader.SetMat4("projection", projection);

		lamp.Render(lampShader);



		screen.NewFrame();
	}
	cube.CleanUp();
	lamp.CleanUp();
	glfwTerminate();
	return 0;
}

void WindowResize(GLFWwindow* window, int width, int height) {
	glfwSetCursorPos(window, width / 2, height / 2);
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

void ProcessInput(float deltaTime) {

	if (Keyboard::Key(GLFW_KEY_ESCAPE)) {
		screen.SetShouldClose(true);
	}
	if (Keyboard::KeyWentDown(GLFW_KEY_DOWN)) {
		mixVal -= 0.1;
		if (mixVal < 0.0f) mixVal = 0;
	}
	if (Keyboard::KeyWentUp(GLFW_KEY_UP)) {
		mixVal += 0.1;
		if (mixVal > 1.0f) mixVal = 1;
	}
	// camera operation
	if (Keyboard::Key(GLFW_KEY_W)) {
		camera.updateCameraPosition(CameraDirection::FORWARD, deltaTime);
	}
	if (Keyboard::Key(GLFW_KEY_A)) {
		camera.updateCameraPosition(CameraDirection::LEFT, deltaTime);
	}
	if (Keyboard::Key(GLFW_KEY_S)) {
		camera.updateCameraPosition(CameraDirection::BACKWARD, deltaTime);
	}
	if (Keyboard::Key(GLFW_KEY_D)) {
		camera.updateCameraPosition(CameraDirection::RIGHT, deltaTime);
	}
	if (Keyboard::Key(GLFW_KEY_SPACE)) {
		camera.updateCameraPosition(CameraDirection::UP, deltaTime);
	}
	if (Keyboard::Key(GLFW_KEY_LEFT_SHIFT)) {
		camera.updateCameraPosition(CameraDirection::DOWN, deltaTime);
	}
	double dx = Mouse::GetMouseDeltaX();
	double dy = Mouse::GetMouseDeltaY();
	
	if (dx != 0 || dy != 0) {
		camera.updateCameraDirection(dx,dy);
	}
	double scrollY = Mouse::GetScrollDeltaY();
	if (scrollY != 0) {
		camera.updateCameraZoom(scrollY);
	}
}
