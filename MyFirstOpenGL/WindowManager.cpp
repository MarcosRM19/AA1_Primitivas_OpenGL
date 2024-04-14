#include "WindowManager.h"

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Define new viewport size
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

void WindowManager::InitProgram()
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

	this->window = window;
}

void WindowManager::PreparePrimitive(Cube* cube, Orthoedron* orthoedron, Pyramid* pyramid)
{
	//Declare vec2 to define the offset
	glm::vec2 offset = glm::vec2(0.f, 0.f);

	//Compile the first shaders
	SHADER.SetVertexShader(SHADER.LoadShader("VertexShader.glsl", GL_VERTEX_SHADER));
	SHADER.SetGeometryShader(SHADER.LoadShader("GeometryShader.glsl", GL_GEOMETRY_SHADER));
	SHADER.SetFragmentShader(SHADER.LoadShader("FragmentShader.glsl", GL_FRAGMENT_SHADER));

	//Compile the first program
	SHADER.AddProgram();

	//Compile the second shaders
	SHADER.SetVertexShader(SHADER.LoadShader("VertexShader.glsl", GL_VERTEX_SHADER));
	SHADER.SetGeometryShader(SHADER.LoadShader("GeometryShader.glsl", GL_GEOMETRY_SHADER));
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

void WindowManager::CreatePrimitive()
{
	//Set the velocities, the calculation of 1000 / 16 comes from converting milliseconds to seconds shooting at a refresh rate of 60 frames per second (FPS)

	//Set a object move a 1 unity per second
	float translationSpeed = 1.0f / (1000.0f / 16.0f);

	//Set a object rotate 90 grades per second
	float rotationSpeed = 90.0f / (1000.0f / 16.0f);

	//Set a object scale doubles in size every second
	float sceleSpeed = 1.0f / (1000.0f / 16.0f);

	//Create the 3 primitive
	Cube* cube = new Cube(glm::vec3(-0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), translationSpeed, rotationSpeed, sceleSpeed);
	Orthoedron* orthoedron = new Orthoedron(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f), translationSpeed, rotationSpeed, sceleSpeed);
	Pyramid* pyramid = new Pyramid(glm::vec3(0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), translationSpeed, rotationSpeed, sceleSpeed);

	//Set the 3 primitives in a vector of primitive
	OBJECTS.Add(cube);
	OBJECTS.Add(orthoedron);
	OBJECTS.Add(pyramid);

	//Prepare the shader, programs and set vao and vbo of the primitive
	PreparePrimitive(cube, orthoedron, pyramid);
}

void WindowManager::DesactivateProgram()
{
	//Deactivate and delete programs
	glUseProgram(0);
	glDeleteProgram(SHADER.compiledPrograms[0]);
	glDeleteProgram(SHADER.compiledPrograms[1]);
}

GLFWwindow* WindowManager::GetWindows()
{
	return window;
}
