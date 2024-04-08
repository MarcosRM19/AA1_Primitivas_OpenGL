#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class ShaderProgram
{
private:
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;

public:
	std::string Load_File(const std::string& filePath);

	GLuint LoadFragmentShader(const std::string& filePath);
	GLuint LoadGeometryShader(const std::string& filePath);
	GLuint LoadVertexShader(const std::string& filePath);

	GLuint CreateProgram(const ShaderProgram& shaders);

	// SETTER
	void SetVertexShader(GLuint vertexShader);
	void SetGeometryShader(GLuint geometryShader);
	void SetFragmentShader(GLuint fragmentShader);

	// GETTERS
	GLuint GetVertexShader();
	GLuint GetGeometryShader();
	GLuint GetFragmentShader();

};

