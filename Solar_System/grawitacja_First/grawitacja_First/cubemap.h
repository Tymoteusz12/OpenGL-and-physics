#ifndef _cubemap_
#define _cubemap_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "Shaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
using namespace std;

class cubeMap 
{
public:

	cubeMap(vector<string> faces, float *skyboxVertices, unsigned int arraySize) {

		this->skyboxVertices = skyboxVertices;
		this->arraySize = arraySize;
		
		glGenTextures(1, &cubemapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++) {

			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}

			else {
				cout << "Cubemap tex failed to load at path: " << faces[i] << endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		createAndBindBuffers();
	}

	void drawCubemap(glm::mat4 view, glm::mat4 projection, CreateShader *&skyShader) {

		glDepthFunc(GL_LEQUAL);

		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		skyShader->useProgram();
		skyShader->setMat4("projection", projection);
		skyShader->setMat4("view", view);
		skyShader->setInt("skybox", 0);
		glBindVertexArray(skyboxVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthFunc(GL_LESS);
	}

private:

	unsigned int cubemapTexture, skyboxVAO, skyboxVBO, arraySize;
	float *skyboxVertices;
	void createAndBindBuffers() {

		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);

		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, arraySize, skyboxVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
};

#endif