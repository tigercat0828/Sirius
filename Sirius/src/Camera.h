#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection {
	NONE = 0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class Camera {
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	glm::vec3 worldUp;

	float yaw;
	float pitch;
	// float roll;

	float speed;
	float zoom;
	Camera(glm::vec3 position);
	void updateCameraDirection(double dx, double dy);
	void updateCameraPosition(CameraDirection dir, double deltaTime);
	void updateCameraZoom(double dy);
	float GetZoom();
	glm::mat4 GetViewMatrix();
private:
	void updateCameraVectors();
	
};


