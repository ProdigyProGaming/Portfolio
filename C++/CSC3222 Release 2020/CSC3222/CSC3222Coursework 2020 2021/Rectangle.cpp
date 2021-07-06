#include "Rectangle.h"

using namespace NCL;
using namespace CSC3222;

//Rectangle class to manage rectangle colliders
//Constructor takes half sizes, position, type, whether the object is static like a wall, and the specific object name
//Passes the position, type, static bool and specific object name to collision volume constructor
Rectangle::Rectangle(float newHalfWidth, float newHalfHeight, Vector2 newPosition, std::string newType, bool newIsStatic, ObjectTypes newObjectType, RigidBody* newBody): CollisionVolume(newPosition, newType, newIsStatic, newObjectType, newBody) {
	//Set the half sizes
	setHalfWidth(newHalfWidth);
	setHalfHeight(newHalfHeight);
}

//Get the half sizes
float Rectangle::getHalfWidth() const {
	return halfSize.x;
}
float Rectangle::getHalfHeight() const {
	return halfSize.y;
}
Vector2 Rectangle::getHalfSize() const {
	return halfSize;
}

//Set the half sizes
void Rectangle::setHalfWidth(float newHalfWidth) {
	halfSize.x = newHalfWidth;
}
void Rectangle::setHalfHeight(float newHalfHeight) {
	halfSize.y = newHalfHeight;
}