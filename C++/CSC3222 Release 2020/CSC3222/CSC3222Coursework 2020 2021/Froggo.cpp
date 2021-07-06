#include "Froggo.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "FruitWizardGame.h"
#include "GameMap.h"

#include "Rectangle.h"
#include "Circle.h"

using namespace NCL;
using namespace CSC3222;

Vector4 froggoIdleFrames[] = {
	Vector4(0  ,(96 * 5) + 32, 80, 64),
	Vector4(80 ,(96 * 5) + 32, 80, 64),
	Vector4(160,(96 * 5) + 32, 80, 64),
	Vector4(240,(96 * 5) + 32, 80, 64),
	Vector4(320,(96 * 5) + 32, 80, 64),
	Vector4(400,(96 * 5) + 32, 80, 64),
};

Vector4 froggoWalkFrames[] = {
	Vector4(0  ,(96 * 5) + 32, 80, 64),
	Vector4(80 ,(96 * 5) + 32, 80, 64),
	Vector4(160,(96 * 5) + 32, 80, 64),
	Vector4(240,(96 * 5) + 32, 80, 64),
	Vector4(320,(96 * 5) + 32, 80, 64),
	Vector4(400,(96 * 5) + 32, 80, 64),
};

Vector4 froggoLadderFrames[] = {
	Vector4(0  ,(96 * 4) + 32, 80, 64),
	Vector4(80 ,(96 * 4) + 32, 80, 64),
	Vector4(160,(96 * 4) + 32, 80, 64),
	Vector4(240,(96 * 4) + 32, 80, 64),
	Vector4(320,(96 * 4) + 32, 80, 64),
	Vector4(400,(96 * 4) + 32, 80, 64),
};

Vector4 froggoStunFrames[] = {
	Vector4(0  ,(96 * 8) + 32, 80, 64),
	Vector4(80, (96 * 8) + 32, 80, 64),
	Vector4(160,(96 * 8) + 32, 80, 64),
	Vector4(240,(96 * 8) + 32, 80, 64),
	Vector4(320,(96 * 8) + 32, 80, 64),
	Vector4(400,(96 * 8) + 32, 80, 64),
};

Vector4 froggoAttackFrames[] = {
	Vector4(0  ,(96 * 1) + 32, 80, 64),
	Vector4(80 ,(96 * 1) + 32, 80, 64),
	Vector4(80 ,(96 * 1) + 32, 80, 64),
	Vector4(160,(96 * 1) + 32, 80, 64),
	Vector4(160,(96 * 1) + 32, 80, 64),
	Vector4(240,(96 * 1) + 32, 80, 64),
};

Vector4 froggoJumpFrames[] = {
	Vector4(0  ,(96 * 7) + 32, 80, 64),
	Vector4(80 ,(96 * 7) + 32, 80, 64),
	Vector4(80 ,(96 * 7) + 32, 80, 64),
	Vector4(160,(96 * 7) + 32, 80, 64),
	Vector4(160,(96 * 7) + 32, 80, 64),
	Vector4(240,(96 * 7) + 32, 80, 64),
};

Froggo::Froggo(SimObject* targetPlayer, GameMap* map) : SimObject() {
	texture			 = texManager->GetTexture("FruitWizard\\frogman_crown.png");
	animFrameCount	 = 6;
	//Set the default state to chasing the player
	state = FroggoState::Chase;
	//Set the stun timer to 0
	stunTimer = 0;
	//Set the player to target to the given object
	player = targetPlayer;
	//Create a new vector to store the path to follow
	path = new std::vector<Vector2>;
	//Set the path counter to -2
	pathWaypointCounter = -2;
	//Set the map to the given map
	currentMap = map;
	//Set the triggers to false
	dustSpawned = false;
	setStunned = false;
	//Set the stun direction to 0
	stunDir = 0;
	//Set the amount to move the collider to 0
	colliderMover = 0;
	//Set the delay for path generation to -1
	pathGenDelay = -1;
}

Froggo::~Froggo() {
}

//Function to add collider (cant be in the constructor as position hasnt been set yet)
void Froggo::AutoAddCollider() {
	//Create collider at position of specific size
	CollisionVolume* cv2 = new Rectangle(10, 20, Vector2(GetPosition().x-5, GetPosition().y + 7), "Rectangle", false, ObjectTypes::King, this);
	//Set the collider
	SetCollider(cv2);
}

