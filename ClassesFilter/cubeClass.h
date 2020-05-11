#ifndef _CUBE_CLASS_
#define _CUBE_CLASS_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include "stb_image.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
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

	void setVertexAndBuffer(float vertices[], unsigned int size, unsigned int typeID);

	void loadTexture(char const* path);

	void DrawObject(unsigned int startingPoint, unsigned int endingPoint);

	void setMaterialProperties(int textureID, float shininess);

	void setMaterialProperties(int firstTextureID, int secondTextureID, float shininess);
	
	void setSpotLightProperties(glm::vec3 vecProperties[], float floatProperties[]);

	void setSpotLightProperties(glm::vec3 vecProperties[], float floatProperties[], unsigned int modelCount);

	void setDirLightProperties(glm::vec3 vecProperties[]);

	void setDirtLightProperties(glm::vec3 vecProperties[], unsigned int modelCount);

	glm::mat4 setModelProperties(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotateAxis, float degrees, glm::mat4* model);

	glm::mat4 setModelProperties(glm::vec3 translation, glm::vec3 scale, glm::mat4* model);

	void moveModel(glm::vec3& modelPos, glm::vec3 modelScale, glm::vec3& speedVec, float deltaTime, bool isFlying);

	void SimulateGravity(glm::vec3& modelPos, float deltaTime);

	void SimulateFriction(glm::vec3& modelPos, float deltaTime);

	void SimulateMove(glm::vec3& modelPos, float deltaTime);

	~model3D() {};
};

#endif