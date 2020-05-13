#include "gravityPhysics.h"


Gravity::Gravity(float constG, float refreshValue) :
	constG(constG), refreshValue(refreshValue){}

void Gravity::loadSunData() {
	cout << "Load sun mass: " << endl;
	cin >> sun.mass;

	cout << "Load sun radius: " << endl;
	cin >> sun.radius;

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

		cout << i + 1 << " Enter model aphelium: " << endl;
		cin >> planet.aphelium;

		cout << i + 1 << " Enter model peryhelium: " << endl;
		cin >> planet.peryhelium;

		cout << i + 1 << " Enter model radius: " << endl;
		cin >> planet.radius;

		planet.position = glm::vec3(0.0f, 0.0f, planet.peryhelium);

		float vMax = findModelSpeed(planet, modelArray[0]);

		planet.vMax = glm::vec3(vMax, 0.0f, 0.0f);

		modelArray.push_back(planet);
		gravityVelocity.push_back(glm::vec3(0.0f));
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
}

void Gravity::updatePosition(int index) {

	gravityVelocity[index] += resultantForce * refreshValue;
	modelArray[index].position += (modelArray[index].vMax + gravityVelocity[index]) * refreshValue;
}
