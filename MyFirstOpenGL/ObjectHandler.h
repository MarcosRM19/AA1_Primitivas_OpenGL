#pragma once
#include <vector>

#include "Primitive.h"

#define OBJECTS ObjectHandler::Instance()

class ObjectHandler
{
private:
	ObjectHandler() = default;

	ObjectHandler(const ObjectHandler&) = delete;
	ObjectHandler& operator = (const ObjectHandler&) = delete;

	std::vector<Primitive*> primitives;

public:
	inline static ObjectHandler& Instance()
	{
		static ObjectHandler manager;
		return manager;
	}

	void Add(Primitive* primitive);
	void IncrementTransforms();
	void DecraseTransforms();

	// Getters
	std::vector<Primitive*> GetPrimitives();
};

