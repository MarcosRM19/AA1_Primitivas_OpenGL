#pragma once

#include <glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Transform
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 forward;
	glm::vec3 scale;

	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale);
};

