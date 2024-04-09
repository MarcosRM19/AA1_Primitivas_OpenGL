#pragma once
#include "Primitive.h"


class Orthoedron : public Primitive
{
private:
    bool isIncreasing;

public:
    //Constructor
    Orthoedron(glm::vec3 position, glm::vec3 rotation,
        glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity)
        : Primitive(position, rotation, forward, scale, fVelocity, fAngularVelocity,
            {
                -0.2f, +0.5f, -0.2f,
                +0.2f, +0.5f, -0.2f,
                -0.2f, -0.5f, -0.2f,
                +0.2f, -0.5f, -0.2f,
                +0.2f, -0.5f, +0.2f,
                +0.2f, +0.5f, -0.2f,
                +0.2f, +0.5f, +0.2f,
                -0.2f, +0.5f, -0.2f,
                -0.2f, +0.5f, +0.2f,
                -0.2f, -0.5f, -0.2f,
                -0.2f, -0.5f, +0.2f,
                +0.2f, -0.5f, +0.2f,
                -0.2f, +0.5f, +0.2f,
                +0.2f, +0.5f, +0.2f
            }) {
        isIncreasing = false;
        
    }

    glm::mat4 ApplyMatrix() override;
};
