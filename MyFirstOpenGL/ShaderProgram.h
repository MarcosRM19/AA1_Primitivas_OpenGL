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

	ShaderProgram()
	{

	}

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

	GLuint LoadFragmentShader(const std::string& filePath);
	GLuint LoadGeometryShader(const std::string& filePath);
	GLuint LoadVertexShader(const std::string& filePath);

	GLuint CreateProgram(const ShaderProgram& shaders);

	void AddProgram()
	{
		compiledPrograms.push_back(SHADER.CreateProgram(SHADER));
	}

	// SETTER
	void SetVertexShader(GLuint vertexShader);
	void SetGeometryShader(GLuint geometryShader);
	void SetFragmentShader(GLuint fragmentShader);

};

