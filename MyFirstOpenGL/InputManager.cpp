#include "InputManager.h"

void InputManager::PauseResumeExecution(int key, int action)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		// Pause all objects
		for (Primitive* primitve : OBJECTS.GetPrimitives())
		{
			primitve->PauseResumeObject();
		}
	}
}

void InputManager::IncrementTransformsVelocities(int key, int action)
{
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		// Increment Velocities
		OBJECTS.IncrementTransforms();
	}
}

void InputManager::DecreaseTransformsVelocities(int key, int action)
{
	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		// Decrase Velocities
		OBJECTS.DecraseTransforms();
	}
}

void InputManager::ChangeBetweenLineAndFill(int key, int action)
{
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		// Change between fill and line
		for (Primitive* primitve : OBJECTS.GetPrimitives())
		{
			primitve->ChangeBetweenLineAndFill();
		}
	}
}

void InputManager::DisableActiveCube(int key, int action)
{
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		// Stop rendering cube
		OBJECTS.GetPrimitives()[0]->DisableActiveObject();
	}
}

void InputManager::DisableActiveOrhoedron(int key, int action)
{
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		// Stop rendering ortoedron
		OBJECTS.GetPrimitives()[1]->DisableActiveObject();
	}
}

void InputManager::DisableActivePyramid(int key, int action)
{
	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		// Stop rendering pyramid
		OBJECTS.GetPrimitives()[2]->DisableActiveObject();
	}
}
