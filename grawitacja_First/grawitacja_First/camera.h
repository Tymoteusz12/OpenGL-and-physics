#ifndef _CAMERA_
#define _CAMERA_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool useGravity = false;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera(float width, float height, const glm::vec3 gravityForce);
	Camera(float width, float height);
	Camera() {}

	glm::mat4 CreateViewMatrix();
	glm::mat4 CreateProjectionMatix(float& radians, float& width, float& height);

	void MoveCameraFunction(GLFWwindow* window, float deltaTime);

	void SimulateGravity();

	void UseCameraWithGravity(GLFWwindow* window);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void setPositionAndDirection(glm::vec3 position, float pitch);

};

#endif