#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include "WindowInit.h"
#include "gravityPhysics.h"
#include "variables/variables.h"
#include "camera.h"
#include "cubeClass.h"
#include "model.h"
#include "variables/booleans.h"
#include "variables/complexTypes.h"
#include "variables/arrays.h"
#include "variables/vectors.h"
#include "cubemap.h"
#include "orbitClass.h"
#include "axisLines.h"
#include "asteroid.h"
#include <iostream>

using namespace std;
using namespace variables;
using namespace booleans;
using namespace complexTypes;
using namespace arrays;
using namespace vectors;

Camera mainCamera(width, height);
Gravity;
lastPosition lastPos;
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float deltaTime, Gravity &solarSystem, glm::vec3 asteroid) {
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS and !viewMode) {
		lastPos.cameraPosition = mainCamera.cameraPos;
		mainCamera.setPositionAndDirection(glm::vec3(0.0f, 5*solarSystem.modelArray[3].radius, 0.0f), -89.0f);
		viewMode = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS and viewMode) {
		mainCamera.cameraPos = lastPos.cameraPosition;
		mainCamera.setPositionAndDirection(mainCamera.cameraPos, 0.0f);
		viewMode = false;
	}
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS and !solarSystem.press) {
		mainCamera.cameraPos = solarSystem.modelArray[solarSystem.id++ % 11].position + glm::dvec3(2*solarSystem.modelArray[3].radius);
		solarSystem.press = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_RELEASE and solarSystem.press)
		solarSystem.press = false;

	if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
		mainCamera.cameraPos = asteroid;

	mainCamera.MoveCameraFunction(window, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	mainCamera.mouse_callback(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	
	if (button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_PRESS)
		mainCamera.mainMouse.leftButton = true;
	if(button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_RELEASE)
		mainCamera.mainMouse.leftButton = false;
	if (button == GLFW_MOUSE_BUTTON_RIGHT and action == GLFW_PRESS)
		mainCamera.mainMouse.rightButton = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT and action == GLFW_RELEASE)
		mainCamera.mainMouse.rightButton = false;
}

void loadViewModelTextures(model3D* viewModel) {
	viewModel->loadTexture("textures/sun_texture.jpg");
	viewModel->loadTexture("textures/mercury.png");
	viewModel->loadTexture("textures/venus.jpg");
	viewModel->loadTexture("textures/earth.jpg");
	viewModel->loadTexture("textures/moon.png");
	viewModel->loadTexture("textures/mars.jpg");
	viewModel->loadTexture("textures/jupiter.jpg");
	viewModel->loadTexture("textures/saturn.jpg");
	viewModel->loadTexture("textures/uranus.jpg");
	viewModel->loadTexture("textures/neptune.jpg");
	viewModel->loadTexture("textures/ceres.jpg");
	viewModel->loadTexture("textures/nightsky.jpg");
}

void findEllipse(Gravity &solarSystem) {
	for (unsigned int i = 1; i < solarSystem.modelArray.size(); i++) {
		solarSystem.dynamicArray.push_back(solarSystem.myVertices);
		solarSystem.findEllipse(i, true);
	}

	for (unsigned int i = 1; i < solarSystem.modelArray.size(); i++) {
		solarSystem.findEllipse(i, false);
	}
}

