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
                -0.2, +0.5, +0.2,
                +0.2, +0.5, +0.2,
                +0.0, -0.5, +0.2,
            }, fScaleVelocity) {
    }

    glm::mat4 ApplyMatrix() override;
};

