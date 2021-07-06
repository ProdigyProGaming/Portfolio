#include "Guard.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "FruitWizardGame.h"

#include "CollisionVolume.h"
#include "Rectangle.h"
#include "GameMap.h"

using namespace NCL;
using namespace CSC3222;

Vector4 guardIdleFrames[] = {
	Vector4(384,32, 64, 32),
	Vector4(448,32, 64, 32),	
	Vector4(512,32, 64, 32),	
	Vector4(576,32, 64, 32),	
	Vector4(448,64, 64, 32),	
	Vector4(512,64, 64, 32),
};

Vector4 guardWalkFrames[] = {
	Vector4(384,96, 64, 32),
	Vector4(448,96, 64, 32),
	Vector4(512,96, 64, 32),
	Vector4(576,96, 64, 32),
	Vector4(640,96, 64, 32),
	Vector4(704,96, 64, 32),
};

Vector4 guardAttackFrames[] = {
	Vector4(384,128, 64, 32),
	Vector4(448,128, 64, 32),
	Vector4(512,128, 64, 32),
	Vector4(576,128, 64, 32),
	Vector4(640,128, 64, 32),
	Vector4(704,128, 64, 32),
};

Vector4 guardStunFrames[] = {
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
	Vector4(448,160, 64, 32),
};

Guard::Guard() : SimObject() {
	texture = texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
	animFrameCount	= 6;
	//Set the default state to patrolling the area
	state = GuardState::Patrol;
	//Set the stun timer to 0
	stunTimer = 0;
	//Set the bool for moving right to true
	goingRight = true;
	//Set the dampening Factor to 0.8
	dampeningFactor = 0.8;
	//Set the stun trigger to false
	setStunned = false;
	//Set the stun direction to 0
	stunDir = 0;
}

Guard::~Guard() {
}

//Function to add collider (cant be in the constructor as position hasnt been set yet)
void Guard::AutoAddCollider() {
	//Create collider at position of specific size
	CollisionVolume* cv2 = new Rectangle(10, 15, GetPosition(), "Rectangle", false, ObjectTypes::Guard, this);
	//Set the collider
	SetCollider(cv2);
}

//Function to set the starting position to the current position
void Guard::setStartingPos() {
	startingPos = position;
}

//Function to set the player
void Guard::setPlayer(SimObject* newPlayer) {
	player = newPlayer;
}

//Function to handle the stun state (takes in dt for stun timer)
void Guard::Stun(float dt) {
	//If the stun timer is 0
	if (stunTimer == 0) {
		//Add an impulse in the correct direction
		AddImpulse(Vector2(100 * stunDir, 0));
		//Reset the stun direction
		stunDir = 0;
	}

	//If the timer is greater than 5
	if (stunTimer >= 5.0f) {
		//If current y is less than original positions y (fallen down a level)
		//-10 to prevent activation on fluctuations of y when colliding with ground
		if (position.y < startingPos.y - 10) {
			setStartingPos();
		}
		//Set the state to patrol
		state = GuardState::Patrol;
		//Reset the stun timer
		stunTimer = 0;
		//Reset the stunned trigger
		setStunned = false;
	}
	//If the timer is less than 5
	else {
		//Increment the stun timer
		stunTimer += dt;
	}
}

//Function to handle the chase state
void Guard::Chase() {
	//Get the x and y distance to the player (absolute value to get distance regardless of sign)
	float xDistanceToPlayer = abs(position.x - player->GetPosition().x);
	float yDistanceToPlayer = abs(position.y - player->GetPosition().y);
	//Get the distance to the starting position
	float distanceToStartingPos = sqrt(pow(position.x - startingPos.x, 2) + pow(position.y - startingPos.y, 2));

	//If the x distance to the player is greater than 6 tiles or the distance to the starting pos is greater than 10 tiles
	//or the y distance to the player is is greater than 8
	if (xDistanceToPlayer > 96 || distanceToStartingPos >= 160 || yDistanceToPlayer > 8) {
		//Change the state to patrol
		state = GuardState::Patrol;
	}
	//If the distance to the player is lass than 3 tiles and the y distance is small enough
	else if (xDistanceToPlayer < 48 && yDistanceToPlayer < 8) {
		//Change the state to attack
		state = GuardState::Attack;
	}
	else {
		//If the player is to the left
		if (player->GetPosition().x < position.x) {
			//Set the flip anim frame to false to make the guard face left
			flipAnimFrame = false;
			//If the tile down and to the left can be walked on (prevents walking off edge)
			if (!game->getCurrentMap()->IsTilePosEmpty(game->getCurrentMap()->WorldPosToTilePos(Vector2(position.x - 8, position.y - 17)))) {
				//Add a negative force
				AddForce(Vector2(-100, 0));
			}
		}
		else {
			//Set the flip anim frame to true to make the guard face right
			flipAnimFrame = true;
			//If the tile down and to the right can be walked on (prevents walking off edge)
			if (!game->getCurrentMap()->IsTilePosEmpty(game->getCurrentMap()->WorldPosToTilePos(Vector2(position.x + 8, position.y - 17)))) {
				//Add a positive force
				AddForce(Vector2(100, 0));
			}
		}
	}
}

