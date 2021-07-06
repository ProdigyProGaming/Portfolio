#include "Environment.h"

using namespace NCL;
using namespace CSC3222;

//Environment class for potnetially storing world collisions (ladders and walls)
Environment::Environment() : SimObject() {
	inverseMass = 0;
}

Environment::~Environment() {
}

bool Environment::UpdateObject(float dt) {
	return true;
}