//Function to get the current path the froggo is following
std::vector<Vector2>* Froggo::GetPath() {
	//Return the path
	return path;
}

//Function to reset the path and the path counter (prevents stacking of routes)
void Froggo::ResetPath() {
	//Clear the path
	path->clear();
	//Reset the counter to -2
	pathWaypointCounter = -2;
}

//Function to set trigger for if a new dust has spawned
void Froggo::SetDustSpawned() {
	//Set the trigger
	dustSpawned = true;
}

//Function to remove a given dust from the dust vector for defending (the player picked up the dust)
void Froggo::RemoveDust(RigidBody* dustToRemove) {
	//find the given dust in the vector
	auto dust = std::find(dusts.begin(), dusts.end(), dustToRemove);
	//If the dust was in the list
	if (dust != dusts.end()) {
		//Remove the dust so the froggo doesnt guard an empty position
		dusts.erase(dust);
	}
}

//Function to add a given dust to a list (new dust has been spawned and needs protecting)
void Froggo::AddToDusts(RigidBody* newDust) {
	//Add the given dust to the list
	dusts.emplace_back(newDust);
}

//Function to generate a path given a target and dt for the delay in generating a path
void Froggo::GeneratePath(Vector2 target, float dt) {
	//If it has been delayed for more than 1 second or the delay hasnt been activated
	if (pathGenDelay >= 1 || pathGenDelay == -1) {
		//Generate the path and store the bool result in the success variable
		bool success = currentMap->GeneratePath(pathPoint, target, GetPath());
		//If a path was created
		if (success) {
			//Set the delay to be deactivated
			pathGenDelay = -1;
			//Set the counter to the end of the path (the path works backwards)
			pathWaypointCounter = path->size() - 1;
		}
		//If a path was not created
		else {
			//Start the delay by setting to 0 (-1 is deactivated)
			pathGenDelay = 0;
		}
	}
	//If the delay has been activated and has not been delayed for 1 second yet
	else {
		//Increase the delay by dt
		pathGenDelay += dt;
	}
}

//Function to handle the stun state (takes in dt for stun timer)
void Froggo::Stun(float dt) {
	//If the setStunned trigger is true, this means this is the first loop in the stun state
	if (setStunned) {
		//Add an impulse to push the enemy back in a given direction
		AddImpulse(Vector2(100 * stunDir, 0));
		//Set the stunned trigger to false to prevent a constant impulse
		setStunned = false;
		//Reset the stun direction to 0 for the next time
		stunDir = 0;
	}
	//If the stunned trigger has been deactivated
	if (!setStunned) {
		//Set the current frame to the last one to keep the froggo on the floor
		currentanimFrame = 5;
	}
	//If the time spent stunned is longer than 3 seconds
	if (stunTimer >= 3.0f) {
		//Change the state to defending the dusts
		state = FroggoState::Defend;
		//Reset the stun timer for next time
		stunTimer = 0;
	}
	//If the time spent stunned is less than 3 seconds
	else {
		//Increase the stun timer by dt
		stunTimer += dt;
	}
}

