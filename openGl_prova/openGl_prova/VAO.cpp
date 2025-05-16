#include "VAO.h"

VAO::VAO()
{
	//generali con un solo oggetto ciascuno
	glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	//configura gli attributi dei vertex così che openGL possa leggerli
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	//abilità gli attributi così che openGL sappia come usarli
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	//rende VAO il vertex array rincipale incollandolo
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
