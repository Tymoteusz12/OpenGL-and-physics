#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
using namespace std;

class CreateShader 
{

private:
	string Shader;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;
	const char* ShaderSource[1];
	int VertexSuccess, FragmentSuccess, ProgramSuccess;
	char infoLog[512];
public: 
	unsigned int NaszProgram;

	CreateShader(const char* vertexShader, const char* fragmentShader);

	void setBool(const string& name, bool value) const;

	void setInt(const string& name, int value) const;

	void setFloat(const string& name, float value);

	void setVec2(const string& name, const glm::vec2& value);

	void setVec2(const string& name, float x, float y);

	void setVec3(const string& name, const glm::vec3& value);

	void setVec3(const string& name, float x, float y, float z);

	void setVec4(const string& name, const glm::vec4& value);

	void setVec4(const string& name, float x, float y, float z, float w);

	void setMat2(const string& name, const glm::mat2& mat);

	void setMat3(const string& name, const glm::mat3& mat);

	void setMat4(const string& name, const glm::mat4& mat);

	void useProgram();

};
#endif