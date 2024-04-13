#include "Cube.h"

void Cube::Update(int programIndex)
{
	//Call update of primitive and passing the index of the program we want to use in this primitive
	Primitive::Update(programIndex);

	//If the exuction is not pause we calculate the transformations of the cube
	if (!GetPauseObject())
	{
		//Set the position of the cube changing the Y axis
		GetTransform()->position = GetTransform()->position + GetTransform()->forward * GetFVelocity();

		//Set the rotation of the cube changing the Y axis
		GetTransform()->rotation = GetTransform()->rotation + glm::vec3(0.f, 1.f, 0.f) * GetFAngulargVelocity();

		//To prevent the cube from leaving the screen we change the forward of the cube to keep it inside the window
		if (GetTransform()->position.y >= 0.5f || GetTransform()->position.y <= -0.5f)
		{
			GetTransform()->forward = GetTransform()->forward * -1.f;
		}
	}

	ApplyMatrix();

	if (GetRenderObject())
	{
		//Define what we want to draw
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
	}
	//Stop using the VAO indicated above
	glBindVertexArray(0);
}

void Cube::ApplyMatrix()
{
	//Initialize the 3 arrays
	SetTransitionMatrix(glm::mat4(1.0f));
	SetRotationMatrix(glm::mat4(1.0f));
	SetScaleMatrix(glm::mat4(1.0f));

	//Apply the translationMatrix taking into account the new position
	SetTransitionMatrix(GenerateTranslationMatrix(GetTransform()->position));

	//Apply the rotationMatrix taking into account the rotation in Y axis
	SetRotationMatrix(GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->rotation.y));
}

void Cube::InitVao()
{
	Primitive::InitVao();
}
