#version 330 core
//posizione del cubo
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	//imposta la posizione del cubo
	gl_Position = camMatrix * model * vec4(aPos, 1.0f);
}