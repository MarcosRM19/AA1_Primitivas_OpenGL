#pragma once
#include "Primitive.h"


class Orthoedron : public Primitive
{
private:
    bool isIncreasing;

public:
    //Constructor
    Orthoedron(glm::vec3 position, glm::vec3 rotation,
        glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, float fScaleVelocity)
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
            }, fScaleVelocity) {
        isIncreasing = false;
        
    }
    void Update(int programIndex) override;
    void ApplyMatrix() override;
    void InitVao() override;
};
