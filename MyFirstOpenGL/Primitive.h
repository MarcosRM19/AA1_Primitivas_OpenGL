#pragma once

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Transform.h"
#include <vector>

class Primitive
{
private:
	Transform* transform;
	float fVelocity;
	float fAngularVelocity;
	float fScaleVelocity = 0.99;
	std::vector<GLfloat> point;
	glm::mat4 modelMatrix;

public:
	//Constructor
	Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, std::vector<GLfloat> point);

	//Matrix
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	glm::mat4 GenerateScaleMatrix(glm::vec3 newScale);

	virtual glm::mat4 ApplyMatrix()
	{
		return modelMatrix;
	}

	//Getters
	Transform* GetTransform();
	glm::mat4 GetModelMatrix();

	float GetFVelocity();
	float GetFAngulargVelocity();
    float GetFScaleVelocity();

	GLfloat* GetPointData();
	std::vector<GLfloat> GetPoint();

	//Setter
	void SetModelMatrix(glm::mat4 matrix);

};

