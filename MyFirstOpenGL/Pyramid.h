#pragma once

#include "Primitive.h"

class Pyramid : public Primitive
{
public:
    //Constructor
    Pyramid(glm::vec3 position, glm::vec3 rotation,
        glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, float fScaleVelocity)
        : Primitive(position, rotation, forward, scale, fVelocity, fAngularVelocity,
            {
                -0.5f, -0.5f, -0.5f,
                +0.5f, -0.5f, -0.5f,
                +0.0f, +0.5f, +0.0f,

                -0.5f, -0.5f, +0.5f,
                +0.5f, -0.5f, +0.5f,
                +0.0f, +0.5f, +0.0f,

                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, +0.5f,
                +0.0f, +0.5f, +0.0f,

                +0.5f, -0.5f, -0.5f,
                +0.5f, -0.5f, +0.5f,
                +0.0f, +0.5f, +0.0f,

                -0.5f, -0.5f, +0.5f,
                -0.5f, -0.5f, -0.5f,
                +0.0f, +0.5f, +0.0f,


            }, fScaleVelocity) {
    }

    glm::mat4 ApplyMatrix() override;
};

