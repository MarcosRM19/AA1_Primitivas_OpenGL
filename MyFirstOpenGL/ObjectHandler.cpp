#include "ObjectHandler.h"

void ObjectHandler::Add(Primitive* primitive)
{
	primitives.push_back(primitive);
}

void ObjectHandler::IncrementTransforms()
{
	//Iterate all primitive to increment the velocities 
	for (Primitive* primitive : primitives)
	{
		primitive->SetFVelocity(primitive->GetFVelocity() + primitive->GetFVelocity() * 0.1);
		primitive->SetFAngulargVelocity(primitive->GetFAngulargVelocity() + primitive->GetFAngulargVelocity() * 0.1);
		primitive->SetFScaleVelocity(primitive->GetFScaleVelocity() + primitive->GetFScaleVelocity() * 0.1);
	}
}

void ObjectHandler::DecraseTransforms()
{
	//Iterate all primitive to decrease the velocities 
	for (Primitive* primitive : primitives)
	{
		primitive->SetFVelocity(primitive->GetFVelocity() - primitive->GetFVelocity() * 0.1);
		primitive->SetFAngulargVelocity(primitive->GetFAngulargVelocity() - primitive->GetFAngulargVelocity() * 0.1);
		primitive->SetFScaleVelocity(primitive->GetFScaleVelocity() - primitive->GetFScaleVelocity() * 0.1);
	}
}

std::vector<Primitive*> ObjectHandler::GetPrimitives()
{
	return primitives;
}
