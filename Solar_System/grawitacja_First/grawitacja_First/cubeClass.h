#ifndef _CUBE_CLASS_
#define _CUBE_CLASS_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "camera.h"
#include "Shaders.h"
using namespace std;

class model3D {
private:
	Camera* cameraPointer;
	bool gravityEnabled = true;
	bool floorBound = false;
	bool wallBound = false;
	unsigned int buffer;
	unsigned int vertexBuffer;
	unsigned int myTempTexture;
	glm::vec3 modelSpeed = glm::vec3(0.0f);
	const glm::vec3 gravityForce;
	glm::vec3 frictionForce;
	glm::vec3 frictionSpeed = glm::vec3(0.0f);
	glm::vec3 gravitySpeed = glm::vec3(0.0f);
public:
	CreateShader* shaderPointer;
	vector <unsigned int> myTextures;
	glm::mat4 myModel;
	glm::vec3 myPosition;

	model3D(Camera* cameraPointer, CreateShader* shaderPointer, glm::vec3 gravityForce, glm::vec3 frictionForce);

	model3D() {}

	void setVertexAndBuffer(float[], const unsigned int, unsigned int);

	void loadTexture(char const*);

	void DrawObject(const unsigned int, const unsigned int);

	void setMaterialProperties(const int, const float);

	void setMaterialProperties(const int, const int, float);
	
	void setSpotLightProperties(glm::vec3[], const float[]);

	void setSpotLightProperties(glm::vec3[], const float [], const unsigned int);

	void setDirLightProperties(glm::vec3[]);

	void setDirtLightProperties(glm::vec3[], const unsigned int);

	glm::mat4 setModelProperties(glm::vec3, glm::vec3, glm::vec3, float, glm::mat4*);

	glm::mat4 setModelProperties(glm::vec3, glm::vec3, glm::mat4*);

	void moveModel(glm::vec3&, glm::vec3, glm::vec3&, float, bool);

	void SimulateGravity(glm::vec3&, float);

	void SimulateFriction(glm::vec3&, float);

	void SimulateMove(glm::vec3&, float);

	~model3D() {};
};

#endif