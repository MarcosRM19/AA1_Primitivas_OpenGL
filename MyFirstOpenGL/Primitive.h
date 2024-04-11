#pragma once

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "ShaderProgram.h"

#include "Transform.h"
#include <vector>

class Primitive
{
private:
	Transform* transform;
	float fVelocity;
	float fAngularVelocity;
	float fScaleVelocity;
	std::vector<GLfloat> point;
	glm::mat4 modelMatrix;

	GLuint vaoPuntos, vboPuntos;

public:
	//Constructor
	Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, std::vector<GLfloat> point, float fScaleVelocity);

	//Matrix
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);
	glm::mat4 GenerateScaleMatrix(glm::vec3 newScale);

	virtual void Update()
	{
		glUniformMatrix4fv(glGetUniformLocation(SHADER.compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(ApplyMatrix()));
		glBindVertexArray(vaoPuntos);
	}

	virtual glm::mat4 ApplyMatrix()
	{
		return modelMatrix;
	}

	virtual void InitVao()
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
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

	//Getters
	Transform* GetTransform();
	glm::mat4 GetModelMatrix();

	float GetFVelocity();
	float GetFAngulargVelocity();
    float GetFScaleVelocity();

	GLfloat* GetPointData();
	std::vector<GLfloat> GetPoint();

	//Setter
	void SetModelMatrix(glm::mat4 matrix);

};

