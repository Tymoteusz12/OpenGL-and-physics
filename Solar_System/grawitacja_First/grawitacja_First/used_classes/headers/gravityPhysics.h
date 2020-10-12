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
	int id = 0;
	bool press = false;
	struct modelData {
		double mass = 0.0f;
		double radius = 0.0f;
		double peryhelion = 0.0f;
		double aphelion = 0.0f;
		glm::dvec3 position = glm::vec3(0.0f);
		glm::dvec3 vMax = glm::vec3(0.0f);
	}sun, planet;

	vector<modelData> modelArray;
	vector<glm::dvec3> gravityVelocity;
	struct ellipseVertices {
		vector<glm::dvec3> assignArrayPlus;
		vector<glm::dvec3> assignArrayMinus;
	}myVertices;

	vector<ellipseVertices> dynamicArray;
	Gravity(const double, const double);

	void loadSunData();
	void loadPlanetsData();
	void findResultantForce(int);
	glm::vec3 findForce(glm::vec3);
	void updatePosition(int);
	void findEllipse(int, bool);
	~Gravity(){}
private:
	float refreshTime = 0;
	const double scale = 1.0E-7;
	const double constG;
	const double refreshValue;
	struct ellipseProperties;
	glm::dvec3 resultantForce;
	const double findModelSpeed(modelData, modelData);
	void assignValuesForMoon(ellipseProperties&, glm::dvec3&);
	bool isMoon(unsigned int);
	
};

#endif