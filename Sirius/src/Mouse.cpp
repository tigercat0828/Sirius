#include "Mouse.h"
double Mouse::x =0;
double Mouse::y = 0;
double Mouse::lastX = 0;
double Mouse::lastY = 0;
double Mouse::deltaX = 0;
double Mouse::deltaY = 0;
double Mouse::scrollDX = 0;
double Mouse::scrollDY = 0;
bool Mouse::firstMouseEntered = true;

bool Mouse::s_Buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::s_ButtonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };


void Mouse::CursorPositionCallback(GLFWwindow* window, double _x, double _y) {
	x = _x;
	y = _y;

	if (firstMouseEntered) {
		lastX = x;
		lastY = y;
		firstMouseEntered = false;
	}
	deltaX = x - lastX;
	deltaY = lastY - y;

	lastX = x;
	lastY = y;
}

void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	
	if (action != GLFW_RELEASE) {
		if (!s_Buttons[button]) s_Buttons[button] = true;
	}
	else {
		s_Buttons[button] = false;
	}
	s_ButtonsChanged[button] = action != GL_REPEAT;
}

void Mouse::MouseWheelCallback(GLFWwindow* window, double dx, double dy) {
	scrollDX = dx;
	scrollDY = dy;
}

double Mouse::GetMousePosX() {
	return x;
}
double Mouse::GetMousePosY() {
	return y;
}
double Mouse::GetMouseDeltaX() {
	double dx = deltaX;
	deltaX = 0;
	return dx;
}
double Mouse::GetMouseDeltaY() {
	double dy = deltaY;
	deltaY = 0;
	return dy;
}
double Mouse::GetScrollDeltaX() {
	double dx = scrollDX;
	scrollDX = 0;
	return dx;
}
double Mouse::GetScrollDeltaY() {
	double dy = scrollDY;
	scrollDY = 0;
	return dy;
}

bool Mouse::button(int button) {
	return s_Buttons[button];
}

bool Mouse::IsbuttonChanged(int button) {
	bool res = s_ButtonsChanged[button];
	s_ButtonsChanged[button] = false;
	return res;
}

bool Mouse::buttonWentUp(int button) {
	return !s_Buttons[button] && IsbuttonChanged(button);
}

bool Mouse::buttonWentDown(int button) {
	return s_Buttons[button] && IsbuttonChanged(button);
}