//Function to handle the chase state (takes in dt for generate path delay)
Vector4* Froggo::Chase(float dt) {
	//Create a variable to store which frames to use and set the default to walk frames
	Vector4* framesToUse = froggoWalkFrames;

	//Get the x and y distance to the player (absolute value to get distance regardless of sign)
	float xDistanceToPlayer = abs(position.x - player->GetPosition().x);
	float yDistanceToPlayer = abs(position.y - player->GetPosition().y);

	//If the x distance to the player is less than 2 tiles and the y distance is close (to prevent trying to attack when on a different level)
	if (xDistanceToPlayer <= 32 && yDistanceToPlayer < 8) {
		//Change the state to attack
		state = FroggoState::Attack;
	}
	//If a dust has been spawned
	else if (dustSpawned) {
		//Change the state to defend the dust
		state = FroggoState::Defend;
	}
	//If the path counter is reset and a dust has not yet been spawned
	else if (pathWaypointCounter == -2 && !dustSpawned) {
		//Call the generate path function and pass the players position (-5 for the bottom of the player) and dt for the delay
		GeneratePath(Vector2(player->GetPosition().x, player->GetPosition().y - 5), dt);
	}
	//If the path counter is -1 (path is finished as 0 is the last item and will -1 to get the next point)
	else if (pathWaypointCounter == -1) {
		//Reset the path
		ResetPath();
		//Call the generate path function and pass the players position (-5 for the bottom of the player) and dt for the delay
		GeneratePath(Vector2(player->GetPosition().x, player->GetPosition().y - 5), dt);
	}
	//If the path counter is not finished 
	else if (pathWaypointCounter > -1) {
		//Get the direction between the froggos path point to the current paths point to go to
		Vector2 direction = path->at(pathWaypointCounter) - pathPoint;

		//If the direction on the x is less than 0 (going to the left)
		if (direction.x < 0) {
			//Set the flip anim frame to false to make froggo face left
			flipAnimFrame = false;
		}
		//If the direction on the x is greater than or equal 0 (going to the right)
		else {
			//Set the flip anim frame to true to make froggo face right
			flipAnimFrame = true;
		}

		//If the absoluate direction of the y (ignore whether its up or down) is greater than 2 (intentionally moving up or down)
		if (abs(direction.y) > 2) {
			//Set the frame to use to be the ladder frames
			framesToUse = froggoLadderFrames;
			//Set the collider width to 6 to fit through on the ladders
			GetCollider()->setHalfWidth(6);
		}
		//If the froggo is not supposed to be moving on the y
		else {
			//Set the frame to use to be the walk frames
			framesToUse = froggoWalkFrames;
			//Set the collider width to the normal value of 10
			GetCollider()->setHalfWidth(10);
		}

		//Add a force in the correct direction multiplied by 1 if froggo is on a ladder, or 2 of not (makes froggo go half the speed when on ladders)
		AddForce(direction * (clibmable ? 1 : 2));

		//Get the distance between the froggos path point and the point on the path
		float distance = sqrt(pow(path->at(pathWaypointCounter).x - pathPoint.x, 2) + pow(path->at(pathWaypointCounter).y - pathPoint.y, 2));
		//If the distance is less than 3 (froggo is close enough to the point)
		if (distance < 3) {
			//Decrement the path counter to get the next point on the path
			pathWaypointCounter--;
			//Reset the path
			ResetPath();
			//Generate a new path to the player
			GeneratePath(Vector2(player->GetPosition().x, player->GetPosition().y - 5), dt);
		}
	}
	//Return the frames to use (ladder or walk)
	return framesToUse;
}

//Function to handle the defend state (takes in dt for generate path delay)
Vector4* Froggo::Defend(float dt) {
	//Create a variable to store which frames to use and set the default to walk frames
	Vector4* framesToUse = froggoWalkFrames;

	//Reset the dust spawned trigger
	dustSpawned = false;

	//Get the x and y distance to the player (absolute value to get distance regardless of sign)
	float xDistanceToPlayer = abs(position.x - player->GetPosition().x);
	float yDistanceToPlayer = abs(position.y - player->GetPosition().y);

	//If the x distance to the player is less than 3 tiles and the y distance is close (to prevent trying to attack when on a different level)
	if (xDistanceToPlayer <= 48 && yDistanceToPlayer < 8) {
		//Change the state to attack
		state = FroggoState::Attack;
	}
	//If the number of dusts since the froggo spawned is 0
	else if (dusts.size() == 0) {
		//Change the state to chase
		state = FroggoState::Chase;
	}
	//If the path counter is reset and a dust has not yet been spawned
	else if (pathWaypointCounter == -2 && !dustSpawned) {
		//Call the generate path function and pass the last dusts position and dt for the delay
		GeneratePath(dusts.at(dusts.size() - 1)->GetPosition(), dt);
	}
	//If the path counter is -1 (path is finished as 0 is the last item and will -1 to get the next point)
	else if (pathWaypointCounter == -1) {
		//Reset the path
		ResetPath();
		//Call the generate path function and pass the last dusts position and dt for the delay
		GeneratePath(dusts.at(dusts.size() - 1)->GetPosition(), dt);
	}
	//If the path counter is not finished 
	else if (pathWaypointCounter > -1) {
		//Get the direction between the froggos path point to the current paths point to go to
		Vector2 direction = path->at(pathWaypointCounter) - pathPoint;

		//If the direction on the x is less than 0 (going to the left)
		if (direction.x <= 0) {
			//Set the flip anim frame to false to make froggo face left
			flipAnimFrame = false;
		}
		//If the direction on the x is greater than or equal 0 (going to the right)
		else {
			//Set the flip anim frame to true to make froggo face right
			flipAnimFrame = true;
		}
		//If the absoluate direction of the y (ignore whether its up or down) is greater than 2 (intentionally moving up or down)
		if (abs(direction.y) > 2) {
			//Set the frame to use to be the ladder frames
			framesToUse = froggoLadderFrames;
			//Set the collider width to 6 to fit through on the ladders
			GetCollider()->setHalfWidth(6);
		}
		//If the froggo is not supposed to be moving on the y
		else {
			//Set the frame to use to be the walk frames
			framesToUse = froggoWalkFrames;
			//Set the collider width to the normal value of 10
			GetCollider()->setHalfWidth(10);
		}

		//Add a force in the correct direction multiplied by 1 if froggo is on a ladder, or 2 of not (makes froggo go half the speed when on ladders)
		AddForce(direction * (clibmable ? 1 : 2));

		//Get the distance between the froggos path point and the point on the path
		float distance = sqrt(pow(path->at(pathWaypointCounter).x - pathPoint.x, 2) + pow(path->at(pathWaypointCounter).y - pathPoint.y, 2));
		//If the distance is less than 3 (froggo is close enough to the point)
		if (distance < 3) {
			//Decrement the path counter to get the next point on the path
			pathWaypointCounter--;
			//Reset the path
			ResetPath();
			//Generate a new path to the dust
			GeneratePath(dusts.at(dusts.size() - 1)->GetPosition(), dt);
		}
	}
	//Return the frames to use (ladder or walk)
	return framesToUse;
}

