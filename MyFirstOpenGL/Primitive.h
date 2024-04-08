#pragma once

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Transform.h"

class Primitive
{
private:
	Transform* transform;
	float fVelocity;
	float fAngularVelocity;

public:
	//Constructor
	Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, float fVelocity, float fAngularVelocity);

	//Matrix
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	glm::mat4 GenerateScaleMatrix(glm::vec3 newScale);

	//Setters
	void SetTransform(Transform transform);

	//Getters
	Transform* GetTransform();

	float GetFVelocity();
	float GetFAngulargVelocity();

};

