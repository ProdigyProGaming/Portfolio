#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include <algorithm>
#include "../../Common/Vector2.h"
#include "FruitWizardGame.h"

#include "PlayerCharacter.h"
#include "Spell.h"

using namespace NCL;
using namespace CSC3222;

GameSimsPhysics::GameSimsPhysics()	{

}

GameSimsPhysics::~GameSimsPhysics()	{

}

void GameSimsPhysics::Update(float dt) {
	//Fixed update
	timeRemaining += dt;
	const float subTimeDelta = 1.0 / 120;

	while (timeRemaining > subTimeDelta) {
		Integration(subTimeDelta);
		CollisionDetection(subTimeDelta);
		CollisionResolution(subTimeDelta);
		IntegrateVelocity(subTimeDelta);
		timeRemaining -= subTimeDelta;
	}
	//Reset forces on all bodies
	for (auto body : allBodies) {
		body->force = Vector2(0, 0);
	}
}

void GameSimsPhysics::AddRigidBody(RigidBody* b) {
	allBodies.emplace_back(b);
}

void GameSimsPhysics::RemoveRigidBody(RigidBody* b) {
	auto at = std::find(allBodies.begin(), allBodies.end(), b);

	if (at != allBodies.end()) {
		//maybe delete too?
		allBodies.erase(at);
	}
}

void GameSimsPhysics::AddCollider(CollisionVolume* c) {
	allColliders.emplace_back(c);
}

void GameSimsPhysics::RemoveCollider(CollisionVolume* c) {
	auto at = std::find(allColliders.begin(), allColliders.end(), c);

	if (at != allColliders.end()) {
		//maybe delete too?
		allColliders.erase(at);
	}
}

void GameSimsPhysics::Integration(float dt) {
	//For all bodies
	for (auto body : allBodies) {
		//Calculate acceleration using force and inverse mass
		Vector2 acceleration = body->force * body->inverseMass;
		//Apply acceleration to velocity
		body->velocity += acceleration * dt;
		//Apply dampening to velocity
		body->velocity *= body->dampeningFactor;		
	}
}



bool testFunction(CollisionVolume* a, CollisionVolume* b, CollisionVolume** c, CollisionVolume** d, ObjectTypes e) {
	if (a->getObjectType() == e || b->getObjectType() == e) {
		*c = (a->getObjectType() == e) ? a : b;
		*d = (a->getObjectType() == e) ? b : a;
		return true;
	}
	return false;
}



