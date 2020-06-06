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
	Orbit(CreateShader *orbitShader, Gravity *pointer):
		orbitShader(orbitShader), verticesPointer(pointer){}

	void addVertices() {

		verticesToDraw = new float* [verticesPointer->modelArray.size() - 1];
		pointsToDraw = new unsigned int[verticesPointer->modelArray.size() - 1];
		orbitVAO = new unsigned int[verticesPointer->modelArray.size() - 1];
		orbitVBO = new unsigned int[verticesPointer->modelArray.size() - 1];
		for (int j = 0; j < verticesPointer->modelArray.size() - 1; j++) {
			unsigned int arraySizePlus = verticesPointer->dynamicArray[j].assignArrayPlus.size();
			unsigned int arraySizeMinus = verticesPointer->dynamicArray[j].assignArrayMinus.size();
			unsigned int sumSize = arraySizePlus + arraySizeMinus;
			pointsToDraw[j] = sumSize;
			verticesToDraw[j] = new float[pointsToDraw[j] * 3 + 3];

			for (unsigned int i = 0; i < arraySizePlus; i++) {
				verticesToDraw[j][i * 3] = verticesPointer->dynamicArray[j].assignArrayPlus[i].x;
				verticesToDraw[j][i * 3 + 1] = verticesPointer->dynamicArray[j].assignArrayPlus[i].y;
				verticesToDraw[j][i * 3 + 2] = verticesPointer->dynamicArray[j].assignArrayPlus[i].z;
			}
			int indexID = 0;
			for (unsigned int i = arraySizePlus; i < sumSize; i++) {
				verticesToDraw[j][i * 3] = verticesPointer->dynamicArray[j].assignArrayMinus[indexID].x;
				verticesToDraw[j][i * 3 + 1] = verticesPointer->dynamicArray[j].assignArrayMinus[indexID].y;
				verticesToDraw[j][i * 3 + 2] = verticesPointer->dynamicArray[j].assignArrayMinus[indexID++].z;
			}
			createBuffers(j);
		}
	}

	void drawOrbit() {
		for (int i = 0; i < verticesPointer->dynamicArray.size(); i++) {
			if (i == 3) {
				static glm::vec3 currentPos = verticesPointer->modelArray[3].position;
				displacement = lastPos - currentPos;
				lastPos = verticesPointer->modelArray[3].position;
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, displacement);
				orbitShader->setMat4("model", model);
			}
			else if(i == 4) {
				glm::mat4 model = glm::mat4(1.0f);
				orbitShader->setMat4("model", model);
			}

			if (pointsToDraw != 0) {
				glBindVertexArray(orbitVAO[i]);
				glLineWidth(1);
				glDrawArrays(GL_LINE_STRIP, 0, pointsToDraw[i]/2);
				glDrawArrays(GL_LINE_STRIP, pointsToDraw[i] / 2 , pointsToDraw[i] / 2 );
				glBindVertexArray(0);
			}
		}
	}
	~Orbit(){
		freeMemory();
		for (unsigned int i = 0; i < verticesPointer->modelArray.size() - 1; i++) {
			delete[] verticesToDraw[i];
		}
	
		delete[] verticesToDraw;
		delete[] pointsToDraw;
	}
private:
	unsigned int *orbitVBO, *orbitVAO;
	unsigned int *pointsToDraw;
	glm::vec3 lastPos = glm::vec3(0.0f);
	glm::vec3 displacement = glm::vec3(0.0f);
	CreateShader* orbitShader;
	Gravity* verticesPointer;
	float **verticesToDraw;
	void createBuffers(int i) {
		glGenVertexArrays(1, &orbitVAO[i]);
		glGenBuffers(1, &orbitVBO[i]);

		glBindVertexArray(orbitVAO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, orbitVBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesToDraw[i]) * pointsToDraw[i] * 3, verticesToDraw[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void freeMemory() {
		for (int i = 0; i < verticesPointer->modelArray.size(); i++) {
			glDeleteVertexArrays(1, &orbitVAO[i]);
			glDeleteBuffers(1, &orbitVBO[i]);
		}
	}
};

#endif
