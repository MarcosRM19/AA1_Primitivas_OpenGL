#pragma once

#include <vector>

#include "Primitive.h"

#define OBJECTS ObjectHandler::Instance()

class ObjectHandler
{
	ObjectHandler() = default;

	ObjectHandler(const ObjectHandler&) = delete;
	ObjectHandler& operator = (const ObjectHandler&) = delete;

public:
	inline static ObjectHandler& Instance()
	{
		static ObjectHandler manager;
		return manager;
	}
	std::vector<Primitive*> primitives;

	void Add(Primitive* primitive)
	{
		primitives.push_back(primitive);
	}
	void IncrementTransforms()
	{
		for (Primitive* primitive : primitives)
		{
			primitive->SetFVelocity(primitive->GetFVelocity() + 0.01f);
			primitive->SetFAngulargVelocity(primitive->GetFAngulargVelocity() + 0.01f);
			primitive->SetFScaleVelocity(primitive->GetFScaleVelocity() + 0.01f);
		}
	}
	void DecraseTransforms()
	{
		for (Primitive* primitive : primitives)
		{
			primitive->SetFVelocity(primitive->GetFVelocity() - 0.01f);
			primitive->SetFAngulargVelocity(primitive->GetFAngulargVelocity() - 0.01f);
			primitive->SetFScaleVelocity(primitive->GetFScaleVelocity() - 0.01f);
		}
	}
};

