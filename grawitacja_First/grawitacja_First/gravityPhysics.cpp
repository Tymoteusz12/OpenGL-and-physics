#include "gravityPhysics.h"


Gravity::Gravity(float constG, float refreshValue) :
	constG(constG), refreshValue(refreshValue){}

void Gravity::loadSunData() {

	cout << "Loading sun data..." << endl;
	sun.mass = 1000000;

	sun.radius = 1.5;
	modelArray.push_back(sun);
	gravityVelocity.push_back(glm::vec3(0.0f));
}

void Gravity::loadPlanetsData() {
	int modelAmount{};
	modelAmount = 9;

	cout << "Loading planet data... " << endl;
	for (int i = 0; i < modelAmount; i++) {
		planet.mass = 5*(1+i);

		if(i >=4)
			planet.aphelium = 20 * (1 + 5*i);
		else 
			planet.aphelium = 20 * (1 + 3 * i);

		if (i >= 4)
			planet.peryhelium = 10 * (1 + 5 * i);
		else
			planet.peryhelium = 10 * (1 + 3 * i);

		planet.radius = 1;
		planet.position = glm::vec3(planet.peryhelium, 0.0f, 0.0f);

		float vMax = findModelSpeed(planet, modelArray[0]);

		planet.vMax = glm::vec3(0.0f, 0.0f, -vMax);

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
	updatePosition(index);
}

void Gravity::findEllipse(int index, bool positive) {

	double currentX = double(modelArray[index].peryhelium);
	double resultantZ = 0;
	double majorA = 0.5 * double(modelArray[index].aphelium + modelArray[index].peryhelium);
	double minorB = 0.5 * double(sqrt(pow(modelArray[index].aphelium, 2.0) + 2.0 * modelArray[index].aphelium * modelArray[index].peryhelium));
	double translationC = 0;
	int mirrorEllipse = 1;
	if(sqrt(pow(majorA, 2.0) - pow(minorB, 2.0) >= 0))
		translationC = sqrt(pow(majorA, 2.0) - pow(minorB, 2.0));

	glm::vec3 centerPoint = modelArray[0].position;
	double ellipseRelation = -pow((currentX - centerPoint.x + translationC) / majorA, 2.0) + 1;

	if (!positive) 
		mirrorEllipse = -1;

	while (ellipseRelation >= 0) {
		ellipseRelation = -pow((currentX - centerPoint.x + translationC) / majorA, 2.0) + 1;
		resultantZ = mirrorEllipse*sqrt(ellipseRelation) * minorB + centerPoint.z;

		glm::vec3 orbitVertices = glm::vec3(currentX, 0.0f, resultantZ);

		if (currentX <= -modelArray[index].aphelium or currentX >= modelArray[index].peryhelium)
			orbitVertices = glm::vec3(currentX, 0.0f, 0.0f);

		if (!positive)
			dynamicArray[index - 1].assignArrayMinus.push_back(orbitVertices);
		else
			dynamicArray[index-1].assignArrayPlus.push_back(orbitVertices);
			
		currentX -= 0.3;
	}
}

void Gravity::updatePosition(int index) {

	gravityVelocity[index] += resultantForce * refreshValue;
	modelArray[index].position += (modelArray[index].vMax + gravityVelocity[index]) * refreshValue;
}
