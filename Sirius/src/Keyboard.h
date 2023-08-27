#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard {
public:
	static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static bool Key(int key);
	static bool IsKeyChanged(int key);
	static bool KeyWentUp(int key);
	static bool KeyWentDown(int key);

private :
	static bool s_Keys[];
	static bool s_KeysChanged[];
};