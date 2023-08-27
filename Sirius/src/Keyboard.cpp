#include "Keyboard.h"
bool Keyboard::s_Keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::s_KeysChanged[GLFW_KEY_LAST] = { 0 };

void Keyboard::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if (action != GLFW_RELEASE) {
		if (!s_Keys[key]) s_Keys[key] = true;
	}
	else {
		s_Keys[key] = false;
	}

	s_KeysChanged[key] = action != GLFW_REPEAT;
}

bool Keyboard::Key(int key) {
	return s_Keys[key];
}

bool Keyboard::IsKeyChanged(int key) {
	bool res = s_KeysChanged[key];
	s_KeysChanged[key] = false;
	return res;
}

bool Keyboard::KeyWentDown(int key) {
	return s_Keys[key] && IsKeyChanged(key);
}

bool Keyboard::KeyWentUp(int key) {
	return !s_Keys[key] && IsKeyChanged(key);
}
