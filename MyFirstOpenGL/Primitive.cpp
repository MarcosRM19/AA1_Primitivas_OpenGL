#include "Primitive.h"

Primitive::Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, std::vector<GLfloat> point, float fScaleVelocity)
{
	transform = new Transform(position, rotation, forward, scale);
	this->fVelocity = fVelocity;
	this->fAngularVelocity = fAngularVelocity;
	this->point = point;
	this->fScaleVelocity = fScaleVelocity;
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

void Primitive::InitVao()
{
	//Definimos cantidad de vao a crear y donde almacenarlos 
	glGenVertexArrays(1, &vaoPuntos);

	//Indico que el VAO activo de la GPU es el que acabo de crear
	glBindVertexArray(vaoPuntos);

	//Definimos cantidad de vbo a crear y donde almacenarlos
	glGenBuffers(1, &vboPuntos);

	//Indico que el VBO activo es el que acabo de crear y que almacenar un array. Todos los VBO que genere se asignaran al ultimo VAO que he hecho glBindVertexArray
	glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);

	//Definimos modo de dibujo para cada cara si cambiamos el LINE por FILL 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Ponemos los valores en el VBO creado
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * GetPoint().size(), GetPointData(), GL_STATIC_DRAW);

	//Indicamos donde almacenar y como esta distribuida la informacion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Indicamos que la tarjeta grafica puede usar el atributo 0
	glEnableVertexAttribArray(0);

	//Desvinculamos VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Desvinculamos VAO
	glBindVertexArray(0);

	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(SHADER.compiledPrograms[0]);
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
