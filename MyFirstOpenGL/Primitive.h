#pragma once

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "ShaderProgram.h"

#include "Transform.h"
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Primitive
{
private:
	Transform* transform;
	float fVelocity;
	float fAngularVelocity;
	float fScaleVelocity;
	std::vector<GLfloat> point;


	GLuint vaoPuntos, vboPuntos;

public:
	glm::mat4 transitionMatrix, rotationMatrix, scaleMatrix;
	//Constructor
	Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, std::vector<GLfloat> point, float fScaleVelocity);

	//Matrix
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	glm::mat4 GenerateScaleMatrix(glm::vec3 newScale);

	virtual void Update(int programIndex)
	{
		glUseProgram(SHADER.compiledPrograms[programIndex]);
		glUniform2f(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
		glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(transitionMatrix));
		glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
		glBindVertexArray(vaoPuntos);
	}

	virtual void ApplyMatrix()
	{
	}

	virtual void InitVao();

	//Getters
	Transform* GetTransform();

	float GetFVelocity();
	float GetFAngulargVelocity();
    float GetFScaleVelocity();

	GLfloat* GetPointData();
	std::vector<GLfloat> GetPoint();

	//Setter
	void SetTransitionMatrix(glm::mat4 matrix);
	void SetRotationMatrix(glm::mat4 matrix);
	void SetScaleMatrix(glm::mat4 matrix);

};

