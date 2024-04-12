#include "ShaderProgram.h"
#include "InputManager.h"
#include "Windows.h"

#include "Cube.h"
#include "Orthoedron.h"
#include "Pyramid.h"

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {
	
	//Define new viewport size
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

GLFWwindow* InitProgram()
{
	//Initialize GLFW to manage windowsand inputs
	glfwInit();

	//Windows configuration
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Initialize the window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Assign a callback function for when the frame buffer is modified
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Define workspace
	glfwMakeContextCurrent(window);

	//Allow GLEW to use experimental features
	glewExperimental = GL_TRUE;

	//Activate cull face
	glEnable(GL_CULL_FACE);

	//Indicate culling side
	glCullFace(GL_BACK);

	//We return window because we need it to future command
	return window;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Set if the execution is paused or resumed
	IM.PauseResumeExecution(key, action);

	//Since we want the inputs to only work when the execution is not paused, we look to see if any of the figures are paused because that means that the entire execution is paused
	if (!OBJECTS.GetPrimitives()[0]->GetPauseObject())
	{
		//All the inputs reaction except the pause and resume input
		IM.IncrementTransformsVelocities(key, action);
		IM.DecreaseTransformsVelocities(key, action);
		IM.ChangeBetweenLineAndFill(key, action);
		IM.DisableActiveCube(key, action);
		IM.DisableActiveOrhoedron(key, action);
		IM.DisableActivePyramid(key, action);
	}
}

void PreparePrimitive(Cube* cube, Orthoedron* orthoedron, Pyramid* pyramid)
{
	//Declare vec2 to define the offset
	glm::vec2 offset = glm::vec2(0.f, 0.f);

	//Compile the first shaders
	SHADER.SetVertexShader(SHADER.LoadShader("MyFirstVertexShader.glsl", GL_VERTEX_SHADER));
	SHADER.SetGeometryShader(SHADER.LoadShader("MyFirstGeometryShader.glsl", GL_GEOMETRY_SHADER));
	SHADER.SetFragmentShader(SHADER.LoadShader("MyFirstFragmentShader.glsl", GL_FRAGMENT_SHADER));

	//Compile the first program
	SHADER.AddProgram();

	//Compile the second shaders
	SHADER.SetVertexShader(SHADER.LoadShader("MyFirstVertexShader.glsl", GL_VERTEX_SHADER));
	SHADER.SetGeometryShader(SHADER.LoadShader("MyFirstGeometryShader.glsl", GL_GEOMETRY_SHADER));
	SHADER.SetFragmentShader(SHADER.LoadShader("PyramidFragmentShader.glsl", GL_FRAGMENT_SHADER));

	//Compile the second program
	SHADER.AddProgram();

	//Define color to clear the color buffer
	glClearColor(0.f, 0.f, 0.f, 1.f);

	cube->InitVao();
	orthoedron->InitVao();
	pyramid->InitVao();

	//Assign initial values ​​to programs
	glUniform2f(glGetUniformLocation(SHADER.compiledPrograms[0], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
	glUniform2f(glGetUniformLocation(SHADER.compiledPrograms[1], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	glShadeModel(GL_FLAT);
}

void main(){

	//Define rand seeds according to time
	srand(static_cast<unsigned int>(time(NULL)));

	//Prepare the window to start working
	GLFWwindow* window = InitProgram();

	//Initialize GLEW and control errors
	if (glewInit() == GLEW_OK) {

		//Create the 3 primitive
		Cube* cube = new Cube(glm::vec3(-0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);
		Orthoedron* orthoedron = new Orthoedron(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);
		Pyramid* pyramid = new Pyramid(glm::vec3(0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);
		
		//Set the 3 primitives in a vector of primitive
		OBJECTS.Add(cube);
		OBJECTS.Add(orthoedron);
		OBJECTS.Add(pyramid);

		//Prepare the shader, programs and set vao and vbo of the primitive
		PreparePrimitive(cube, orthoedron, pyramid);

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) 
		{
			//Pull the events (buttons, keys, mouse...)
			glfwPollEvents();

			glfwSetKeyCallback(window, KeyCallback);

			//Clean the buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			
			for (int i = 0; i < OBJECTS.GetPrimitives().size(); i++)
			{
				int index = 0;
				if (i == 2)
					index = 1;

				OBJECTS.GetPrimitives()[i]->Update(index);
			}

			//Change buffers
			glFlush();
			glfwSwapBuffers(window);
		}

		//Deactivate and delete programs
		glUseProgram(0);
		glDeleteProgram(SHADER.compiledPrograms[0]);
		glDeleteProgram(SHADER.compiledPrograms[1]);

	}else {
		std::cout << "It crushed" << std::endl;
		glfwTerminate();
	}

	//Finish GLFW
	glfwTerminate();

}