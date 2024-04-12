#include "Primitive.h"

Primitive::Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, std::vector<GLfloat> point, float fScaleVelocity)
{
	transform = new Transform(position, rotation, forward, scale);
	this->fVelocity = fVelocity;
	this->fAngularVelocity = fAngularVelocity;
	this->point = point;
	this->fScaleVelocity = fScaleVelocity;

	renderObject = true;
	pauseObject = false;
	fillObject = true;

	time = 0;
}

glm::mat4 Primitive::GenerateTranslationMatrix(glm::vec3 translation)
{
	return glm::translate(glm::mat4(1.f), translation);;
}

glm::mat4 Primitive::GenerateRotationMatrix(glm::vec3 axis, float fDegrees)
{
	return glm::rotate(glm::mat4(1.f), glm::radians(fDegrees), glm::normalize(axis));
}

glm::mat4 Primitive::GenerateScaleMatrix(glm::vec3 newScale)
{
	return glm::scale(glm::mat4(1.f), newScale);
}

void Primitive::Update(int programIndex)
{
	//Set which program has to use
	glUseProgram(SHADER.compiledPrograms[programIndex]);

	//Pass the information from the matreized to the shaders
	glUniform2f(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
	glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "translationMatrix"), 1, GL_FALSE, glm::value_ptr(transitionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	
	glBindVertexArray(vaoPuntos);
}

void Primitive::ApplyMatrix()
{
}

void Primitive::InitVao()
{
	//Define the amount of vacuum to be created and where to store it 
	glGenVertexArrays(1, &vaoPuntos);

	//Indicate that the active VAO of the GPU is the one I just created
	glBindVertexArray(vaoPuntos);

	//Define the number of vbos to create and where to store them
	glGenBuffers(1, &vboPuntos);

	//Indicate that the active VBO is the one I just created and that it stores an array. All the VBOs I generate will be assigned to the last VAO I made glBindVertexArray
	glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);

	//Define drawing mode for each face
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Put the values ​​in the created VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * GetPoint().size(), GetPointData(), GL_STATIC_DRAW);

	//Indicate where to store and how the information is distributed
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Indicate that the graphics card can use attribute 0
	glEnableVertexAttribArray(0);

	//Unlink VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Unlink VAO
	glBindVertexArray(0);

}

void Primitive::ChangeBetweenLineAndFill()
{
	fillObject = !fillObject;
	if (fillObject)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

bool Primitive::DisableActiveObject()
{
	return renderObject = !renderObject;
}

bool Primitive::PauseResumeObject()
{
	//We save the time when the execution is paused and when it is resumed we set the the time at the time when the execution was done
	if (!pauseObject)
		time = glfwGetTime();
	else
		glfwSetTime(time);

	return pauseObject = !pauseObject;
}

Transform* Primitive::GetTransform()
{
	return transform;
}

float Primitive::GetFVelocity()
{
	return fVelocity;
}

float Primitive::GetFAngulargVelocity()
{
	return fAngularVelocity;
}

float Primitive::GetFScaleVelocity()
{
	return fScaleVelocity;
}

GLfloat* Primitive::GetPointData()
{
	GLfloat* pointData = point.data();
	return pointData;
}

std::vector<GLfloat> Primitive::GetPoint()
{
	return point;
}

bool Primitive::GetRenderObject()
{
	return renderObject;
}

bool Primitive::GetPauseObject()
{
	return pauseObject;
}

void Primitive::SetTransitionMatrix(glm::mat4 matrix)
{
	transitionMatrix = matrix;
}

void Primitive::SetRotationMatrix(glm::mat4 matrix)
{
	rotationMatrix = matrix;
}

void Primitive::SetScaleMatrix(glm::mat4 matrix)
{
	scaleMatrix = matrix;
}

void Primitive::SetFVelocity(float fVelocity)
{
	this->fVelocity = fVelocity;
}

void Primitive::SetFAngulargVelocity(float fAngularVelocity)
{
	this->fAngularVelocity = fAngularVelocity;
}

void Primitive::SetFScaleVelocity(float fScaleVelocity)
{
	this->fScaleVelocity = fScaleVelocity;
}

