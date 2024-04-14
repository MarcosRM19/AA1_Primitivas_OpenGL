#include "ShaderProgram.h"

std::string ShaderProgram::Load_File(const std::string& filePath)
{
	std::ifstream file(filePath);

	std::string fileContent;
	std::string line;

	//Throw an error if the file could not be opened
	if (!file.is_open()) {
		std::cerr << "No se ha podido abrir el archivo: " << filePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//Read the content and dump it into the auxiliary variable
	while (std::getline(file, line)) {
		fileContent += line + "\n";
	}

	//Close data stream and return content
	file.close();

	return fileContent;
}

GLuint ShaderProgram::LoadShader(const std::string& filePath, GLuint shader)
{
	//Create a fragment shader
	GLuint _shader = glCreateShader(shader);

	//Use the function created to read the fragment shader and store it
	std::string sShaderCode = Load_File(filePath);
	const char* cShaderSource = sShaderCode.c_str();

	//Link the fragment shader with its source code
	glShaderSource(_shader, 1, &cShaderSource, nullptr);

	//Compile the fragment shader
	glCompileShader(_shader);

	//Check compilation errors
	GLint success;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

	//If the compilation has been successful we return the fragment shader
	if (success) {
		return _shader;
	}
	else {
		//Obtain length of the log
		GLint logLength;
		glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logLength);

		//Obtenemos the log
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(_shader, logLength, nullptr, errorLog.data());

		//Show the log and end the program
		std::cerr << "An error occurred while loading the fragment shader:  " << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

GLuint ShaderProgram::CreateProgram(const ShaderProgram& shaders)
{
	//Create GPU program
	GLuint program = glCreateProgram();

	//Verify that a vertex shader exists and attach it to the program
	if (shaders.vertexShader != 0) {
		glAttachShader(program, shaders.vertexShader);
	}

	//Verify that a geometry shader existsand attach it to the program
	if (shaders.geometryShader != 0) {
		glAttachShader(program, shaders.geometryShader);
	}

	//Verify that a fragment shader existsand attach it to the program
	if (shaders.fragmentShader != 0) {
		glAttachShader(program, shaders.fragmentShader);
	}

	//Link the program
	glLinkProgram(program);

	//Get program status
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	//Return program if everything is correct or show log in case of error
	if (success) {

		//Release resources
		if (shaders.vertexShader != 0) {
			glDetachShader(program, shaders.vertexShader);
		}

		//Release resources
		if (shaders.geometryShader != 0) {
			glDetachShader(program, shaders.geometryShader);
		}

		//Release resources
		if (shaders.fragmentShader != 0) {
			glDetachShader(program, shaders.fragmentShader);
		}

		return program;
	}
	else {

		//Obtain length of the log
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		//Store log
		std::vector<GLchar> errorLog(logLength);
		glGetProgramInfoLog(program, logLength, nullptr, errorLog.data());

		std::cerr << "Error linking the program:" << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void ShaderProgram::AddProgram()
{
	compiledPrograms.push_back(SHADER.CreateProgram(SHADER));
}

void ShaderProgram::SetVertexShader(GLuint vertexShader)
{
	this->vertexShader = vertexShader;
}

void ShaderProgram::SetGeometryShader(GLuint geometryShader)
{
	this->geometryShader = geometryShader;
}

void ShaderProgram::SetFragmentShader(GLuint fragmentShader)
{
	this->fragmentShader = fragmentShader;
}