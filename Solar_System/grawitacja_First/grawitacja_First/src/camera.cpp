#include "camera.h"

Camera::Camera(const float width, const float height, const glm::vec3 gravityForce) :
	width(width), height(height), gravity(gravityForce), lastx(width / 2), lasty(height / 2) 
{}

Camera::Camera(const float width, const float height) :
	width(width), height(height), lastx(width / 2), lasty(height / 2) {}

glm::mat4 Camera::CreateViewMatrix() {
	currentView = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return currentView;
}

glm::mat4 Camera::CreateProjectionMatix(const float& radians, const float& width, const float& height) {
	return glm::perspective(glm::radians(radians), width / height, 0.1f, (float)6.0E10);
}

void Camera::MoveCameraFunction(GLFWwindow* window, float deltaTime) {
	this->deltaTime = deltaTime;
	if (useGravity) {
		SimulateGravity();
		UseCameraWithGravity(window);
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cameraSpeed = 3000.0;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS)
			cameraSpeed = 29.97;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * deltaTime * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * deltaTime * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= cameraSpeed * deltaTime * glm::normalize(glm::cross(cameraFront, cameraUp));
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += cameraSpeed * deltaTime * glm::normalize(glm::cross(cameraFront, cameraUp));
	}
}

void Camera::SimulateGravity() {
	if (cameraPos.y > 0) {
		speed += deltaTime * gravity;
		cameraPos += speed;
	}
	else {
		speed = glm::vec3(0.0f);
		cameraPos.y = 0.0f;
	}
}

void Camera::UseCameraWithGravity(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed = 20.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS)
		cameraSpeed = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS and cameraPos.y == 0.0f) {
		speed = glm::vec3(0.0f, 0.10f, 0.0f);
		cameraPos += speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos.x += cameraSpeed * deltaTime * cameraFront.x;
		cameraPos.z += cameraSpeed * deltaTime * cameraFront.z;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos.x -= cameraSpeed * deltaTime * cameraFront.x;
		cameraPos.z -= cameraSpeed * deltaTime * cameraFront.z;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= cameraSpeed * deltaTime * glm::normalize(glm::cross(cameraFront, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += cameraSpeed * deltaTime * glm::normalize(glm::cross(cameraFront, cameraUp));
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {
		lastx = xpos;
		lasty = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastx;
	float yoffset = lasty - ypos;
	float zoffset = 0;
	lastx = xpos;
	lasty = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

	if (mainMouse.rightButton) {
		trans = cameraPos + cameraFront* glm::vec3(3.1855);
	}
	if (mainMouse.leftButton)
		cameraPos = -cameraFront * glm::vec3(3.1855) + trans;

}

void Camera::setPositionAndDirection(glm::vec3 position, float pitch) {
	cameraPos = position;
	this->pitch = pitch;
	yaw = -90.0f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}