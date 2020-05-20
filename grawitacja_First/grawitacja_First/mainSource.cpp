#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include "WindowInit.h"
#include "gravityPhysics.h"
#include "variables.h"
#include "camera.h"
#include "cubeClass.h"
#include "model.h"
#include "booleans.h"
#include "complexTypes.h"
#include "arrays.h"
#include "vectors.h"
#include "cubemap.h"
#include "orbitClass.h"
#include <iostream>

using namespace std;
using namespace variables;
using namespace booleans;
using namespace complexTypes;
using namespace arrays;
using namespace vectors;

Camera mainCamera(width, height);

lastPosition lastPos;
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS and !viewMode) {
		lastPos.cameraPosition = mainCamera.cameraPos;
		mainCamera.setPositionAndDirection(glm::vec3(0.0f,50.0f, 0.0f), -89.0f);
		viewMode = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS and viewMode) {
		mainCamera.cameraPos = lastPos.cameraPosition;
		mainCamera.setPositionAndDirection(mainCamera.cameraPos, 0.0f);
		viewMode = false;
	}
	
	mainCamera.MoveCameraFunction(window, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	mainCamera.mouse_callback(window, xpos, ypos);
}

void updateModelPositions(Gravity &solarSystem, Model &mainModel, CreateShader *shader, int index) {

		solarSystem.findResultantForce(index);
		float radiusToScale = solarSystem.modelArray[index].radius;
		glm::vec3 positionToDraw = solarSystem.modelArray[index].position;
		model = glm::mat4(1.0f);
		model = glm::translate(model, positionToDraw);
		model = glm::scale(model, glm::vec3(radiusToScale));
		shader->setMat4("model", model);
		mainModel.Draw(*shader);
}

int main(void)
{
	glfwInit();

	CreateWindow* object = new CreateWindow;
	GLFWwindow* window = object->window;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD \n";
		return -1;
	}

	CreateShader* BlockShader = new CreateShader("VertexShaderCode.glsl", "FragmentShaderCode.glsl");
	CreateShader* skyShader = new CreateShader("cubeVertex.glsl", "cubeFragment.glsl");
	CreateShader* orbitShader = new CreateShader("orbitVertex.glsl", "orbitFragment.glsl");

	model3D* viewModel = new model3D(&mainCamera, BlockShader, glm::vec3(0.0f), glm::vec3(0.0f));
	Model mainModel("C:/Users/Tymek/Documents/BlenderObjFiles/sun2.obj");
	
	viewModel->loadTexture("textures/suntxt.jpg");

	Orbit planetOrbit(orbitShader);
	Gravity solarSystem(constG, refreshValue);
	
	solarSystem.loadSunData();
	solarSystem.loadPlanetsData();

	cubeMap skyBox(faces, skyboxVertices, sizeof(skyboxVertices));

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window, deltaTime);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, viewModel->myTextures[0]);

		projection = mainCamera.CreateProjectionMatix(viewAngle, width, height);
		view = mainCamera.CreateViewMatrix();

		spotLightVecProperties[0] = mainCamera.cameraPos;
		spotLightVecProperties[1] = mainCamera.cameraFront;

		model = glm::mat4(1.0f);
		orbitShader->useProgram();
		orbitShader->setMat4("projection", projection);
		orbitShader->setMat4("view", view);
		orbitShader->setMat4("model", model);
		for (int i = 0; i < solarSystem.modelArray.size(); i++) {
			vector<glm::vec3> pathVertices = solarSystem.findOrbitPath(i, deltaTime);
			if (pathVertices.size() != 0) {
				planetOrbit.addVertices(pathVertices);
				planetOrbit.drawOrbit();
			}
		}

		BlockShader->useProgram();
		viewModel->shaderPointer = BlockShader;
		BlockShader->setMat4("projection", projection);
		BlockShader->setMat4("view", view);
		BlockShader->setMat4("model", model);
		BlockShader->setVec3("viewPos", mainCamera.cameraPos);
		viewModel->setMaterialProperties(0, 32.0f);
		viewModel->setSpotLightProperties(spotLightVecProperties, spotLightFloatProperties);
			
		for (int i = 0; i < solarSystem.modelArray.size(); i++) 
			updateModelPositions(solarSystem, mainModel, BlockShader, i);

		view = glm::mat4(glm::mat3(mainCamera.CreateViewMatrix()));
		skyBox.drawCubemap(view, projection, skyShader);
			
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}