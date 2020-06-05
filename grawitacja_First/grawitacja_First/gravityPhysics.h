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
	Gravity(double constG, double refreshValue);

	void loadSunData();
	void loadPlanetsData();
	void findResultantForce(int index);
	glm::vec3 findForce(glm::vec3);
	void updatePosition(int index);
	void updateMoonOrbit();

	void findEllipse(int, bool);
	~Gravity(){}
private:
	float refreshTime = 0;
	double scale = 1.0E-8;
	const double constG;
	const double refreshValue;
	glm::dvec3 resultantForce;
	
	double findModelSpeed(modelData planet, modelData sun);

};

#endif