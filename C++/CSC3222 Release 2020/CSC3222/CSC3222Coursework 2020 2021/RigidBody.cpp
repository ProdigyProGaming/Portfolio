#include "RigidBody.h"

using namespace NCL;
using namespace CSC3222;

RigidBody::RigidBody()	{
	inverseMass = 10.0f;
	elasticity  = 0.5f;
	//Set default dampening factor
	dampeningFactor = 0.95f;

	deleteThisObject = false;
}


RigidBody::~RigidBody()	{

}
