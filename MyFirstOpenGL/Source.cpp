#include "InputManager.h"

void main(){
	//Define rand seeds according to time
	srand(static_cast<unsigned int>(time(NULL)));

	//Prepare the window to start working
	WM.InitProgram();

	//Initialize GLEW and control errors
	if (glewInit() == GLEW_OK) {

		//Create and init the 3 primitives
		WM.CreatePrimitive();

		//Generate the game loop
		while (!glfwWindowShouldClose(WM.GetWindows())) 
		{
			//Checking the inputs
			IM.Update();

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
			glfwSwapBuffers(WM.GetWindows());
		}

		WM.DesactivateProgram();

	}
	else 
	{
		std::cout << "It crushed" << std::endl;
		glfwTerminate();
	}

	//Finish GLFW
	glfwTerminate();
}