void GameSimsPhysics::CollisionResolution(float dt) {
	//For each of the collision pairs
	for (CollisionPair col : collisions) {
		//Get the total mass for the collided objects
		float totalMass = col.a->getBody()->inverseMass + col.b->getBody()->inverseMass;

		//Set activated to false (used for ignoring normal solid collisions)
		bool activated = false;
		
		//Create two objects to give an order to the colliders (means checking against only object 1 instead of both col.a and col.b)
		CollisionVolume* object1 = nullptr;
		CollisionVolume* object2 = nullptr;

		/*

		//If either of the objects are the player 
		if (col.a->getObjectType() == ObjectTypes::Player || col.b->getObjectType() == ObjectTypes::Player) {
			//Set the player to object 1 and the other object to 2
			object1 = (col.a->getObjectType() == ObjectTypes::Player) ? col.a : col.b;
			object2 = (col.a->getObjectType() == ObjectTypes::Player) ? col.b : col.a;
		}
		//If either of the objects are a spell 
		else if (col.a->getObjectType() == ObjectTypes::Spell || col.b->getObjectType() == ObjectTypes::Spell) {
			//Set the spell to object 1 and the other object to 2
			object1 = (col.a->getObjectType() == ObjectTypes::Spell) ? col.a : col.b;
			object2 = (col.a->getObjectType() == ObjectTypes::Spell) ? col.b : col.a;
		}
		//If either of the objects are a guard 
		else if (col.a->getObjectType() == ObjectTypes::Guard || col.b->getObjectType() == ObjectTypes::Guard) {
			//Set the guard to object 1 and the other object to 2
			object1 = (col.a->getObjectType() == ObjectTypes::Guard) ? col.a : col.b;
			object2 = (col.a->getObjectType() == ObjectTypes::Guard) ? col.b : col.a;
		}
		//If either of the objects are the king
		else if (col.a->getObjectType() == ObjectTypes::King || col.b->getObjectType() == ObjectTypes::King) {
			//Set the king to object 1 and the other object to 2
			object1 = (col.a->getObjectType() == ObjectTypes::King) ? col.a : col.b;
			object2 = (col.a->getObjectType() == ObjectTypes::King) ? col.b : col.a;
		}
		//If either of the objects are a pixie 
		else if (col.a->getObjectType() == ObjectTypes::Pixie || col.b->getObjectType() == ObjectTypes::Pixie) {
			//Set the pixie to object 1 and the other object to 2
			object1 = (col.a->getObjectType() == ObjectTypes::Pixie) ? col.a : col.b;
			object2 = (col.a->getObjectType() == ObjectTypes::Pixie) ? col.b : col.a;
		}
		else {
			object1 = col.a;
			object2 = col.b;
		}

		*/

		bool done = false;
		done = (!done) ? testFunction(col.a, col.b, &object1, &object2, ObjectTypes::Player) : true;
		done = (!done) ? testFunction(col.a, col.b, &object1, &object2, ObjectTypes::Spell) : true;
		done = (!done) ? testFunction(col.a, col.b, &object1, &object2, ObjectTypes::Guard) : true;
		done = (!done) ? testFunction(col.a, col.b, &object1, &object2, ObjectTypes::King) : true;
		done = (!done) ? testFunction(col.a, col.b, &object1, &object2, ObjectTypes::Pixie) : true;
		if (!done) {
			object1 = col.a;
			object2 = col.b;
		}

		//Switch the first objects type
		switch (object1->getObjectType()) {
		//If the object is the player
		case ObjectTypes::Player:
			//Switch the other object
			switch (object2->getObjectType()) {
			case ObjectTypes::Spell:
				//If the second object is a spell, dont collide with the player
				activated = true;
				break;
			case ObjectTypes::Ladder:
				//If the second object is a ladder, allow the player to climb
				object1->getBody()->setClimbable(true);
				//Prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Fruit:
				//If the second object is a fruit, set a number of points to add and a trigger for decrementing the fruit count
				pointsToAdd = 1000;
				decrementFruitCount = true;
				//Set the fruit to be deleted
				object2->getBody()->setToDeleteObject();
				//Prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Dust:
				//If the second object is a dust, set a trigger to increment the dust count and points to add
				incrementDustCount = true;
				pointsToAdd = 500;
				//Set the dust to be deleted from the froggo dust list
				dustToDelete = object2->getBody();
				//Set the dust to be deleted
				object2->getBody()->setToDeleteObject();
				//Prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Pixie:
				//If the second object is a pixie, set the points to be added and the trigger for incrementing the magic count
				pointsToAdd = 1000;
				incrementMagicCount = true;
				//Set the pixie to be deleted
				object2->getBody()->setToDeleteObject();
				//Prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Guard:
				//If the second object is a guard and he isnt stunned
				if (!object2->getBody()->GetStunned()) {
					//Set the trigger for dying
					loseLife = true;
				}
				//Prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::King:
				//If the second object is the king and he isnt stunned
				if (!object2->getBody()->GetStunned()) {
					//Set the trigger for dying
					loseLife = true;
				}
				//Prevent normal solid collision
				activated = true;
				break;
			}
			break;
		//If the object is a spell
		case ObjectTypes::Spell:
			//Switch the other object
			switch (object2->getObjectType()) {
			case ObjectTypes::Guard:
				//If the other object is a guard, delete the spell and set the guard to be stunned
				object1->getBody()->setToDeleteObject();
				object2->getBody()->SetStunned(object1->getPosition().x < object2->getPosition().x ? 1 : -1);
				//Set points to be added
				pointsToAdd = 200;
				//Prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::King:
				//If the other object is the king, delete the spell and set the king to be stunned
				object1->getBody()->setToDeleteObject();
				object2->getBody()->SetStunned(object1->getPosition().x < object2->getPosition().x ? 1 : -1);
				//Set points to be added
				pointsToAdd = 200;
				//Prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Ladder:
			case ObjectTypes::Pixie:
			case ObjectTypes::Fruit:
			case ObjectTypes::Dust:
				//If the other object is a ladder, pixie or fruit, prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Wall:
			case ObjectTypes::Floor:
				//If the other object is a floor or wall and the wall that has been collided is not the same as the last collided wall
				if (!(object2->getPosition() == object1->getBody()->GetLastWallCollided())) {
					//Set the last collided wall to the current wall
					object1->getBody()->SetLastWallCollided(object2->getPosition());
					//Increment the bounces
					object1->getBody()->incrementBounces();
				}
			}
			break;
		//If the object is a guard
		case ObjectTypes::Guard:
			//Switch the other object
			switch (object2->getObjectType()) {
			case ObjectTypes::Fruit:
			case ObjectTypes::Ladder:
			case ObjectTypes::King:
			case ObjectTypes::Guard:
			case ObjectTypes::Dust:
			case ObjectTypes::Pixie:
				//If the second object is one of the above, prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Wall:
				//If the second object is a wall set the going right variable to whether the guard should move right or not
				if (object1->getPosition().x <= object2->getPosition().x) {
					object1->getBody()->setGoingRight(false);
				}
				else {
					object1->getBody()->setGoingRight(true);
				}
				break;
			}
			break;
		//If the object is the king
		case ObjectTypes::King:
			//Switch the other object
			switch (object2->getObjectType()) {
			case ObjectTypes::Fruit:
			case ObjectTypes::Dust:
			case ObjectTypes::Pixie:
				//If the second object is one of the above, prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Ladder:
				//If the second object is a ladder, set the climbable variable to true
				object1->getBody()->setClimbable(true);
				//Prevent normal solid collision
				activated = true;
				break;
			case ObjectTypes::Wall:
				//If the second object is a wall set the going right variable to whether the king should move right or not (shouldnt usually happen)
				if (object1->getPosition().x <= object2->getPosition().x) {
					object1->getBody()->setGoingRight(false);
				}
				else {
					object1->getBody()->setGoingRight(true);
				}
				break;
			}
			break;
		//If the object is a pixie
		case ObjectTypes::Pixie:
			//Switch the other object
			switch (object2->getObjectType()) {
				case ObjectTypes::Wall:
				case ObjectTypes::Floor:
				case ObjectTypes::Ladder:
				case ObjectTypes::Fruit:
				case ObjectTypes::Dust:
					//If the second object is one of the above, prevent normal solid collision
					activated = true;
					break;
				}
			break;
		}

		//If the normal solid collisions should happen (not been set otherwise)
		if (!activated) {
			//Calculate the impulse
			Vector2 aImpulse = col.normal * col.penetration * (col.a->getBody()->inverseMass / totalMass);
			Vector2 bImpulse = col.normal * col.penetration * (col.b->getBody()->inverseMass / totalMass);
			//Apply a negative impulse to a and a normal impulse to b
			col.a->getBody()->AddImpulse(-aImpulse);
			col.b->getBody()->AddImpulse(bImpulse);
		}
	}
	//Clear the collisions list
	collisions.clear();
}

