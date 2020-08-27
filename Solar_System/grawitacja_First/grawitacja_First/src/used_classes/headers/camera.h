#ifndef _CAMERA_
#define _CAMERA_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
class Camera
{
private:
	float cameraSpeed = 1.0f;
	bool firstMouse = true;
	bool viewMode = false;
	float width, height;
	float lastx = 0.0f, lasty = 0.0f;
	float deltaTime = 0.0f;
	const float sensitivity = 0.05f;
	const glm::vec3 gravity;
	glm::vec3 speed = glm::vec3(0.0f, 0.0f, 0.0f);
public:
	glm::vec3 trans = glm::vec3(0.0f);
	struct mouseStates {
		bool leftButton = false;
		bool rightButton = false;
	}mainMouse;
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool useGravity = false;
	glm::mat4 currentView = glm::mat4(1.0f);
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 500.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera(const float, const float, const glm::vec3);
	Camera(const float, const  float);
	Camera() {}

	glm::mat4 CreateViewMatrix();
	glm::mat4 CreateProjectionMatix(const float&, const float&, const float&);

	void MoveCameraFunction(GLFWwindow*, float);

	void SimulateGravity();

	void UseCameraWithGravity(GLFWwindow*);

	void mouse_callback(GLFWwindow*, double, double);

	void translateCamera(double, double);

	void setPositionAndDirection(glm::vec3, float);

};

#endif