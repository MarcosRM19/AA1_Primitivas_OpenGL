#pragma once

#include <glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Transform
{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 forward;

public:
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward);

	//Setters
	void SetPosition(glm::vec3 newPosition);
	void SetRotation(glm::vec3 newRotation);
	void SetForward(glm::vec3 newForward);

	//Getters
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetForward();
};

