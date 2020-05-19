#include "gravityPhysics.h"


Gravity::Gravity(float constG, float refreshValue, Orbit *orbitPointer) :
	constG(constG), refreshValue(refreshValue), orbitPointer(orbitPointer){}

void Gravity::loadSunData() {
	cout << "Load sun mass: " << endl;
	cin >> sun.mass;
	//sun.mass = 100;
	cout << "Load sun radius: " << endl;
	cin >> sun.radius;
	//sun.radius = 2;
	modelArray.push_back(sun);
	gravityVelocity.push_back(glm::vec3(0.0f));
}

void Gravity::loadPlanetsData() {
	int modelAmount{};
	cout << "Enter number of planets: " << endl;
	cin >> modelAmount;

	for (int i = 0; i < modelAmount; i++) {

		cout << i + 1 << " Enter model mass: " << endl;
		cin >> planet.mass;
		//planet.mass = 5;
		cout << i + 1 << " Enter model aphelium: " << endl;
		cin >> planet.aphelium;
		//planet.aphelium = 20;
		cout << i + 1 << " Enter model peryhelium: " << endl;
		cin >> planet.peryhelium;
		//planet.peryhelium = 10;
		cout << i + 1 << " Enter model radius: " << endl;
		cin >> planet.radius;
		//planet.radius = 1;
		planet.position = glm::vec3(0.0f, 0.0f, planet.peryhelium);

		float vMax = findModelSpeed(planet, modelArray[0]);

		planet.vMax = glm::vec3(vMax, 0.0f, 0.0f);

		modelArray.push_back(planet);
		gravityVelocity.push_back(glm::vec3(0.0f));
	}

	modelArrayCopy = modelArray;
	gravityVelCopy = gravityVelocity;

	for (int i = 1; i < modelArrayCopy.size(); i++) {
		modelArrayCopy[i].mass = modelArray[i].mass / pointsAmount;
		float vMax = findModelSpeed(modelArrayCopy[i], modelArrayCopy[0]);
	}
}

float Gravity::findModelSpeed(modelData planet, modelData sun) {

	float constVal = -2 * constG * sun.mass * (1 / planet.aphelium - 1 / planet.peryhelium);
	float kepler = 1 - pow(planet.peryhelium / planet.aphelium, 2.0f);
	float vMax = sqrt(constVal / kepler);

	return vMax;
}

void Gravity::findResultantForce(int index) {

	resultantForce = glm::vec3(0.0f);
	for (int i = 0; i < modelArray.size(); i++) {
		if (i != index) {

			float vectorLength = glm::length(modelArray[i].position - modelArray[index].position);
			glm::vec3 direction = glm::normalize(modelArray[i].position - modelArray[index].position);
			glm::vec3 force = glm::vec3(0.0f);

			if (vectorLength != 0.0f)
				force = ((constG * modelArray[i].mass) / (vectorLength * vectorLength)) * direction;

			resultantForce += force;
		}
	}
	updatePosition(index);
}

vector<glm::vec3> Gravity::findOrbitPath(int index, float deltaTime){

	vector<glm::vec3> pathVertices;

	refreshTime += deltaTime;
	if (refreshTime >= 0.001) {
		unsigned int loopVar = 0;
		refreshTime = 0;
		while (loopVar++ <= pointsAmount) {
			resultantForce = glm::vec3(0.0f);
			for (int i = 0; i < modelArray.size(); i++) {
				if (i != index) {

					float vectorLength = glm::length(modelArrayCopy[i].position - modelArrayCopy[index].position);
					glm::vec3 direction = glm::normalize(modelArrayCopy[i].position - modelArrayCopy[index].position);
					glm::vec3 force = glm::vec3(0.0f);

					if (vectorLength != 0.0f)
						force = ((constG * modelArrayCopy[i].mass) / (vectorLength * vectorLength)) * direction;

					resultantForce += force;
				}
			}
			gravityVelCopy[index] += resultantForce * refreshValue * speedBoost;
			modelArrayCopy[index].position += (modelArrayCopy[index].vMax + gravityVelCopy[index]) * refreshValue * speedBoost;
			pathVertices.push_back(modelArrayCopy[index].position);
		}
		return pathVertices;
	}
}

void Gravity::updatePosition(int index) {

	gravityVelocity[index] += resultantForce * refreshValue;
	modelArray[index].position += (modelArray[index].vMax + gravityVelocity[index]) * refreshValue;
}
