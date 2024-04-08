#pragma once
#include "Primitive.h"


class Cube : public Primitive
{
public:
	//Constructor
	Cube( glm::vec3 position, glm::vec3 rotation,
		glm::vec3 forward, float fVelocity, float fAngularVelocity)
		: Primitive(position, rotation, forward, fVelocity, fAngularVelocity, 
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
			}) {		
	}
};

