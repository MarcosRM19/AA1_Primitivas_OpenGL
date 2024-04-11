#include "ShaderProgram.h"
#include "Windows.h"

#include "Cube.h"
#include "Orthoedron.h"
#include "Pyramid.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Definir nuevo tama�o del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);

	glUniform2f(glGetUniformLocation(SHADER.compiledPrograms[0], "windowSize"), iFrameBufferWidth, iFrameBufferHeight);
}

GLFWwindow* InitProgram()
{
	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	//Configuramos la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Asignamos funci�n de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_BACK);

	return window;
}

void PreparePrimitive(Cube* cube, Orthoedron* orthoedron, Pyramid* pyramid)
{
	//Declarar vec2 para definir el offset
	glm::vec2 offset = glm::vec2(0.f, 0.f);

	//Compilar shaders
	SHADER.SetVertexShader(SHADER.LoadVertexShader("MyFirstVertexShader.glsl"));
	SHADER.SetGeometryShader(SHADER.LoadGeometryShader("MyFirstGeometryShader.glsl"));
	SHADER.SetFragmentShader(SHADER.LoadFragmentShader("MyFirstFragmentShader.glsl"));

	//Compilar programa
	SHADER.AddProgram();

	//Definimos color para limpiar el buffer de color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	cube->InitVao();
	orthoedron->InitVao();
	pyramid->InitVao();

	//Asignar valores iniciales al programa
	glUniform2f(glGetUniformLocation(SHADER.compiledPrograms[0], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	glShadeModel(GL_FLAT);
}

void main(){

	//Definir semillas del rand seg�n el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	GLFWwindow* window = InitProgram();

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		Cube* cube = new Cube(glm::vec3(-0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);
		Orthoedron* orthoedron = new Orthoedron(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);
		Pyramid* pyramid = new Pyramid(glm::vec3(0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);
		PreparePrimitive(cube, orthoedron, pyramid);

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			
			cube->Update();
			orthoedron->Update();
			pyramid->Update();

			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(window);
		}

		//Desactivar y eliminar programa
		glUseProgram(0);
		glDeleteProgram(SHADER.compiledPrograms[0]);

	}else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}

	//Finalizamos GLFW
	glfwTerminate();

}