void updateModelPositions(Gravity &solarSystem, vector<Model> &models, CreateShader *shader, unsigned int index) {
		
		solarSystem.findResultantForce(index);
		float radiusToScale = solarSystem.modelArray[index].radius;
		glm::vec3 positionToDraw = solarSystem.modelArray[index].position;
		model = glm::mat4(1.0f);
		model = glm::translate(model, positionToDraw);
		model = glm::rotate(model, glm::radians(float(glfwGetTime()) * 6), glm::vec3(0.05f * (index+1) , 0.6f * (index+1), 0.0f));
		model = glm::scale(model, glm::vec3(radiusToScale));
		shader->setMat4("model", model);
		if(index == 0)
			models[0].Draw(*shader);
		else
			models[1].Draw(*shader);
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
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD \n";
		return -1;
	}

	CreateShader* BlockShader = new CreateShader("Shaders/VertexShaderCode.glsl", "Shaders/FragmentShaderCode.glsl");
	CreateShader* skyShader = new CreateShader("Shaders/cubeVertex.glsl", "Shaders/cubeFragment.glsl");
	CreateShader* orbitShader = new CreateShader("Shaders/orbitVertex.glsl", "Shaders/orbitFragment.glsl");
	CreateShader* test = new CreateShader("Shaders/testV.glsl", "Shaders/testF.glsl");
	CreateShader* asteroidShader = new CreateShader("Shaders/asteroidV.glsl", "Shaders/asteroidF.glsl");

	model3D* viewModel = new model3D(&mainCamera, BlockShader, glm::vec3(0.0f), glm::vec3(0.0f));
	{
		cout << "Loading models... " << endl;
		Model sunModel("models/sun.obj");
		Model planetModel("models/planet.obj");
		Model rock("models/rock.obj");

		cout << "Loading textures... " << endl;
		loadViewModelTextures(viewModel);

		vector<Model> models;
		models.push_back(sunModel);
		models.push_back(planetModel);

		axisLines axes(orbitShader);
		Gravity solarSystem(constG, refreshValue);
		Orbit planetOrbit(orbitShader, &solarSystem);

		solarSystem.loadSunData();
		solarSystem.loadPlanetsData();

		cubeMap skyBox(faces, skyboxVertices, sizeof(skyboxVertices));

		cout << "Finding orbit vertices..." << endl;
		findEllipse(solarSystem);
		planetOrbit.addVertices();
		
		cout << "Generating asteroid belt... " << endl;
		asteroidBelt asteroidInstance(asteroidShader, &rock, constG, solarSystem.modelArray[0].mass);
		asteroidInstance.findAsteroidMatrix(solarSystem);
		asteroidInstance.createBuffers();

		glm::vec3 ringTranslation = solarSystem.modelArray[7].position;

		float refreshTime = 0;
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);

		for (unsigned int i = 0; i <= 11; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, viewModel->myTextures[i]);
		}

		while (!glfwWindowShouldClose(window)) {

			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			projection = mainCamera.CreateProjectionMatix(viewAngle, width, height);
			view = mainCamera.CreateViewMatrix();

			processInput(window, deltaTime, solarSystem, asteroidInstance.asteroid[0].position);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			spotLightVecProperties[0] = mainCamera.cameraPos;
			spotLightVecProperties[1] = mainCamera.cameraFront;

			model = glm::mat4(1.0f);
			orbitShader->useProgram();
			orbitShader->setMat4("projection", projection);
			orbitShader->setMat4("view", view);
			orbitShader->setMat4("model", model);

			refreshTime += deltaTime;
			if (refreshTime >= 0.001f) {
				refreshTime = 0.0f;
				planetOrbit.drawOrbit(); 
				axes.drawAxes();
				orbitShader->setBool("isAxis", false);
				asteroidShader->useProgram();
				asteroidShader->setVec3("translation", -ringTranslation);
			}

			model = glm::mat4(1.0f);
			BlockShader->useProgram();
			viewModel->shaderPointer = BlockShader;
			BlockShader->setMat4("projection", projection);
			BlockShader->setMat4("view", view);
			BlockShader->setMat4("model", model);
			BlockShader->setVec3("viewPos", mainCamera.cameraPos);
			viewModel->setMaterialProperties(0, 32.0f);
			viewModel->setSpotLightProperties(spotLightVecProperties, spotLightFloatProperties);

			for (unsigned int i = 0; i < solarSystem.modelArray.size(); i++) {
				viewModel->setMaterialProperties(i, 32.0f);
				viewModel->setSpotLightProperties(spotLightVecProperties, spotLightFloatProperties);
				updateModelPositions(solarSystem, models, BlockShader, i);
			}

			test->useProgram();
			test->setMat4("projection", projection);
			test->setMat4("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, mainCamera.trans);
			model = glm::scale(model, glm::vec3(solarSystem.modelArray[3].radius));
			test->setInt("texture_diffuse1", 3);
			test->setMat4("model", model);
			planetModel.Draw(*test);
			
			ringTranslation += asteroidInstance.findDisplacement(solarSystem);
			asteroidShader->useProgram();
			asteroidShader->setMat4("projection", projection);
			asteroidShader->setMat4("view", view);
			asteroidShader->setInt("texture_diffuse1", 11);
			glActiveTexture(GL_TEXTURE11);
			glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id);
			for (unsigned int i = 0; i < rock.meshes.size(); i++) {
				glBindVertexArray(rock.meshes[i].vertexBuffer);
				glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT,
					0, asteroidInstance.amount);
 			}

			view = glm::mat4(glm::mat3(mainCamera.CreateViewMatrix()));
			skyBox.drawCubemap(view, projection, skyShader);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	delete BlockShader, skyShader, orbitShader, test, viewModel;
 	return 0;
}