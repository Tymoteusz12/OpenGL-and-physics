#include "gravityPhysics.h"


Gravity::Gravity(double constG, double refreshValue) :
	constG(constG), refreshValue(refreshValue){}

void Gravity::loadSunData() {

	cout << "Loading sun data..." << endl;
	
	sun.mass = 1.99E30 * scale ;

	sun.radius = 6.96E8 * scale * 0.333f;

	modelArray.push_back(sun);
	gravityVelocity.push_back(glm::vec3(0.0f));
}

void Gravity::loadPlanetsData() {
	int modelAmount{};
	modelAmount = 9;

	cout << "Loading planet data... " << endl;

	double planetData[] = {
		//aphelion , perihelion, radius, mass
		69.8E9, 46.0E9, 2.4395E6, 0.33E24, // Mercury
		108.9E9, 107.5E9, 6.052E6, 4.87E24, // Venus
		152.1E9, 147.1E9, 6.378E6, 5.97E24, // Earth
		249.2E9, 206.6E9, 3.396E6, 0.642E24, // Mars

		816.6E9, 740.5E9, 7.1492E8, 1898E24, // Jupiter
		1514.5E9, 1352.6E9, 6.0268E8, 568.0E24, // Saturn
		3003.6E9, 2741.3E9, 2.5559E7, 86.8E24, // Uranus
		4545.7E9, 4444.5E9, 2.4764E7, 102.0E24, // Neptune
		5906.4E9, 4436.8E9 ,1.185E6, 0.0146E24// Pluto
	};

	for (int i = 0; i < modelAmount; i++) {
		
		planet.mass = planetData[i * 4 + 3] * scale;
		planet.radius = planetData[i * 4 + 2] * scale;
		planet.peryhelion = planetData[i * 4 + 1] * scale;
		planet.aphelion = planetData[i * 4] * scale;

		planet.position = glm::vec3(planet.peryhelion, 0.0f, 0.0f);

		double vMax = findModelSpeed(planet, modelArray[0]);

		planet.vMax = glm::vec3(0.0f, 0.0f, -vMax);

		modelArray.push_back(planet);
		gravityVelocity.push_back(glm::vec3(0.0f));
	}
}

double Gravity::findModelSpeed(modelData planet, modelData sun) {

	double constVal = -2 * constG * sun.mass * (1 / planet.aphelion - 1 / planet.peryhelion);
	double kepler = 1 - pow(planet.peryhelion / planet.aphelion, 2.0f);
	double vMax = sqrt(constVal / kepler);

	return vMax;
}

void Gravity::findResultantForce(int index) {

	resultantForce = glm::dvec3(0.0f);
	for (int i = 0; i < modelArray.size(); i++) {
		if (i != index) {

			double vectorLength = glm::length(modelArray[i].position - modelArray[index].position);
			glm::dvec3 direction = glm::normalize(modelArray[i].position - modelArray[index].position);
			glm::dvec3 force = glm::vec3(0.0f);

			if (vectorLength != 0.0f)
				force = ((constG * modelArray[i].mass) / (vectorLength * vectorLength)) * direction;

			resultantForce += force;
		}
	}
	updatePosition(index);
}

void Gravity::findEllipse(int index, bool positive) {

	double currentX = modelArray[index].peryhelion;
	double resultantZ = 0;
	double majorA = 0.5 * (modelArray[index].aphelion + modelArray[index].peryhelion);
	double minorB = 0.5 * (sqrt(pow(modelArray[index].aphelion, 2.0) + 2.0 * modelArray[index].aphelion * modelArray[index].peryhelion));
	double translationC = 0;
	int mirrorEllipse = 1;
	if (sqrt(pow(majorA, 2.0) - pow(minorB, 2.0) >= 0))
		translationC = modelArray[index].aphelion - majorA;

	glm::dvec3 centerPoint = modelArray[0].position;
	double ellipseRelation = -pow((currentX - centerPoint.x + translationC) / majorA, 2.0) + 1;

	if (!positive) 
		mirrorEllipse = -1;

	while (ellipseRelation >= 0) {
		ellipseRelation = -pow((currentX - centerPoint.x + translationC) / majorA, 2.0) + 1;
		resultantZ = mirrorEllipse*sqrt(ellipseRelation) * minorB + centerPoint.z;

		glm::dvec3 orbitVertices = glm::dvec3(currentX, 0.0f, resultantZ);

		if (currentX <= -modelArray[index].aphelion or currentX >= modelArray[index].peryhelion)
			orbitVertices = glm::dvec3(currentX, 0.0f, 0.0f);

		if (!positive)
			dynamicArray[index - 1].assignArrayMinus.push_back(orbitVertices);
		else
			dynamicArray[index-1].assignArrayPlus.push_back(orbitVertices);
			
		if(index >= 4)
			currentX -= 10.0*(double(index)*5.0+1.0);
		else
			currentX -= 10.0*(double(index) + 1.0);
	}
}

void Gravity::updatePosition(int index) {

	gravityVelocity[index] += resultantForce * refreshValue;
	modelArray[index].position += (modelArray[index].vMax + gravityVelocity[index]) * refreshValue;
}
