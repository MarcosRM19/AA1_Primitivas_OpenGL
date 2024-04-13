#include "Orthoedron.h"

void Orthoedron::Update(int programIndex)
{
	//Call update of primitive and passing the index of the program we want to use in this primitive
	Primitive::Update(programIndex);

	//If the exuction is not pause we calculate the transformations of the orthoedron
	if (!GetPauseObject())
	{
		//modifying the scale, depending on whether the orthoedron has to be growing or not, the scale in Y will multiply or divide
		if (isIncreasing)
			GetTransform()->scale.y /= (1 - GetFScaleVelocity());
		else
			GetTransform()->scale.y *= (1 - GetFScaleVelocity());

		//Set the rotation of the orthoedron changing the Z axis
		GetTransform()->rotation = GetTransform()->rotation + glm::vec3(0.f, 0.f, 1.f) * GetFAngulargVelocity();

		//To scale and descale the orthoedron so that it becomes a cube, we ensure that the scale is not less than half and at the same time that it is not greater than the original scale.
		if (GetTransform()->scale.y >= 1.f || GetTransform()->scale.y <= 0.5f)
		{
			isIncreasing = !isIncreasing;
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

void Orthoedron::ApplyMatrix()
{
	//Initialize the 3 arrays
	SetTransitionMatrix(glm::mat4(1.0f));
	SetRotationMatrix(glm::mat4(1.0f));
	SetScaleMatrix(glm::mat4(1.0f));
	
	//Apply the scaleMatrix taking into account the new scale
	SetScaleMatrix(GenerateScaleMatrix(GetTransform()->scale));

	//Apply the rotationMatrix taking into account the rotation in Z axis
	SetRotationMatrix(GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), GetTransform()->rotation.z));

}

void Orthoedron::InitVao()
{
	Primitive::InitVao();

}
