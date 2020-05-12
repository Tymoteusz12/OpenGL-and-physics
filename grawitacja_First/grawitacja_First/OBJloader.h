#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
using namespace std;
using namespace variables;
verticesState& loadOBJ(const char* file_path) {

	vector<glm::vec3> vertex_positions;
	vector<glm::vec3> vertex_normals;
	vector<glm::vec2> vertex_texCoords;

	vector<GLint> vertexPosIndices;
	vector<GLint> vertexNormalIndices;
	vector<GLint> vertexTextureIndices;

	vector<Vertex> vertices;

	static verticesState saveCondition;

	stringstream objReader;
	ifstream objFile(file_path);
	string line = "";
	string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;

	if (!objFile.is_open()) {
		cout << "Failed to open file " << endl;
	}

	while (getline(objFile, line)) {
		objReader.clear();
		objReader.str(line);
		objReader >> prefix;
		if (prefix == "v") {
			objReader >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt") {
			objReader >> temp_vec2.x >> temp_vec2.y;
			vertex_texCoords.push_back(temp_vec2);
		}
		else if (prefix == "vn") {
			objReader >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		else if (prefix == "f") {
			int counter = 0;
			while (objReader >> temp_glint) {
				if (counter == 0)
					vertexPosIndices.push_back(temp_glint);

				else if (counter == 1) 
					vertexTextureIndices.push_back(temp_glint);

				else if (counter == 2) 
					vertexNormalIndices.push_back(temp_glint);

				if (objReader.peek() == '/') {
					++counter;
					objReader.ignore(1, '/');
				}
				else if (objReader.peek() == ' ') {
					counter = 0;
					objReader.ignore(1, ' ');
				}
			}
		}
	}

	vertices.resize(vertexPosIndices.size(), Vertex());

		for (size_t i = 0; i < vertices.size(); i++) {
			vertices[i].positions = vertex_positions[vertexPosIndices[i] - 1];

			if (vertexTextureIndices.size() > 0) {
				vertices[i].texCoords = vertex_texCoords[vertexTextureIndices[i] - 1];
				saveCondition.textureExists = true;
			}

			if (vertexNormalIndices.size() > 0) {
				vertices[i].normals = vertex_normals[vertexNormalIndices[i] - 1];
				saveCondition.normalsExists = true;
			}
		}
		
	objFile.close();
	
	vertex_positions.clear();
	vertex_texCoords.clear();
	vertex_normals.clear();
	vertexPosIndices.clear();
	vertexTextureIndices.clear();
	vertexNormalIndices.clear();

	saveCondition.vertexPointer = vertices;

	return saveCondition;
}

class loadModel
{
public:
	loadModel() {}
	loadModel(verticesState& savedCondition) :
		textureExists(savedCondition.textureExists),
		normalsExists(savedCondition.normalsExists),
		modelProperties(savedCondition.vertexPointer)
	{
		separateVertex();
	}

	~loadModel() {
		cout << "Always clear memory when no used. Now you did. Used destructor of loadModel class." << endl;
	}

private:
	unsigned int modelBuffer, vertexBuffer;
	bool textureExists;
	bool normalsExists;
	vector<Vertex> modelProperties;
	vector<glm::vec3> tempPos;
	vector<glm::vec2> tempTextureCoords;
	vector<glm::vec3> tempNormals;

	void separateVertex() {
		unsigned int i = 0;
		cout << modelProperties.size() << endl;
		while (separateLoopState()) {
			tempPos.push_back(modelProperties[i].positions);
			if (textureExists)
				tempTextureCoords.push_back(modelProperties[i].texCoords);
			if (normalsExists)
				tempNormals.push_back(modelProperties[i].normals);
			i++;
		}
	}

	bool separateLoopState() {
		if (tempPos.size() + tempTextureCoords.size() + tempNormals.size() < modelProperties.size())
			return true;
		else return false;
	}

};