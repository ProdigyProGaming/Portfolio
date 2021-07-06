#include "Pixie.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"

#include "FruitWizardGame.h"

#include "Rectangle.h"

#include <algorithm>

using namespace NCL;
using namespace CSC3222;

//Static list of boids (pixies and enemies)
std::vector<SimObject*> Pixie::allBoids;
//Static count of pixies
int Pixie::pixieCount;

Vector4 pixieFrames[] = {
	Vector4(32 * 1,32 * 4, 32, 32),
	Vector4(32 * 2,32 * 4, 32, 32),
	Vector4(32 * 3,32 * 4, 32, 32),
	Vector4(32 * 4,32 * 4, 32, 32),
};

Pixie::Pixie() : SimObject() {
	texture			= texManager->GetTexture("FruitWizard\\super_random_sprites.png");
	animFrameCount	= 4;
	allBoids.emplace_back(this);
}

Pixie::~Pixie() {
}

//Function to add collider (cant be in the constructor as position hasnt been set yet)
void Pixie::AutoAddCollider() {
	//Create collider at position of specific size
	CollisionVolume* cv2 = new Rectangle(8, 8, position, "Rectangle", false, ObjectTypes::Pixie, this);
	//Set the collider
	SetCollider(cv2);
}

//Function to get the list of boids
std::vector<SimObject*> Pixie::getBoids() {
	//Return the list
	return allBoids;
}

//Function to set the number of pixies
void Pixie::SetPixieCount(int count) {
	//Set the count variable
	pixieCount = count;
}

//Function to get the number of pixies
int Pixie::GetPixieCount() {
	//Return the count
	return pixieCount;
}

//Function to add other objects (enemies) to the boid list
void Pixie::AddOtherObjects(SimObject* newObect) {
	//If the object isnt already in the list
	if (std::find(allBoids.begin(), allBoids.end(), newObect) == allBoids.end()) {
		//Add the boid to the list
		allBoids.emplace_back(newObect);
	}
}

//Function for alignment
Vector2 Pixie::Alignment() {
	//Set the direction vector to the current velocity
	Vector2 dir = this->GetVelocity();

	//For each of the boids
	for (SimObject* p : allBoids) {
		//If the boid is the current object, dont do any calculations
		if (p == this) {
			continue;
		}
		//If the boid is an enemy, dont use for calculations
		if (p->GetCollider()->getObjectType() == ObjectTypes::Guard || p->GetCollider()->getObjectType() == ObjectTypes::King) {
			continue;
		}
		//Get the distance from this to the boid
		float distance = sqrt(pow(this->GetPosition().x - p->GetPosition().x, 2) + pow(this->GetPosition().y - p->GetPosition().y, 2));
		//If the distance is greater than the threshold amount, dont do any more calculations
		if (distance > 16) {
			continue;
		}
		//Set the direction to the other boids velocity
		dir += p->GetVelocity();
	}
	//Normalise the direction
	return dir.Normalised();
}

//Function for seperation
Vector2 Pixie::Seperation() {
	Vector2 dir;
	
	//For each of the boids
	for (SimObject* p : allBoids) {
		//If the boid is the current object, dont do any calculations
		if (p == this) {
			continue;
		}
		//If the boid is an enemy, dont use for calculations
		if (p->GetCollider()->getObjectType() == ObjectTypes::Guard || p->GetCollider()->getObjectType() == ObjectTypes::King) {
			continue;
		}
		//Get the distance from this to the boid
		float distance = sqrt(pow(this->GetPosition().x - p->GetPosition().x, 2) + pow(this->GetPosition().y - p->GetPosition().y, 2));
		//If the distance is greater than 25, dont do any more calculations
		if (distance > 25) {
			continue;
		}
		//Set the strength to 1 - the distance over the seperation threshold
		float strength = 1.0f - (distance / 25);
		//Set the vector to the position - the normalised position multiplied by the strength
		dir += (this->GetPosition()-p->GetPosition()).Normalised() * strength;
	}
	//Normalise the direction
	return dir.Normalised();
}