void GameSimsPhysics::IntegrateVelocity(float dt) {
	//For all of the bodies
	for (auto body : allBodies) {
		//Modify the position using velocity
		body->position = body->position + body->velocity * dt;
	}
}

//Narrow phase to be done upon detecting collision with main colliders
void GameSimsPhysics::NarrowPhase(CollisionVolume* volume1, CollisionVolume* volume2) {
	//Create collision pair
	CollisionPair* cp = new CollisionPair{};
	
	//Create temp variables for reducing number of lines
	CollisionVolume* volWithSubColliders;
	CollisionVolume* otherColliders;
	//If the first volume has child colliders
	if (volume1->getChildrenVolumes()->size() > 0) {
		//Set the volWithSubColliders to the first volume
		volWithSubColliders = volume1;
		//Set the other variable to the second volume
		otherColliders = volume2;
	}
	//If the first volume does not have child colliders (the second volume must have sub colliders)
	else {
		//Set the volWithSubColliders to the second volume
		volWithSubColliders = volume2;
		//Set the other variable to the first volume
		otherColliders = volume1;
	}
	//Loop through the first volume that had sub colliders
	for (int i = 0; i < volWithSubColliders->getChildrenVolumes()->size(); i++) {
		//If the other volume had sub colliders
		if (otherColliders->getChildrenVolumes()->size() > 0) {
			//Loop through the other volumes colliders
			for (int j = 0; j < otherColliders->getChildrenVolumes()->size(); j++) {
				//If a collision occurs between any of the sub volumes
				if (volWithSubColliders->getChildrenVolumes()->at(i)->CheckCollision(otherColliders->getChildrenVolumes()->at(j), cp)) {
					//Add the collision pair to the collisions list
					collisions.emplace_back(*cp);
					//std::cout << "Sub Collision;";
				}
			}
		}
		//If the other volume does not have sub colliders
		else {
			//Check each sub collider with the main collider
			if (volWithSubColliders->getChildrenVolumes()->at(i)->CheckCollision(otherColliders, cp)) {
				//Add the collision pair to the collisions list
				collisions.emplace_back(*cp);
				//std::cout << "Sub Collision;";
			}
		}
	}
}

