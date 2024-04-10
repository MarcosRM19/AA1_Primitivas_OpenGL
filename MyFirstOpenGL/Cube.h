#pragma once
#include "Primitive.h"


class Cube : public Primitive
{
public:
	//Constructor
	Cube( glm::vec3 position, glm::vec3 rotation,
		glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, float fScaleVelocity)
		: Primitive(position, rotation, forward, scale, fVelocity, fAngularVelocity, 
			{
                -0.2f, +0.2f, -0.2f,
                +0.2f, +0.2f, -0.2f,
                -0.2f, -0.2f, -0.2f,
                +0.2f, -0.2f, -0.2f,
                +0.2f, -0.2f, +0.2f,
                +0.2f, +0.2f, -0.2f,
                +0.2f, +0.2f, +0.2f,
                -0.2f, +0.2f, -0.2f,
                -0.2f, +0.2f, +0.2f,
                -0.2f, -0.2f, -0.2f,
                -0.2f, -0.2f, +0.2f,
                +0.2f, -0.2f, +0.2f,
                -0.2f, +0.2f, +0.2f,
                +0.2f, +0.2f, +0.2f
			}, fScaleVelocity) {
	}
    void Update() override;
    glm::mat4 ApplyMatrix() override;
};

