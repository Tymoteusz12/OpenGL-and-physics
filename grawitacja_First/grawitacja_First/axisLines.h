#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include <vector>
#include <iostream>

CreateShader *shader;

using namespace std;

class axisLines {
public:
	axisLines(CreateShader *shader): axes(36) {
		createBuffers();
		shaderPointer = shader;
	}

	void drawAxes() {
		shaderPointer->useProgram();
		shaderPointer->setBool("isAxis", true);
		glBindVertexArray(VAO);
		glLineWidth(2);
		glDrawArrays(GL_LINE_STRIP, 0, axes);
	}
private:
	unsigned int VAO, VBO;
	const int axes;
	CreateShader* shaderPointer;

	float axisVertices[72] = {
		0.0f,   0.0f,   0.0f,   0.0f, 0.0f, 1.0f,
		0.0f,   0.0f,  50.0f,   0.0f, 0.0f, 1.0f,
		0.0f,   0.0f,   0.0f,   0.0f, 0.0f, 0.3f,
		0.0f,   0.0f, -50.0f,   0.0f, 0.0f, 0.3f,
		0.0f,   0.0f,   0.0f,	0.0f, 1.0f, 0.0f,
		0.0f,  50.0f,   0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,   0.0f,   0.0f,	0.0f, 0.3f, 0.0f,
		0.0f, -50.0f,   0.0f,   0.0f, 0.3f, 0.0f,
		0.0f,   0.0f,   0.0f,	1.0f, 0.0f, 0.0f,
	   50.0f,   0.0f,   0.0f,   1.0f, 0.0f, 0.0f,
		0.0f,   0.0f,   0.0f,	0.3f, 0.0f, 0.0f,
	  -50.0f,   0.0f,   0.0f,   0.3f, 0.0f, 0.0f
		
	};

	void createBuffers() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), &axisVertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);
	}

};