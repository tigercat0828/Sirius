#include "Screen.h"
#include "Keyboard.h"
#include "Mouse.h"

unsigned int Screen::SCR_WIDTH = 800;
unsigned int Screen::SCR_HEIGHT= 600;

void Screen::FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); 
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}
Screen::Screen() : window(nullptr) {

}

bool Screen::Init() {
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (!window) {
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

void Screen::SetParameter() {
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, Screen::FrameBufferSizeCallback);
	glfwSetKeyCallback(window, Keyboard::KeyCallback);
	glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
	glfwSetCursorPosCallback(window, Mouse::CursorPositionCallback);
	glfwSetScrollCallback(window, Mouse::MouseWheelCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

void Screen::Update() {
	glClearColor(.2f, .3f, .3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::NewFrame() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Screen::ShouldClose() {
	return glfwWindowShouldClose(window);
}

void Screen::SetShouldClose(bool shouldClose) {
	glfwSetWindowShouldClose(window, shouldClose);
}
