#include "Fruit.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"

#include "FruitWizardGame.h"

#include "CollisionVolume.h"
#include "Circle.h"

using namespace NCL;
using namespace CSC3222;

Fruit::Fruit() : SimObject() {
	texture = texManager->GetTexture("FruitWizard\\Fruit.png");

	int fruitID = rand() % 16;

	animFrameData = Vector4((fruitID / 4) * 16.0f, (fruitID % 4) * 16.0f, 16.0f, 16.0f);
	inverseMass = 0;
}

Fruit::~Fruit() {
}

//Function to add collider (cant be in the constructor as position hasnt been set yet)
void Fruit::AutoAddCollider() {
	//Create collision volume for the spell
	CollisionVolume* cv3 = new Circle(5, GetPosition(), "Circle", true, ObjectTypes::Fruit, this);
	//Set the spells collider
	SetCollider(cv3);
}

bool Fruit::UpdateObject(float dt) {
	//If this object has been set to delete or the game wants the fruit deleted
	if (deleteThisObject || game->getDeleteFruit()) {
		//Return false (this starts the code to delete objects in fruit wizard game)
		return false;
	}
	return true;
}