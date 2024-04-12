#include "Pyramid.h"

void Pyramid::Update(int programIndex)
{
	//Call update of primitive and passing the index of the program we want to use in this primitive
	Primitive::Update(programIndex);

	currentTime = glfwGetTime();

	//If the exuction is not pause we calculate the transformations of the pyramid
	if (!GetPauseObject())
	{
		//Set the position of the pyramid changing the Y axis
		GetTransform()->position = GetTransform()->position + GetTransform()->forward * GetFVelocity();

		//Set the rotation of the pyramid changing the X axis and Y axis
		GetTransform()->rotation = GetTransform()->rotation + glm::vec3(1.f, 1.f, 0.f) * GetFAngulargVelocity();

		//To prevent the pyramid from leaving the screen we change the forward of the pyramid to keep it inside the window
		if (GetTransform()->position.y >= 0.5f || GetTransform()->position.y <= -0.5f)
		{
			GetTransform()->forward = GetTransform()->forward * -1.f;
		}

		//Pass the information of the current time to the fragmentShader of the second program to change the color of the pyramid taking into account the current time
		glUniform1f(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "u_Time"), currentTime);
	}
	ApplyMatrix();
		
	if (GetRenderObject())
	{
		//Define what we want to draw
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
		glDrawArrays(GL_TRIANGLE_STRIP, 6, 4);
	}
	//Stop using the VAO indicated above
	glBindVertexArray(0);
}

void Pyramid::ApplyMatrix()
{
	//Initialize the 3 arrays
	SetTransitionMatrix(glm::mat4(1.0f));
	SetRotationMatrix(glm::mat4(1.0f));
	SetScaleMatrix(glm::mat4(1.0f));

	//Apply the translationMatrix taking into account the new position
	SetTransitionMatrix(GenerateTranslationMatrix(GetTransform()->position));

	//Apply the rotationMatrix taking into account the rotation, first in X axis and then in Y axis
	SetRotationMatrix(GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), GetTransform()->rotation.x) 
		* GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->rotation.y));

}

void Pyramid::InitVao()
{
	Primitive::InitVao();

}
