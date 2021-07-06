#include "PlayerCharacter.h"
#include "TextureManager.h"
#include "../../Common/Window.h"
#include "GameSimsRenderer.h"
#include "Spell.h"
#include "FruitWizardGame.h"
#include "GameSimsPhysics.h"
#include "GameMap.h"
#include "Rectangle.h"

#include "Circle.h"

using namespace NCL;
using namespace CSC3222;

Vector4 runFrames[] = {
	Vector4(64,160, 32, 32),
	Vector4(96,160, 32, 32),
	Vector4(128,160, 32, 32),
	Vector4(160,160, 32, 32),
	Vector4(192,160, 32, 32),
	Vector4(224,160, 32, 32),
};

Vector4 attackFrames[] = {
	Vector4(128,288, 32, 30),
	Vector4(64,224, 32, 32),
	Vector4(160,288, 32, 30),
	Vector4(96,224, 32, 32),
	Vector4(192,288, 32, 29),
	Vector4(64,256, 32, 32)
};

Vector4 idleFrames[] = {
	Vector4(64,128, 32, 32),
	Vector4(96,128, 32, 32),
	Vector4(128,128, 32, 32),
	Vector4(160,128, 32, 32),
	Vector4(128,128, 32, 32),
	Vector4(224,128, 32, 32)
};

Vector4 fallFrames[] = {
	Vector4(64,320, 32, 32),
	Vector4(64,320, 32, 32),
	Vector4(64,320, 32, 32),
	Vector4(96,320, 32, 32),
	Vector4(96,320, 32, 32),
	Vector4(96,320, 32, 32)
};

Vector4 deathFrames[] = {
	Vector4(96,352, 32, 32),
	Vector4(128,352, 32, 32),
	Vector4(96,352, 32, 32),	
	Vector4(128,352, 32, 32),
	Vector4(96,352, 32, 32),
	Vector4(128,352, 32, 32),
};

Vector4 ladderFrames[] = {//Not an ideal spritesheet for ladders!
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
	Vector4(64,224, 32, 32),
};


PlayerCharacter::PlayerCharacter() : SimObject() {
	currentAnimState	= PlayerState::Left;
	texture				= texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
	animFrameCount		= 6;
	//Set the damping factor
	dampeningFactor = 0.8;
	
}
//Function to add collider (cant be in the constructor as position hasnt been set yet)
void PlayerCharacter::AutoAddCollider() {
	//Create collider at position of specific size
	CollisionVolume* cv1 = new Rectangle(8, 16, GetPosition(), "Rectangle", false, ObjectTypes::Player, this);
	//Add a sub collider
	//cv1->addChildVolume(new Circle(8, GetPosition(), "Circle", false, ObjectTypes::Player, this));
	//Set the collider
	SetCollider(cv1);
}

PlayerCharacter::~PlayerCharacter() {

}

bool PlayerCharacter::UpdateObject(float dt) {
	if (deleteThisObject) {
		return false;
	}
	float testSpeed = 64;
	Vector4* animSource = idleFrames;

	Vector2 newVelocity;

	if (currentAnimState == PlayerState::Attack) {
		animSource = attackFrames;
		if (currentanimFrame >= 5) {
			currentAnimState = PlayerState::Idle;
		}
	}
	else {
		currentAnimState = PlayerState::Idle;
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LEFT)) {
			animSource = runFrames;
			currentAnimState = PlayerState::Left;
			//Add a force of -200 on the x axis (replaces velocity manipulation)
			AddForce(Vector2(-200, 0));
			flipAnimFrame = true;
		}
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
			animSource = runFrames;
			currentAnimState = PlayerState::Right;
			//Add a force of 200 on the x axis (replaces velocity manipulation)
			AddForce(Vector2(200, 0));
			flipAnimFrame = false;
		}	
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::UP)) {
			if (getClimbable()) {
				animSource = ladderFrames;
				AddForce(Vector2(0, 150));
			}
		}
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::DOWN)) {
			if (getClimbable()) {
				animSource = fallFrames;
				AddForce(Vector2(0, -100));
			}
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE)) {
			if (game->GetMagicCount() > 0) {
				currentAnimState = PlayerState::Attack;
				srand((int)(game->getGameTime() * 1000.0f));
				float randY = ((float(rand()) / float(RAND_MAX)) * (0.3 - -0.3)) + -0.3;
				//Create a spell and give a direction to move the spell
				Spell* testSpell = new Spell(Vector2((flipAnimFrame) ? -1 : 1, randY));
				//Set the spells position
				testSpell->SetPosition(Vector2(position.x, position.y));
				//Call the add collider function to add collider
				testSpell->AutoAddCollider();
				//Add the spell to the game
				game->AddNewObject(testSpell);
				//Increment the magic count (not how the final game will work, but used as proof of concept of score manipulation)
				game->DecrementMagicCount();
				currentanimFrame = 0;
			}
		}
		//If on a ladder, slower gravity, otherwise -150 for gravity
		if (getClimbable()) {
			AddForce(Vector2(0, -75));
		}
		else {
			AddForce(Vector2(0, -150));
		}

		//If the tiles below is empty (should fall down)
		if (game->getCurrentMap()->IsTilePosEmpty(game->getCurrentMap()->WorldPosToTilePos(Vector2(position.x, position.y - 16))) &&
			game->getCurrentMap()->IsTilePosEmpty(game->getCurrentMap()->WorldPosToTilePos(Vector2(position.x + 8, position.y - 16))) && 
			game->getCurrentMap()->IsTilePosEmpty(game->getCurrentMap()->WorldPosToTilePos(Vector2(position.x - 8, position.y - 16)))) {
			animSource = fallFrames;
		}
	}
	
	animFrameData = animSource[currentanimFrame];
	//Update the colliders position
	GetCollider()->setPosition(this->GetPosition());
	clibmable = false;
	return true;
}