//Function to handle the patrol state
void Guard::Patrol() {
	//Get the x and y distance to the player (absolute value to get distance regardless of sign)
	float xDistanceToPlayer = abs(position.x - player->GetPosition().x);	
	float yDistanceToPlayer = abs(position.y - player->GetPosition().y);
	//Get the distance to the starting position
	float distanceToStartingPos = sqrt(pow(position.x - startingPos.x, 2) + pow(position.y - startingPos.y, 2));

	//If the distance to the player is less than 2 tiles and the y distance is small enough
	if (xDistanceToPlayer <= 48 && yDistanceToPlayer < 8) {
		//Change the state to chase
		state = GuardState::Chase;
	}
	//If the distance to the starting position is greater than 10 tiles
	else if (distanceToStartingPos >= 160) {
		//If the velocity is less than 0 and the position is to the left of the starting point
		if (velocity.x <= 0 && position.x < startingPos.x) {
			//Set the bool for going right to true
			goingRight = true;
		}
		//If the velocity is greater than 0 and the position is to the right of the starting point
		else if (velocity.x > 0 && position.x > startingPos.x) {
			//Set the bool for going right to false
			goingRight = false;
		}
	}
	//If the tile to the right and below is empty (to prevent walking off an edge)
	else if (game->getCurrentMap()->IsTilePosEmpty(game->getCurrentMap()->WorldPosToTilePos(Vector2(position.x + 9, position.y - 17)))) {
		//Set the bool for going right to false
		goingRight = false;
	}
	//If the tile to the left and below is empty (to prevent walking off an edge)
	else if (game->getCurrentMap()->IsTilePosEmpty(game->getCurrentMap()->WorldPosToTilePos(Vector2(position.x - 9, position.y - 17)))) {
		//Set the bool for going right to true
		goingRight = true;
	}
	
	//If the bool is set to go right
	if (goingRight) {
		//Set the flip anim frame to true to make the guard face right
		flipAnimFrame = true;
		//Add a force to move to the right
		AddForce(Vector2(100, 0));
	}
	else {
		//Set the flip anim frame to false to make the guard face left
		flipAnimFrame = false;
		//Add a force to move to the left
		AddForce(Vector2(-100, 0));
	}
}


void Guard::Attack() {
	//Get the x and y distance to the player (absolute value to get distance regardless of sign)
	float xDistanceToPlayer = abs(position.x - player->GetPosition().x);
	float yDistanceToPlayer = abs(position.y - player->GetPosition().y);

	//If the player is to the left of the current position
	if (player->GetPosition().x < position.x) {
		//Set the flip anim frame to false to make the guard face left
		flipAnimFrame = false;
		//Set the amount to move the collider by to -16 if the frame is the later frames to move the collider to the left and hit the player
		colliderMover = (currentanimFrame == 4 || currentanimFrame == 5) ? -16 : 0;
	}
	else {
		//Set the flip anim frame to true to make the guard face right
		flipAnimFrame = true;
		//Set the amount to move the collider by to 16 if the frame is the later frames to move the collider to the left and hit the player
		colliderMover = (currentanimFrame == 4 || currentanimFrame == 5) ? 16 : 0;
	}
	//If the distance to the player is greater than 4 tiles or the y distance is greater than 1 tiles
	if (xDistanceToPlayer > 64 || yDistanceToPlayer > 16) {
		//Change the state to chase
		state = GuardState::Chase;
	}
}



bool Guard::UpdateObject(float dt) {
	Vector4* animSource = guardIdleFrames;

	//If the setStunned trigger has been set by the physics class
	//Set the state to stunned
	if (setStunned) state = GuardState::Stun;
	//Switch the state variable
	switch (state)
	{
	//If the state is stun
	case GuardState::Stun:
		//Change the sprites to the stun or idle frames
		if (stunTimer >= 1) {
			animSource = guardIdleFrames;
		}
		else {
			animSource = guardStunFrames;
		}
		//Call the stun function
		Stun(dt);
		break;
	//If the state is chase
	case GuardState::Chase:
		//Change the sprites
		animSource = guardWalkFrames;
		//Call the chase function
		Chase();
		break;
	//If the state is patrol
	case GuardState::Patrol:
		//Change the sprites
		animSource = guardWalkFrames;
		//Call the patrol function
		Patrol();
		break;
	//If the state is attack
	case GuardState::Attack:
		//Change the sprites
		animSource = guardAttackFrames;
		//Call the attack function
		Attack();
		break;
	}

	//Set the frame data to the correct source
	animFrameData = animSource[currentanimFrame];
	//Move the collider to the position plus any movement (necessary for attacks)
	GetCollider()->setPosition(Vector2(GetPosition().x + colliderMover, GetPosition().y));
	//Reset the amount to move the collider to 0
	colliderMover = 0;

	//If the tile below is empty (should fall down)
	if (game->getCurrentMap()->IsTilePosEmpty(game->getCurrentMap()->WorldPosToTilePos(Vector2(position.x, position.y - 16)))) {
		//Move the guard downwards
		AddForce(Vector2(0, -100));
	}

	return true;
}