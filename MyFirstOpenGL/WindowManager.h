#pragma once
#include "ObjectHandler.h"
#include "ShaderProgram.h"

#include "Cube.h"
#include "Orthoedron.h"
#include "Pyramid.h"

#define WM WindowManager::Instance()

class WindowManager
{
private:
	WindowManager() = default;

	WindowManager(const WindowManager&) = delete;
	WindowManager& operator = (const WindowManager&) = delete;

	GLFWwindow* window;

public:
	inline static WindowManager& Instance()
	{
		static WindowManager manager;
		return manager;
	}

	void InitProgram();
	void PreparePrimitive(Cube* cube, Orthoedron* orthoedron, Pyramid* pyramid);
	void CreatePrimitive();
	void DesactivateProgram();

	// Getter
	GLFWwindow* GetWindows();

};

