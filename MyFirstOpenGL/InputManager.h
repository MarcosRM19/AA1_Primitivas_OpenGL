#pragma once
#include "WindowManager.h"

#define IM InputManager::Instance()

class InputManager
{
private:
	bool pause;

	InputManager()
	{
		pause = false;
	}

	InputManager(const InputManager&) = delete;
	InputManager& operator = (const InputManager&) = delete;


public:
	inline static InputManager& Instance()
	{
		static InputManager manager;
		return manager;
	}

	void Update();

	void PauseResumeExecution(int key, int action);
	void IncrementTransformsVelocities(int key, int action);
	void DecreaseTransformsVelocities(int key, int action);
	void ChangeBetweenLineAndFill(int key, int action);
	void DisableActiveCube(int key, int action);
	void DisableActiveOrhoedron(int key, int action);
	void DisableActivePyramid(int key, int action);

	bool GetPause();
};

