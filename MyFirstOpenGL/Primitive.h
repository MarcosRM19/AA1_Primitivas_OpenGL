#pragma once

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Transform.h"

#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Primitive
{
private:
	Transform* transform;

	float fVelocity;
	float fAngularVelocity;
	float fScaleVelocity;

	bool renderObject;
	bool pauseObject;
	bool fillObject;

	std::vector<GLfloat> point;
	GLuint vaoPuntos, vboPuntos;

	float time;

public:
	glm::mat4 transitionMatrix, rotationMatrix, scaleMatrix;

	//Constructor
	Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, std::vector<GLfloat> point, float fScaleVelocity);

	//Matrix
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	glm::mat4 GenerateScaleMatrix(glm::vec3 newScale);
	virtual void ApplyMatrix();

	virtual void Update(int programIndex);

	virtual void InitVao();

	virtual void ChangeBetweenLineAndFill();

	bool DisableActiveObject();
	bool PauseResumeObject();

	//Getters
	Transform* GetTransform();

	float GetFVelocity();
	float GetFAngulargVelocity();
    float GetFScaleVelocity();

	GLfloat* GetPointData();
	std::vector<GLfloat> GetPoint();

	bool GetRenderObject();
	bool GetPauseObject();

	//Setter
	void SetTransitionMatrix(glm::mat4 matrix);
	void SetRotationMatrix(glm::mat4 matrix);
	void SetScaleMatrix(glm::mat4 matrix);

	void SetFVelocity(float fVelocity);
	void SetFAngulargVelocity(float fAngularVelocity);
	void SetFScaleVelocity(float fScaleVelocity);
};

