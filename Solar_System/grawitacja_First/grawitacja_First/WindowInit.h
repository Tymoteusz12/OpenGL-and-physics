#ifndef _WINDOW_INIT_
#define _WINDOW_INIT_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
class CreateWindow
{
public:
	GLFWwindow* window;
	CreateWindow()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(1024, 1024, "LearnOPGL", NULL, NULL);

		if (window == NULL) {
			cout << "Failed to create GLFW window. \n";
			glfwTerminate();
		}
	}
};

#endif;