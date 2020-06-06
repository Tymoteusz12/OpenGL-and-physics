#version 430 core

out vec4 FragColor;
in vec3 color;

uniform bool isAxis;

void main(){
	if(isAxis)
		FragColor = vec4(color, 1.0f);
	else
		FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}