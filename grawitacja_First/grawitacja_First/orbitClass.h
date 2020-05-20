#ifndef _orbit_
#define _orbit_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include <vector>
#include <iostream>

using namespace std;

class Orbit {

public:
	Orbit(CreateShader *orbitShader):
		orbitShader(orbitShader){}

	void addVertices(vector<glm::vec3> vertices) {
		pointsToDraw = vertices.size();
		verticesToDraw = new float[vertices.size() * 3];
			for (int i = 0; i < vertices.size(); i++) {
			verticesToDraw[i * 3] = vertices[i].x;
			verticesToDraw[i * 3 + 1] = vertices[i].y;
			verticesToDraw[i * 3 + 2] = vertices[i].z;
			}		
	}
	void drawOrbit() {
		createBuffers();
		glBindVertexArray(orbitVAO);
		glPointSize(5);
		glDrawArrays(GL_POINTS, 0, pointsToDraw);
		freeMemory();
	}
private:
	unsigned int orbitVBO, orbitVAO;
	int pointsToDraw;
	CreateShader* orbitShader;
	float* verticesToDraw;

	void createBuffers() {
		glGenVertexArrays(1, &orbitVAO);
		glGenBuffers(1, &orbitVBO);

		glBindVertexArray(orbitVAO);
		glBindBuffer(GL_ARRAY_BUFFER, orbitVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesToDraw) * pointsToDraw * 3, verticesToDraw, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void freeMemory() {
		glDeleteVertexArrays(1, &orbitVAO);
		glDeleteBuffers(1, &orbitVBO);
		delete[] verticesToDraw;
	}
};



#endif
