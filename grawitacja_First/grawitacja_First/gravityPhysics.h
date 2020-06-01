#ifndef _gravity_
#define _gravity_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>

using namespace std;

class Gravity {
public:
	struct modelData {
		float mass = 0.0f;
		float radius = 0.0f;
		float peryhelium = 0.0f;
		float aphelium = 0.0f;
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 vMax = glm::vec3(0.0f);
	}sun, planet;

	vector<modelData> modelArray;
	vector<glm::vec3> gravityVelocity;
	unsigned int* sizes = new unsigned int [modelArray.size()];
	struct ellipseVertices {
		vector<glm::vec3> assignArrayPlus;
		vector<glm::vec3> assignArrayMinus;
	}myVertices;

	vector<ellipseVertices> dynamicArray;
	Gravity(float constG, float refreshValue);

	void loadSunData();
	void loadPlanetsData();
	void findResultantForce(int index);
	void updatePosition(int index);

	void findEllipse(int, bool);
	~Gravity(){}
private:
	float refreshTime = 0;
	const float constG;
	const float refreshValue;
	glm::vec3 resultantForce;
	
	float findModelSpeed(modelData planet, modelData sun);

};

#endif