//Function for cohesion
Vector2 Pixie::Cohesion() {
	//Set the average position to this position
	Vector2 avgPos = this->GetPosition();
	//Set the count to 1
	float count = 1;

	//For each of the boids
	for (SimObject* p : allBoids) {
		//If the boid is the current object, dont do any calculations
		if (p == this) {
			continue;
		}
		//If the boid is an enemy, dont use for calculations
		if (p->GetCollider()->getObjectType() == ObjectTypes::Guard || p->GetCollider()->getObjectType() == ObjectTypes::King) {
			continue;
		}
		//Get the distance from this to the boid
		float distance = sqrt(pow(this->GetPosition().x - p->GetPosition().x, 2) + pow(this->GetPosition().y - p->GetPosition().y, 2));
		//If the distance is greater than 5, dont do any more calculations
		if (distance > 5) {
			continue;
		}
		//Add the position to the average position
		avgPos += p->GetPosition();
		//Increment the count
		count++;
	}
	//Divide the average position by the count
	avgPos /= count;
	//Set the direction to the average position - this position
	Vector2 dir = avgPos - this->GetPosition();
	//Normalise the direction
	return dir.Normalised();
}

//Function for avoidance
Vector2 Pixie::Avoidance() {
	//Strength value to vary depending on type (pixie or enemy)
	int strength = 10;
	Vector2 dir;
	//For each of the boids
	for (SimObject* p : allBoids) {
		//If the boid is the current object, dont do any calculations
		if (p == this) {
			continue;
		}
		//If the boid is an enemy, set strength to higher for more avoidance
		if (p->GetCollider()->getObjectType() == ObjectTypes::Guard || p->GetCollider()->getObjectType() == ObjectTypes::King) {
			strength = 20;
		}
		//If the boid is not an enemy, set the strength back to default (10)
		else {
			strength = 10;
		}
		//Get the distance from this to the boid
		float distance = sqrt(pow(this->GetPosition().x - p->GetPosition().x, 2) + pow(this->GetPosition().y - p->GetPosition().y, 2));
		//If the distance is greater than 30, dont do any more calculations
		if (distance > 30) {
			continue;
		}
		//Add this position - the other normalised position to the direction vector and multiply by the strength
		dir += (this->GetPosition() - p->GetPosition()).Normalised() * strength;
	}
	//Normalise the direction
	return dir;
}

bool Pixie::UpdateObject(float dt) {
	//If this object is to be deleted
	if (deleteThisObject) {
		//Remove this from the list of boids
		allBoids.erase(std::find(allBoids.begin(), allBoids.end(), this));
		//Decrement the count
		pixieCount--;
		return false;
	}

	//Reset velocity
	velocity = Vector2(0, 0);

	//Get all the calculations and add to the direction vector
	Vector2 dir;
	dir += Alignment();
	dir += Seperation();
	dir += Cohesion();
	dir += Avoidance();
	//Add a force in the direction multiplied by 100
	AddForce(dir * 100);

	animFrameData = pixieFrames[currentanimFrame];

	//Calculate spring forces to apply to pixie
	//Get the distance between the pixie and target
	float distance = sqrt(pow(getSpringTarget()->GetPosition().x - GetPosition().x, 2) + pow(getSpringTarget()->GetPosition().y - GetPosition().y, 2));
	//Get the direction to the target
	Vector2 direction = Vector2(GetPosition().x - getSpringTarget()->GetPosition().x, GetPosition().y - getSpringTarget()->GetPosition().y);
	//Get the dot product of direction and velocity
	float v = Vector2::Dot(direction, GetVelocity());
	//Multiply dot product with damping constant
	float cv = 0.9 * v;
	//Multiply sping snappyness with distance and subtract cv
	float force = (-0.003 * distance) - cv;
	//Add the force in the right direction
	AddForce(direction * force);

	
	
	//Flip the sprite depending on where the target is
	flipAnimFrame = getSpringTarget()->GetPosition().x < GetPosition().x;
	GetCollider()->setPosition(this->GetPosition());
	
	

	return true;
}