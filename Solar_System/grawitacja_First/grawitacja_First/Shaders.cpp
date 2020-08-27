#include "used_classes/headers/Shaders.h"

CreateShader::CreateShader(const char* vertexShader, const char* fragmentShader) {

	ifstream meVertexInput(vertexShader);
	ifstream meFragmentInput(fragmentShader);
	if (!meVertexInput.good()) {
		cout << "Failed to load file. " << vertexShader << endl;
		exit(1);
	}
	if (!meFragmentInput.good()) {
		cout << "Failed to load file. " << fragmentShader << endl;
		exit(1);
	}

	Shader = string(istreambuf_iterator<char>(meVertexInput),
		istreambuf_iterator<char>());

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	ShaderSource[0] = Shader.c_str();
	glShaderSource(vertexShaderID, 1, ShaderSource, NULL);
	glCompileShader(vertexShaderID);
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &VertexSuccess);
	if (!VertexSuccess) {

		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		cout << "Vertex compilation failed: " << infoLog << endl;
	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	Shader = string(istreambuf_iterator<char>(meFragmentInput), istreambuf_iterator<char>());
	ShaderSource[0] = Shader.c_str();

	glShaderSource(fragmentShaderID, 1, ShaderSource, NULL);
	glCompileShader(fragmentShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &FragmentSuccess);

	if (!FragmentSuccess) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		cout << "Fragment compilation failed: " << infoLog << endl;
	}

	NaszProgram = glCreateProgram();
	glAttachShader(NaszProgram, vertexShaderID);
	glAttachShader(NaszProgram, fragmentShaderID);
	glLinkProgram(NaszProgram);

	glGetProgramiv(NaszProgram, GL_LINK_STATUS, &ProgramSuccess);
	if (!ProgramSuccess) {
		glGetProgramInfoLog(NaszProgram, 512, NULL, infoLog);
		cout << "Shader program not linked successfully, " << infoLog << endl;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void CreateShader::setBool(const string& name, bool value) const {
	glUniform1i(glGetUniformLocation(NaszProgram, name.c_str()), (int)value);
}

void CreateShader::setInt(const string& name, int value) const {
	glUniform1i(glGetUniformLocation(NaszProgram, name.c_str()), value);
}

void CreateShader::setFloat(const string& name, float value) {
	glUniform1f(glGetUniformLocation(NaszProgram, name.c_str()), value);
}

void CreateShader::setVec2(const string& name, const glm::vec2& value) {
	glUniform2fv(glGetUniformLocation(NaszProgram, name.c_str()), 1, &value[0]);
}

void CreateShader::setVec2(const string& name, float x, float y) {
	glUniform2f(glGetUniformLocation(NaszProgram, name.c_str()), x, y);
}

void CreateShader::setVec3(const string& name, const glm::vec3& value) {
	glUniform3fv(glGetUniformLocation(NaszProgram, name.c_str()), 1, &value[0]);
}

void CreateShader::setVec3(const string& name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(NaszProgram, name.c_str()), x, y, z);
}

void CreateShader::setVec4(const string& name, const glm::vec4& value) {
	glUniform4fv(glGetUniformLocation(NaszProgram, name.c_str()), 1, &value[0]);
}

void CreateShader::setVec4(const string& name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(NaszProgram, name.c_str()), x, y, z, w);
}

void CreateShader::setMat2(const string& name, const glm::mat2& mat) {
	glUniformMatrix2fv(glGetUniformLocation(NaszProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void CreateShader::setMat3(const string& name, const glm::mat3& mat) {
	glUniformMatrix3fv(glGetUniformLocation(NaszProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void CreateShader::setMat4(const string& name, const glm::mat4& mat) {
	glUniformMatrix4fv(glGetUniformLocation(NaszProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void CreateShader::useProgram() {
	glUseProgram(NaszProgram);
}