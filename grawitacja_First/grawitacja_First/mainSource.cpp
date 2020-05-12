#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include "WindowInit.h"
#include "variables.h"
#include "camera.h"
#include "cubeClass.h"
#include "model.h"
#include "booleans.h"
#include "complexTypes.h"
#include "arrays.h"
#include "vectors.h"

#include <iostream>

using namespace std;
using namespace variables;
using namespace booleans;
using namespace complexTypes;
using namespace arrays;
using namespace vectors;

Camera mainCamera(width, height, gravityForce);

float findModelSpeed(modelProperties, modelProperties);
glm::vec3 countResultantForce(vector <modelProperties>&, int);

lastPosition lastPos;
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void setDirectionAndPosition(glm::vec3 cameraPos, float cameraPitch) {
	mainCamera.cameraPos = cameraPos;
	mainCamera.pitch = cameraPitch;
	mainCamera.yaw = -90.0f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(mainCamera.yaw)) * cos(glm::radians(mainCamera.pitch));
	direction.y = sin(glm::radians(mainCamera.pitch));
	direction.z = sin(glm::radians(mainCamera.yaw)) * cos(glm::radians(mainCamera.pitch));
	mainCamera.cameraFront = glm::normalize(direction);
}

void processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		isFlying = false;
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		isFlying = true;
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS and !viewMode) {
		lastPos.cameraPosition = mainCamera.cameraPos;
		setDirectionAndPosition(glm::vec3(0.0f,50.0f, 0.0f), -89.0f);
		viewMode = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS and viewMode) {
		mainCamera.cameraPos = lastPos.cameraPosition;
		setDirectionAndPosition(mainCamera.cameraPos, 0.0f);
		viewMode = false;
	}
	
	mainCamera.MoveCameraFunction(window, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	mainCamera.mouse_callback(window, xpos, ypos);
}

void updateModelPosition(vector <modelProperties> &modelArray, Model &mainModel, CreateShader *shader, int index) {

		glm::vec3 force = countResultantForce(modelArray, index);

		tempVec[index] += force * refreshValue;

		modelArray[index].position += (modelArray[index].vMax + tempVec[index])*refreshValue;

		model = glm::mat4(1.0f);
		if (index == 0)
			bodySize = glm::vec3(1.0f);
		else
			bodySize = glm::vec3(0.3f);
		model = glm::translate(model, modelArray[index].position);
		model = glm::scale(model, bodySize);
		shader->setMat4("model", model);
		mainModel.Draw(*shader);

}

glm::vec3 countResultantForce(vector <modelProperties>& modelArray, int index) {

	glm::vec3 resultantForce = glm::vec3(0.0f);
		
	for (int i = 0; i < modelArray.size(); i++) {
		if (i == index) continue;

		float vectorLength = glm::length(modelArray[i].position - modelArray[index].position);
		glm::vec3 direction = glm::normalize(modelArray[i].position - modelArray[index].position);
		glm::vec3 force = glm::vec3(0.0f);

		if (vectorLength != 0.0f)
			force = ((constG * modelArray[i].mass) / (vectorLength * vectorLength)) * direction;

		resultantForce += force;

		}

	return resultantForce;
}

void loadModelProperties() {

	modelProperties temp{};
	int modelAmount{};

	cout << "Load number of models: " << endl;
	cin >> modelAmount;

	cout << "Load sun mass: " << endl;
	cin >> temp.mass;

	modelArray.push_back(temp);
	tempVec.push_back(glm::vec3(0.0f));

	for (int i = 0; i < modelAmount; i++) {

		cout << i + 1 << " Enter model mass: " << endl;
		cin >> temp.mass;

		cout << i + 1 << " Enter model aphelium: " << endl;
		cin >> temp.aphelium;

		cout << i + 1 << " Enter model peryhelium: " << endl;
		cin >> temp.peryhelium;

	//	cout << i + 1 << " Enter model radius: " << endl;
		//temp.radius = 1;

		temp.position = glm::vec3(0.0f, 0.0f, temp.peryhelium);

		float vMax = findModelSpeed(temp, modelArray[0]);

		temp.vMax = glm::vec3(vMax, 0.0f, 0.0f);

		modelArray.push_back(temp);
		tempVec.push_back(glm::vec3(0.0f));
	}
}

float findModelSpeed(modelProperties model, modelProperties main) {

	float constVal = -2 * constG * main.mass * (1 / model.aphelium - 1 / model.peryhelium);
	float kepler = 1 - pow(model.peryhelium / model.aphelium, 2.0f);
	float vMax = sqrt(constVal / kepler);

	return vMax;
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

	model3D* viewModel = new model3D(&mainCamera, BlockShader, gravityForce, glm::vec3(0.0f));
	Model mainModel("C:/Users/Tymek/Documents/BlenderObjFiles/sun2.obj");
	
	viewModel->loadTexture("textures/suntxt.jpg");

	glEnable(GL_DEPTH_TEST);

	loadModelProperties();

	while (!glfwWindowShouldClose(window)) {

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, viewModel->myTextures[0]);

			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			processInput(window, deltaTime);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			projection = mainCamera.CreateProjectionMatix(viewAngle, width, height);
			view = mainCamera.CreateViewMatrix();

			spotLightVecProperties[0] = mainCamera.cameraPos;
			spotLightVecProperties[1] = mainCamera.cameraFront;

			BlockShader->useProgram();
			viewModel->shaderPointer = BlockShader;
			BlockShader->setMat4("projection", projection);
			BlockShader->setMat4("view", view);
			BlockShader->setMat4("model", model);
			BlockShader->setVec3("viewPos", mainCamera.cameraPos);
			viewModel->setMaterialProperties(0, 32.0f);
			viewModel->setSpotLightProperties(spotLightVecProperties, spotLightFloatProperties);
			
			for (int i = 0; i < modelArray.size(); i++) 
				updateModelPosition(modelArray, mainModel, BlockShader, i);
			
			glfwSwapBuffers(window);

			glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}