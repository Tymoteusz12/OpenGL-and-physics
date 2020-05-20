#ifndef _gravity_
#define _gravity_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include "orbitClass.h"
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
	vector<glm::vec3> gravityVelCopy;
	vector<modelData> modelArrayCopy;

	Gravity(float constG, float refreshValue);

	void loadSunData();
	void loadPlanetsData();
	void findResultantForce(int index);
	void updatePosition(int index);

	vector<glm::vec3> findOrbitPath(int index, float deltaTime);
private:
	float pointsAmount = 50.0f;
	float equalSpeedBoost = 1 / pointsAmount;
	float speedBoost = 10.0f;
	float finalSpeedBoost = speedBoost * equalSpeedBoost;
	float refreshTime = 0;
	const float constG;
	const float refreshValue;
	glm::vec3 resultantForce;
	
	float findModelSpeed(modelData planet, modelData sun);

};

#endif