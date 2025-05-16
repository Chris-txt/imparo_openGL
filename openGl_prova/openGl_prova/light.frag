#version 330 core

out vec4 FragColor;

uniform vec4 lightColor;

void main()
{
	//colore del cubo uguale al colore che emette
	FragColor = lightColor;
}