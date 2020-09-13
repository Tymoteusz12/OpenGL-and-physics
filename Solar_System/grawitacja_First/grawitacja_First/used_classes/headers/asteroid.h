#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include "gravityPhysics.h"
#include "model.h"
#include <vector>
#include <iostream>

using namespace std;

Gravity;
Model;

class asteroidBelt
{
public:
	const unsigned int amount = 22000;
	const unsigned int solarSystemAsteroids = 10000;
	const unsigned int saturnFirstRing = 5000;
	const unsigned int saturnSecondRing =7000;
	glm::mat4* asteroidMatrices;
	struct asteroidProperties {
		glm::vec3 position = glm::vec3(0.0f);
		float scale = 0;
		float rotAngle = 0;
	}*asteroid;

	struct physicsVariables {
		const float constG;
		const float sunMass;
	}*physicsProperties;

	asteroidBelt(CreateShader* shader, Model* rock, const float constG, const float sunMass) {
		asteroidShader = shader;
		physicsProperties = new physicsVariables{
			constG,
			sunMass
		};
		asteroid = new asteroidProperties[amount];
		asteroidMatrices = new glm::mat4[amount];
		rockPointer = rock;
	}

	void findAsteroidMatrix(Gravity solarSystem) {
		srand(glfwGetTime());
		const float marsRadius = (solarSystem.modelArray[4].aphelion + solarSystem.modelArray[4].peryhelion) / 2;
		const float jupiterRadius = (solarSystem.modelArray[5].aphelion + solarSystem.modelArray[5].peryhelion) / 2;
		const float earthMass = solarSystem.modelArray[3].mass;
		const float earthRadius = solarSystem.modelArray[3].radius / 50; // divide by 50, so asteroids will not grow like planets
		float radius = jupiterRadius + marsRadius;
		float offset = (jupiterRadius - marsRadius)*2;
		glm::vec3 correction = glm::vec3(offset, 0.0f, offset);

		valuesToAssign result{
			radius , offset, earthRadius, earthMass,
			correction, 1000.0f
		};

		for (unsigned int i = 0; i < amount; i++) {
			glm::mat4 tempModel = glm::mat4(1.0f);

			if (i > solarSystemAsteroids) {
				result.radius = solarSystem.modelArray[7].radius * 2.5 ;
				result.offset = result.radius * 0.05f;
				result.correction = solarSystem.modelArray[7].position;
				result.sizeDivision = 10000.0f;
			}
			if (i > solarSystemAsteroids + saturnFirstRing) {
				result.radius = solarSystem.modelArray[7].radius * 3.5;
				result.sizeDivision = 10000.0f;
			}

			assignProperValues(result, i);
			assignToAsteroid(result, i);
			tempModel = returnTempModel(i);
			
			assignFinalMatrix(tempModel, i);
		}
	}

	glm::vec3 findDisplacement(Gravity solarSystem) {
		glm::vec3 currentPos = solarSystem.modelArray[7].position;
		displacement = lastPos - currentPos;
		lastPos = currentPos;

		return displacement;
	}

	void createBuffers() {
		glGenBuffers(1, &ringVBO);
		glBindBuffer(GL_ARRAY_BUFFER, ringVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * amount, &asteroidMatrices[0], GL_STATIC_DRAW);

		for (unsigned int i = 0; i < rockPointer->meshes.size(); i++) {
			unsigned int VAO = rockPointer->meshes[i].vertexBuffer;

			glBindVertexArray(VAO);
			size_t vec4Size = sizeof(glm::vec4);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1*vec4Size));
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);

			glBindVertexArray(0);
		}
	}

private:
	glm::vec3 lastPos = glm::vec3(0.0f);
	glm::vec3 displacement = glm::vec3(0.0f);
	CreateShader* asteroidShader;
	Model *rockPointer;
	unsigned int ringVBO;

	struct valuesToAssign {
		float radius, offset, scale, mass;
		glm::vec3 correction;
		float sizeDivision;
		float x, y, z;
		float angle, displacement;
	};

	void assignProperValues(valuesToAssign& result, int iteration) {
		result.angle = float(iteration) / float(amount) * 360.0f;
		result.displacement = (rand() % (int)(2 * result.offset * 100)) / 35.0 - result.offset;
		result.x = sin(result.angle) * result.radius + result.displacement;
		result.displacement = (rand() % (int)(2 * 100)) / 350.0;
		result.y = result.displacement + 0.4f;
		result.displacement = (rand() % (int)(2 * result.offset * 100)) / 35.0 - result.offset;
		result.z = cos(result.angle) * result.radius + result.displacement;
	}

	void assignToAsteroid(valuesToAssign result, int id) {
		asteroid[id].position = glm::vec3(result.x, result.y, result.z) + result.correction;
		asteroid[id].scale = (rand() % 10000 + 1) * result.scale / result.sizeDivision;
		asteroid[id].rotAngle = rand() % 360;
	}
	glm::mat4 returnTempModel(int id) {
		glm::mat4 tempModel = glm::mat4(1.0f);
		tempModel = glm::translate(tempModel, asteroid[id].position);
		tempModel = glm::scale(tempModel, glm::vec3(asteroid[id].scale));
		tempModel = glm::rotate(tempModel, asteroid[id].rotAngle, glm::vec3(0.8f, 0.6f, 0.4f));

		return tempModel;
	}

	void assignFinalMatrix(glm::mat4 modelToAssign, int id) {
		asteroidMatrices[id] = modelToAssign;
	}
	
};