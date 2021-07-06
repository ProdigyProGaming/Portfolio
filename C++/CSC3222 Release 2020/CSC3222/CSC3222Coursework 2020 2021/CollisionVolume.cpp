#include "CollisionVolume.h"
#include "Circle.h"

using namespace NCL;
using namespace CSC3222;

//Contructor for collision volume sets given variables
CollisionVolume::CollisionVolume(Vector2 newPosition, std::string newType, bool newIsStatic, ObjectTypes newObjectType, RigidBody* newBody)
{
	childCollisionVolumes = new std::vector<CollisionVolume*>();
	position = newPosition;
	type = newType;
	isStatic = newIsStatic;
	objectType = newObjectType;


	body = newBody;
}


CollisionVolume::~CollisionVolume()
{
}


RigidBody* CollisionVolume::getBody() const {
	return body;
}


//Sets the position of all colliders
void CollisionVolume::setPosition(Vector2 newPosition) {
	//Get the variance between the current position and the new position to calculate how much to move the sub colliders by
	//Sub colliders have their own positions so this prevents updating each one individually
	float xVariance = newPosition.x - position.x;
	float yVariance = newPosition.y - position.y;
	//Set the main position
	position = newPosition;
	//For every sub collider
	for (auto childCV : *childCollisionVolumes) {
		//Set the sub colliders position to the original position plus the variance
		childCV->setPosition(Vector2(position.x + xVariance, position.y + yVariance));
	}
}

//Getter for the position value
Vector2 CollisionVolume::getPosition() const {
	return position;
}
//Getter for the type value
std::string CollisionVolume::getType() const {
	return type;
}
//Getter for the static value
bool CollisionVolume::getIsStatic() const {
	return isStatic;
}
//Getter for the object name value
ObjectTypes CollisionVolume::getObjectType() const {
	return objectType;
}
//Function to add sub collider
void CollisionVolume::addChildVolume(CollisionVolume* newChildVolume) {
	childCollisionVolumes->emplace_back(newChildVolume);
}
//Function for comparison of floats
bool floatComparison(float a, float b) {
	float epsilon = 0.005f;
	return (fabs(a - b) < epsilon);
}
//Collision checker function takes in a volume and a collision pair to be filled if a collision occurs
bool CollisionVolume::CheckCollision(CollisionVolume* volume1, CollisionPair* cp) {
	//Boolean for if the volumes are the same type (AABB AABB, Cirlce Cirlce, AABB Cirlce)
	bool sameShape = this->type == volume1->type;

	//If both colliders are circles
	if (sameShape && this->type == "Circle") {
		//Get the distance on each axis between the two volumes
		float distanceX = this->position.x - volume1->position.x;
		float distanceY = this->position.y - volume1->position.y;

		//Get the distance as one float
		float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
		//If the distance is less than the two radius added together
		if (distance <= this->getRadius() + volume1->getRadius()) {
			//Set the colliders in the collision pair
			cp->a = this;
			cp->b = volume1;
			//Set the penetration
			cp->penetration = (this->getRadius() + volume1->getRadius()) - distance;
			//Calculate the normal using magnitude
			Vector2 direction = volume1->getPosition() - this->getPosition();
			float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
			if (!floatComparison(magnitude, 0.0f)) {
				cp->normal = Vector2(direction.x / magnitude, direction.y / magnitude);
			}
			//Return true for a collision occured
			return true;
		}
		//Return false if a collision didnt occur
		return false;
	}
	//If both colliders are rectangles
	else if (sameShape && this->type == "Rectangle") {
		bool var1, var2, var3, var4;
		//Get the variables for if each axis is overlapping
		var1 = this->position.x - this->getHalfWidth() <= volume1->position.x + volume1->getHalfWidth();
		var2 = this->position.x + this->getHalfWidth() >= volume1->position.x - volume1->getHalfWidth();
		var3 = this->position.y - this->getHalfHeight() <= volume1->position.y + volume1->getHalfHeight();
		var4 = this->position.y + this->getHalfHeight() >= volume1->position.y - volume1->getHalfHeight();

		//If all the variables are true
		if (var1 && var2 && var3 && var4) {
			//Set the colliders in the collision pair
			cp->a = this;
			cp->b = volume1;
			//Calculate which axis has the least amount of intersection
			float xIntersection = (getHalfWidth() + volume1->getHalfWidth()) - (volume1->position.x - position.x);
			float yIntersection = (getHalfHeight() + volume1->getHalfHeight()) - abs(volume1->position.y - position.y);

			//Get the direction vector and calculate magnitude
			Vector2 direction = volume1->getPosition() - this->getPosition();

			
			float magnitudeX = sqrt(direction.x * direction.x);
			float magnitudeY = sqrt(direction.y * direction.y);
			if (!floatComparison(magnitudeX, 0.0f) && !floatComparison(magnitudeY, 0.0f)) {
				//If statement for which axis is less
				if (xIntersection < yIntersection) {
					//Set the normal
					cp->normal = Vector2(direction.x / magnitudeX, 0);
					//Set the penetration
					cp->penetration = xIntersection;
				}
				else {
					//Set the normal
					cp->normal = Vector2(0, direction.y / magnitudeY);
					//Set the penetration
					cp->penetration = yIntersection;
				}
			}

			//Return true for a collision occured
			return true;
		}
		//Return false if a collision didnt occur
		return false;
	}
	//If the shapes are not the same (AABB circle)
	else if (!sameShape) {
		//Assign the collision volume to new variables
		CollisionVolume* circle = (this->type == "Circle") ? this : volume1;
		CollisionVolume* rectangle = (this->type == "Rectangle") ? this : volume1;
		
		//Find the closest point on the rectangle to the circles midpoint
		float closestX = clamp(circle->position.x, rectangle->position.x - (rectangle->getHalfWidth()), rectangle->position.x + (rectangle->getHalfWidth()));
		float closestY = clamp(circle->position.y, rectangle->position.y - (rectangle->getHalfHeight()), rectangle->position.y + (rectangle->getHalfHeight()));
		//Find the distance between the circles position to the closest point
		float distanceX = circle->position.x - closestX;
		float distanceY = circle->position.y - closestY;
		//Get the distance squared
		float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
		//If the distance (squared) is less than the radius (squared) meaning collision
		if (distanceSquared < (circle->getRadius() * circle->getRadius())) {
			//Set the colliders in the collision pair
			//cp->a = this;
			//cp->b = volume1;
			//Set the penetration
			cp->penetration = sqrt(distanceSquared) - circle->getRadius();
			Vector2 direction;
			if (rectangle->position.x - rectangle->getHalfWidth() > circle->position.x - circle->getRadius()) {
				cp->a = circle;
				cp->b = rectangle;

				direction = circle->getPosition() - Vector2(closestX, closestY);
			}
			else {
				cp->a = rectangle;
				cp->b = circle;
				
				direction = Vector2(closestX, closestY) - circle->getPosition();
			}
			
			//Calculate the normal
			float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
			if (!floatComparison(magnitude, 0.0f)) {
				cp->normal = Vector2(direction.x / magnitude, direction.y / magnitude);
			}
			
			//Return true for a collision occured
			return true;
		}
		//Return false if a collision didnt occur
		return false;
	}
	//Return false if a collision didnt occur
	return false;
}
//Function for clamping a value between two given floats
float CollisionVolume::clamp(float value, float minValue, float maxValue) {
	value = std::max(minValue, std::min(maxValue, value));
	return value;
}
