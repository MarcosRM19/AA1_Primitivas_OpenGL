#pragma once
#include "ObjectHandler.h"

#define IM InputManager::Instance()

class InputManager
{
private:
	InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator = (const InputManager&) = delete;

public:
	inline static InputManager& Instance()
	{
		static InputManager manager;
		return manager;
	}

	void PauseResumeExecution(int key, int action);
	void IncrementTransformsVelocities(int key, int action);
	void DecreaseTransformsVelocities(int key, int action);
	void ChangeBetweenLineAndFill(int key, int action);
	void DisableActiveCube(int key, int action);
	void DisableActiveOrhoedron(int key, int action);
	void DisableActivePyramid(int key, int action);
};

