#pragma once

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "ShaderProgram.h"

#include "Transform.h"
#include <vector>

class Primitive
{
private:
	Transform* transform;
	float fVelocity;
	float fAngularVelocity;
	float fScaleVelocity;
	std::vector<GLfloat> point;
	glm::mat4 transitionMatrix, rotationMatrix, scaleMatrix;

	GLuint vaoPuntos, vboPuntos;

public:
	//Constructor
	Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, std::vector<GLfloat> point, float fScaleVelocity);

	//Matrix
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	glm::mat4 GenerateScaleMatrix(glm::vec3 newScale);

	virtual void Update()
	{
		glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[0], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(transitionMatrix));
		glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[0], "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[0], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
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

