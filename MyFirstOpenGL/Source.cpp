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

void main(){

	//Definir semillas del rand seg�n el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	GLFWwindow* window = InitProgram();

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		//Declarar intancia de gameobject
		Cube* cube = new Cube(glm::vec3(-0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);
		Orthoedron* orthoedron = new Orthoedron(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);
		Pyramid* pyramid = new Pyramid(glm::vec3(0.6f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), 0.01f, -1.f, 0.01f);

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

		GLuint vaoPuntos, vboPuntos;

		//Definimos cantidad de vao a crear y donde almacenarlos 
		glGenVertexArrays(1, &vaoPuntos);

		//Indico que el VAO activo de la GPU es el que acabo de crear
		glBindVertexArray(vaoPuntos);

		//Definimos cantidad de vbo a crear y donde almacenarlos
		glGenBuffers(1, &vboPuntos);

		//Indico que el VBO activo es el que acabo de crear y que almacenar� un array. Todos los VBO que genere se asignaran al �ltimo VAO que he hecho glBindVertexArray
		glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);		

		//Definimos modo de dibujo para cada cara si cambiamos el LINE por FILL 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//Ponemos los valores en el VBO creado
		//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * orthoedron->GetPoint().size(), orthoedron->GetPointData(), GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * pyramid->GetPoint().size(), pyramid->GetPointData(), GL_STATIC_DRAW);

		//Indicamos donde almacenar y como esta distribuida la informaci�n
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		//Indicamos que la tarjeta gr�fica puede usar el atributo 0
		glEnableVertexAttribArray(0);

		//Desvinculamos VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Desvinculamos VAO
		glBindVertexArray(0);

		//Indicar a la tarjeta GPU que programa debe usar
		glUseProgram(SHADER.compiledPrograms[0]);

		//Asignar valores iniciales al programa
		glUniform2f(glGetUniformLocation(SHADER.compiledPrograms[0], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
		//glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		
		glShadeModel(GL_FLAT);

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			double currentTime = glfwGetTime();

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			//Definimos que queremos usar el VAO con los puntos
			glBindVertexArray(vaoPuntos);
			
			//glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(orthoedron->ApplyMatrix()));
			pyramid->Update();

			glUniform1f(glGetUniformLocation(compiledPrograms[0], "u_Time"), currentTime);
			glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(pyramid->ApplyMatrix()));

			//Definimos que queremos dibujar
			glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
			glDrawArrays(GL_TRIANGLE_STRIP, 6, 10);

			//Dejamos de usar el VAO indicado anteriormente
			glBindVertexArray(0);

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