//Function to handle the attack state
void Froggo::Attack() {
	//Set the collider width to larger to hit the player properly
	GetCollider()->setHalfWidth(24);
	
	//Get the x and y distance to the player (absolute value to get distance regardless of sign)
	float xDistanceToPlayer = abs(position.x - player->GetPosition().x);
	float yDistanceToPlayer = abs(position.y - player->GetPosition().y);

	//If the player is to the left of the froggo
	if (player->GetPosition().x < position.x) {
		//Set the flip anim frame to false to make froggo face left
		flipAnimFrame = false;
		//Set the amount to move the collider by to -12 to move the collider to the left and hit the player
		colliderMover = -12;
	}
	//If the player is to the right of the froggo
	else {
		//Set the flip anim frame to true to make froggo face right
		flipAnimFrame = true;
		//Set the amount to move the collider by to 12 to move the collider to the right and hit the player
		colliderMover = 12;
	}

	//If the distance to the player is greater than 3 tiles or the y distance is greater than 2 tiles
	if (xDistanceToPlayer > 48 || yDistanceToPlayer > 32) {
		//Change the state to defend
		state = FroggoState::Defend;
	}
}


bool Froggo::UpdateObject(float dt) {
	Vector4* animSource = froggoIdleFrames;

	//Set the path point of the froggo to the same x but lower on the y 
	pathPoint = Vector2(GetPosition().x, GetPosition().y - 6);
	//If the setStunned trigger has been set by the physics class
	//Set the state to stunned
	if (setStunned) state = FroggoState::Stun;
	//Switch the state variable
	switch (state)
	{
	//If the state is stun
	case FroggoState::Stun:
		//Change the sprites
		animSource = froggoStunFrames;
		//Call the stun function
		Stun(dt);
		break;
	//If the state is chase
	case FroggoState::Chase:
		//Call the chase function and set the anim source to the return (ladder or walk)
		animSource = Chase(dt);
		break;
	//If the state is defend
	case FroggoState::Defend:
		//Call the defend function and set the anim source to the return (ladder or walk)
		animSource = Defend(dt);
		break;
	//If the state is attack
	case FroggoState::Attack:
		//Change the sprites
		animSource = froggoAttackFrames;
		//Call the attack function
		Attack();
		break;
	}


	//Code to add gravity. Does not properly work as it makes the froggo bounce a lot on the floor
	/*
	//If the froggo is on a ladder, make the gravity weaker
	if (getClimbable()) {
		AddForce(Vector2(0, -75));
	}
	//If not, add gravity of -11
	else {
		AddForce(Vector2(0, -100));
	}
	*/
	
	//Set the frame data to the correct source
	animFrameData = animSource[currentanimFrame];
	//Move the collider to the position plus any movement (necessary for attacks)
	GetCollider()->setPosition(Vector2(GetPosition().x + colliderMover, GetPosition().y + 7));
	//Reset the amount to move the collider to 0
	colliderMover = 0;
	//Reset the climable variable
	clibmable = false;

	return true;
}