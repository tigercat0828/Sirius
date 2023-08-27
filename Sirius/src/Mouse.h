#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mouse {
public:
	static void CursorPositionCallback(GLFWwindow* window, double _x, double _y);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MouseWheelCallback(GLFWwindow* window, double dx, double dy);
	
	static double GetMousePosX();
	static double GetMousePosY();
	static double GetMouseDeltaX();
	static double GetMouseDeltaY();
	static double GetScrollDeltaX();
	static double GetScrollDeltaY();

	static bool button(int button);
	static bool IsbuttonChanged(int button);
	static bool buttonWentUp(int button);
	static bool buttonWentDown(int button);


private:
	static double x;
	static double y;
	static double lastX;
	static double lastY;
	static double deltaX;
	static double deltaY;
	
	static double scrollDX;
	static double scrollDY;

	static bool s_Buttons[];
	static bool s_ButtonsChanged[];

	static bool firstMouseEntered;
};
