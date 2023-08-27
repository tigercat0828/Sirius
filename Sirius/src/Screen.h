#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>



class Screen {

public:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	Screen();
	bool Init();
	void SetParameter();

	void Update();
	void NewFrame();

	bool ShouldClose();
	void SetShouldClose(bool shouldClose);

private:
	GLFWwindow* window;

};

