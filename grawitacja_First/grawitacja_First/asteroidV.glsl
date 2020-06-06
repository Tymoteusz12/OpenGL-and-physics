#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 translation;
void main(){

	if(gl_InstanceID == 0)
		gl_Position = projection * view * model * vec4(aPos, 1.0);

	else if(gl_InstanceID != 0 && gl_InstanceID < 10000)
		gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);

	else{
		mat4 ringModel = instanceMatrix;
		ringModel[3][0] += translation.x;
		ringModel[3][1] += translation.y;
		ringModel[3][2] += translation.z;
		gl_Position = projection * view * ringModel * vec4(aPos, 1.0);
	}


	TexCoords = aTexCoords;

}