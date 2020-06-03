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
	unsigned int amount = 100000;
	struct asteroidProperties {
		glm::vec3 position = glm::vec3(0.0f);
		float mass = 0;
		glm::vec3 vMax = glm::vec3(0.0f);
	}*asteroid;

	struct physicsVariables {
		const float constG;
		float sunMass;
	}*physicsProperties;

	asteroidBelt(CreateShader *shader, Model *rock, const float constG, float sunMass){
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
		float marsRadius = (solarSystem.modelArray[4].aphelion + solarSystem.modelArray[4].peryhelion) / 2;
		float jupiterRadius = (solarSystem.modelArray[5].aphelion + solarSystem.modelArray[5].peryhelion) / 2;
		float earthMass = solarSystem.modelArray[3].mass;
		float earthRadius = solarSystem.modelArray[3].radius;
		float radius = marsRadius + (jupiterRadius - marsRadius)/4;
		float offset = (jupiterRadius - marsRadius)*2;
		glm::vec3 correction = glm::vec3(offset, 0.0f, offset);

		for (unsigned int i = 0; i < amount; i++) {
			glm::mat4 tempModel = glm::mat4(1.0f);
			float x, z;
			float angle = float(i) / float(amount) * 360.0f;
  			float displacement = (rand() % (int)(2 * offset * 100)) / 35.0 - offset;
			x = sin(angle) * radius + displacement;
			displacement = (rand() % (int)(2 * 100)) / 100.0;
			float y = displacement + 0.4f;
			displacement = (rand() % (int)(2 * offset * 100)) / 35.0 - offset;
			z = cos(angle) * radius + displacement;

			glm::vec3 direction = glm::normalize(glm::vec3(x, y, z));
			asteroid[i].position = glm::vec3(x, y, z) + correction;
			asteroid[i].vMax = findAsteroidVelocity(asteroid[i].position) * direction;
			asteroid[i].mass = rand() % (int)(earthMass) / earthMass + earthMass / 1000.0;
			float scale = (rand()% 10000+1) * earthRadius / 1000.0;
			float rotAngle = rand() % 360;

			tempModel = glm::translate(tempModel, asteroid[i].position);
			tempModel = glm::scale(tempModel, glm::vec3(scale));
			tempModel = glm::rotate(tempModel, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

			asteroidMatrices[i] = tempModel;
		}
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

	glm::vec3 findAsteroidVelocity(glm::vec3 position) {
		
		float xVel = sqrt(physicsProperties->constG * physicsProperties->sunMass / abs(position.x));
		float yVel = sqrt(physicsProperties->constG * physicsProperties->sunMass / abs(position.y));
		float zVel = sqrt(physicsProperties->constG * physicsProperties->sunMass / abs(position.z));
		glm::vec3 vMax = glm::vec3(xVel, yVel, zVel);

		return vMax;
	}
	CreateShader* asteroidShader;
	Model *rockPointer;
	unsigned int ringVBO;
	glm::mat4* asteroidMatrices;
	
};