#include "Camera.h"
#include <cmath>

using namespace glm;
Camera::Camera(vec3 position) :
	cameraPos(position),
	worldUp(vec3(0.0f, 1.0f, 0.0f)),
	yaw(-90.0f),
	pitch(0.0f),
	speed(2.5f),
	zoom(45.0f),
	cameraFront(vec3(0.0f, 0.0f, -1.0f)) 
{
	updateCameraVectors();
}

void Camera::updateCameraDirection(double dx, double dy) {
	pitch += dy;
	yaw += dx;
	if (pitch > 89.0f) pitch = 89.0f;
	else if (pitch < -89.0f) pitch = -89.0f;

	updateCameraVectors();
	
}

void Camera::updateCameraPosition(CameraDirection dir, double deltaTime) {
	float velocity = (float)deltaTime * speed;
	switch (dir) {
	case CameraDirection::FORWARD:
		cameraPos += cameraFront * velocity;
		break;
	case CameraDirection::BACKWARD:
		cameraPos -= cameraFront * velocity;
		break;
	case CameraDirection::LEFT:
		cameraPos -= cameraRight * velocity;
		break;
	case CameraDirection::RIGHT:
		cameraPos += cameraRight* velocity;
		break;
	case CameraDirection::UP:
		cameraPos += cameraUp * velocity;
		break;
	case CameraDirection::DOWN:
		cameraPos -= cameraUp * velocity;
		break;
	default:
		break;
	}
}

void Camera::updateCameraZoom(double dy) {

	zoom = glm::clamp((float)(zoom - dy), 1.0f, 45.0f);
}

float Camera::GetZoom() {
	return zoom;
}

mat4 Camera::GetViewMatrix() {
	return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::updateCameraVectors() {
	vec3 direction;
	direction.x = cos(radians(yaw)) * cos(radians(pitch));
	direction.y = sin(radians(pitch));
	direction.z = sin(radians(yaw)) * cos(radians(pitch));
	cameraFront = normalize(direction);
	cameraRight = normalize(cross(cameraFront, worldUp));
	cameraUp = normalize(cross(cameraRight, cameraFront));
}
