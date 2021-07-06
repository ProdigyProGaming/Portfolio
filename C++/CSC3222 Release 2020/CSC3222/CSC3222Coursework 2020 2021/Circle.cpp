#include "Circle.h"

using namespace NCL;
using namespace CSC3222;

//Circle class to manage circle colliders
//Constructor takes radius, position, type, whether the object is static like a wall, and the specific object name
//Passes the position, type, static bool and specific object name to collision volume constructor
Circle::Circle(float newRadius, Vector2 newPosition, std::string newType, bool newIsStatic, ObjectTypes newObjectType, RigidBody* newBody) : CollisionVolume(newPosition, newType, newIsStatic, newObjectType, newBody) {
	//Sets the circle radius
	setRadius(newRadius);
}
//Getter for the radius returns the radius
float Circle::getRadius() const {
	return radius;
}
//Setter for the radius sets the radius value to the given float
void Circle::setRadius(float newRadius) {
	radius = newRadius;
}
