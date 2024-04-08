#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Primitive
{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 forward;
	float fVelocity;
	float fAngularVelocity;

public:
	//constructor
	Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, float fVelocity, float fAngularVelocity);

	//Matrix
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	glm::mat4 GenerateScaleMatrix(glm::vec3 newScale);

	//Setters
	void SetPosition(glm::vec3 newPosition);
	void SetRotation(glm::vec3 newRotation);
	void SetForward(glm::vec3 newForward);

	//Getters
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetForward();
	float GetFVelocity();
	float GetFAngulargVelocity();

};

