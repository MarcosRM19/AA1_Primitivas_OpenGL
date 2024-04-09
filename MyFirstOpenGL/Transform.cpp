#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->forward = forward;
	this->scale = scale;
}