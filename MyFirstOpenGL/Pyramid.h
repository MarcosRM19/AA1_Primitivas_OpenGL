#pragma once
#include "Primitive.h"

class Pyramid : public Primitive
{
private:
    double currentTime;

public:
    //Constructor
    Pyramid(glm::vec3 position, glm::vec3 rotation,
        glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, float fScaleVelocity)
        : Primitive(position, rotation, forward, scale, fVelocity, fAngularVelocity,
            {        
                // Triangle Fan
                +0.0f, +0.2f, +0.0f,
                -0.2f, -0.2f, +0.2f,
                +0.2f, -0.2f, +0.2f,
                +0.2f, -0.2f, -0.2f,
                -0.2f, -0.2f, -0.2f,
                -0.2f, -0.2f, +0.2f,
                
                // Triangle Strip
                +0.2f, -0.2f, +0.2f,
                -0.2f, -0.2f, +0.2f,
                +0.2f, -0.2f, -0.2f,
                -0.2f, -0.2f, -0.2f
            }, fScaleVelocity) {
    }
    void Update(int programIndex) override;
    void ApplyMatrix() override;
    void InitVao() override;
};