void GameSimsPhysics::CollisionDetection(float dt) {
	//Sort the colliders
	InsertionSort();

	//Create collision pair
	CollisionPair* cp = new CollisionPair{};

	//For all of the colliders
	for (int i = 0; i < allColliders.size(); i++) {
		//Get the max extent of this collider
		float max = allColliders.at(i)->getPosition().x + ((allColliders.at(i)->getType() == "Circle") ? allColliders.at(i)->getRadius() : allColliders.at(i)->getHalfWidth());
		//For each of the remaining colliders
		for (int j = i + 1; j < allColliders.size(); j++) {
			//Get the min extent of this collider
			float min = allColliders.at(j)->getPosition().x - ((allColliders.at(j)->getType() == "Circle") ? allColliders.at(j)->getRadius() : allColliders.at(j)->getHalfWidth());
			//If the min of the second is greater than the max of the first (the next shape is beyond what could collide and therefore all following shapes)
			if (min > max) {
				//Break out of the for as no remaining shapes could collide
				break;
			}
			//If both colliders are static, try the next shape as static objects shouldnt be checked
			if (allColliders.at(i)->getIsStatic() && allColliders.at(j)->getIsStatic()) {
				continue;
			}
			//Check if a collision occurs between the main colliders
			if (allColliders[i]->CheckCollision(allColliders[j], cp)) {
				//If both have no sub colliders 
				if (allColliders.at(i)->getChildrenVolumes()->size() == 0 && allColliders.at(j)->getChildrenVolumes()->size() == 0) {
					//Add to collisions list
					collisions.emplace_back(*cp);
					//std::cout << "Collision;";
				}
				//If at least one has sub colliders
				else {
					//Do narrow phase checking on the volumes
					NarrowPhase(allColliders[i], allColliders[j]);
				}
			}
		}
	}
}
//Insertion sort
void GameSimsPhysics::InsertionSort() {
	int j;
	//For all of the colliders
	for (int i = 1; i < allColliders.size(); i++) {
		//Set the key to the current collision volume
		auto key = allColliders.at(i);
		//Get the min extent of the key
		float keyValue = key->getPosition().x - ((key->getType() == "Circle") ? key->getRadius() : key->getHalfWidth());
		j = i;
		//While j is greater than 0 and the new colliders min extent is greater than the keys min extent (need to keep searching for the correct place)
		while (j > 0 && (allColliders.at(j - 1)->getPosition().x - ((allColliders.at(j-1)->getType() == "Circle") ? allColliders.at(j-1)->getRadius() : allColliders.at(j-1)->getHalfWidth()) > keyValue)) {
			//Move the colliders at j and j - 1
			allColliders.at(j) = allColliders.at(j - 1);
			//Decrement j
			j--;
		}
		//Set the position to key
		allColliders.at(j) = key;
	}
}