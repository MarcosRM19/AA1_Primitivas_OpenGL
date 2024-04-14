#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define SHADER ShaderProgram::Instance()

class ShaderProgram
{
private:
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;

	ShaderProgram() = default;

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator =(const ShaderProgram&) = delete;

public:
	inline static ShaderProgram& Instance()
	{
		static ShaderProgram shader;
		return shader;
	}

	std::vector<GLuint> compiledPrograms;

	std::string Load_File(const std::string& filePath);

	GLuint LoadShader(const std::string& filePath, GLuint shader);

	GLuint CreateProgram(const ShaderProgram& shaders);

	void AddProgram();

	// SETTER
	void SetVertexShader(GLuint vertexShader);
	void SetGeometryShader(GLuint geometryShader);
	void SetFragmentShader(GLuint fragmentShader);

};

