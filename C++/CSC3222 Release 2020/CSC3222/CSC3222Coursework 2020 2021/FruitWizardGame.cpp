#include "FruitWizardGame.h"
#include "SimObject.h"
#include "GameMap.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"
#include "GameSimsPhysics.h"
#include "PlayerCharacter.h"
#include "Fruit.h"
#include "Guard.h"
#include "Froggo.h"
#include "Pixie.h"
#include "PixieDust.h"
#include "Spell.h"

#include "Environment.h"

#include "Rectangle.h"
#include "Circle.h"

#include "CollisionVolume.h"

#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"

using namespace NCL;
using namespace CSC3222;

Pixie* pixie;

FruitWizardGame::FruitWizardGame() {
	renderer = new GameSimsRenderer();
	texManager = new TextureManager();
	physics = new GameSimsPhysics();
	SimObject::InitObjects(this, texManager);
	InitialiseGame();
}

FruitWizardGame::~FruitWizardGame() {
	delete currentMap;
	delete texManager;
	delete renderer;
	delete physics;
}

//Function to decrement fruit remaining
void FruitWizardGame::decrementFruitRemaining() {
	fruitRemaining--;
}

//Getter for the number of fruit remaining
int FruitWizardGame::getFruitRemaining() const {
	return fruitRemaining;
}
//Getter for deleting fruit
bool FruitWizardGame::getDeleteFruit() const {
	return deleteFruit;
}
//Getter for game time
float FruitWizardGame::getGameTime() const {
	return gameTime;
}
//Getter for restarting the game
bool FruitWizardGame::getRestartGame() const {
	return restartGame;
}
//Getter for the current map
GameMap* FruitWizardGame::getCurrentMap() const {
	return currentMap;
}
//Function to decrement magic count
void FruitWizardGame::DecrementMagicCount() {
	magicCount--;
}
//Function for getting magic count
int FruitWizardGame::GetMagicCount() {
	return magicCount;
}

//Function to place fruit in the map
void FruitWizardGame::placeFruit() {
	currentMap->ResetValidSpawnPositions();
	//Randomise seed
	srand((int)(gameTime * 1000.0f));
	
	//For each of the fruit remaining
	for (int i = 0; i < getFruitRemaining(); i++) {
		//Create fruit (will be changed to store fruit in list and move instead of create new ones)
		//(Since death is not possible yet, this only gets called once at the start)
		Fruit* f = new Fruit();
		//Get random position within the valid spawn positions
		int randPos = rand() % currentMap->getValidSpawnPositions()->size() / 2;
		int xPos, yPos;
		//Set the positions to the valid location
		xPos = currentMap->getValidSpawnPositions()->at(randPos * 2);
		yPos = currentMap->getValidSpawnPositions()->at((randPos * 2) + 1);
		//Remove the valid spawn location once it has been used
		currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
		currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
		//Set the position of the fruit
		f->SetPosition(Vector2((xPos * 16) + 8, (yPos * 16) + 8));
		//Call function to add collider to fruit
		f->AutoAddCollider();
		//Add the object
		AddNewObject(f);
	}
}

void FruitWizardGame::Update(float dt) {
	
	for (auto i : newObjects) {
		gameObjects.emplace_back(i);
	}
	newObjects.clear();

	gameTime += dt;
	
	renderer->Update(dt);
	physics->Update(dt);
	currentMap->DrawMap(*renderer);

	srand((int)(gameTime * 1000.0f));

	for (auto i = gameObjects.begin(); i != gameObjects.end(); ) {
		(*i)->UpdateAnimFrame(dt);
		if (!(*i)->UpdateObject(dt)) { //object has said its finished with
			//Remove the collider from the physics list
			physics->RemoveCollider((*i)->GetCollider());
			//Remove the rigid body from the physics list
			physics->RemoveRigidBody((*i));
			delete (*i);
			i = gameObjects.erase(i);
		}
		else {
			(*i)->DrawObject(*renderer);
			++i;
		}
	}

	//If set to delete the fruit call the place fruit function
	if (deleteFruit) {
		placeFruit();
	}

	deleteFruit = false;

	//If the chance to spawn has not passed, and the dust count is less than the max, and every 30 seconds (exluding the first second)
	if (!chancePassed && dustCount < 4 && ((int)gameTime) % 30 == 0 && gameTime >= 1) {
		//Get a rangom chance
		int chance = rand() % 5;
		//If the chance is 0 (one in 10 chance of that happening)
		if (chance == 0) {
			//Create a pixie dust object
			PixieDust* testDust = new PixieDust();
			//Get a random valid spawn location
			int randPos = rand() % currentMap->getValidSpawnPositions()->size() / 2;
			int xPos, yPos;
			//Set the positions to the valid location
			xPos = currentMap->getValidSpawnPositions()->at(randPos * 2);
			yPos = currentMap->getValidSpawnPositions()->at((randPos * 2) + 1);
			//Set the position of the dust
			testDust->SetPosition(Vector2((xPos * 16) + 8, (yPos * 16) + 12));
			testDust->AutoAddCollider();

			//Add the object
			AddNewObject(testDust);

			//If the froggo has been spawned
			if (spawnedFroggo) {
				//Reset his path
				froggo->ResetPath();
				//Set the trigger for a dust being spawned
				froggo->SetDustSpawned();
				//Add the dust to the froggos dust list
				froggo->AddToDusts(testDust);
				//Generate a path to the dust
				froggo->GeneratePath(Vector2((xPos * 16) + 8, (yPos * 16) + 12), dt);
			}

			//Remove the valid spawn location once it has been used
			currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
			currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));			
		}
		//Regardless of whether a dust was added or not, the chance to spawn has passed so set to true
		chancePassed = true;
	}
	//One second after the 30 second mark
	if (((int)gameTime % 30) == 1) {
		//Reset the chance passed value
		chancePassed = false;
	}

	//If the dust count is more than 4 and the control key has been pressed and pixie mode isnt already active
	if (dustCount >= 4 && Window::GetKeyboard()->KeyDown(KeyboardKeys::CONTROL) && !pixieMode) {
		//Set the bool to true
		pixieMode = true;
		//Set the pixie count to 8
		pixie->SetPixieCount(8);
		//Decrement the dust count by 4
		dustCount -= 4;
		//For each of the new pixies to be spawned
		for (int i = 0; i < 8; i++) {
			//Create a new pixie
			pixie = new Pixie();
			//Get a random valid spawn location
			int randPos = rand() % currentMap->getValidSpawnPositions()->size() / 2;
			int xPos, yPos;
			//Set the positions to the valid location
			xPos = currentMap->getValidSpawnPositions()->at(randPos * 2);
			yPos = currentMap->getValidSpawnPositions()->at((randPos * 2) + 1);

			//Set the pixies position
			pixie->SetPosition(Vector2((xPos * 16) + 8, (yPos * 16) + 8));
			//Add the collider
			pixie->AutoAddCollider();
			//Set pixies spring target to the player
			pixie->setSpringTarget(player);
			//Add the object
			AddNewObject(pixie);

			//Remove the valid spawn location once it has been used
			currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
			currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
		}
	}

	//If pixie mode is active and there are no more pixies
	if (pixieMode && pixie->GetPixieCount() == 0) {
		//Deactivate pixie mode
		pixieMode = false;
	}


	//Increment the current score by any points that are to be added
	currentScore += physics->getPointsToAdd();
	//If the fruit count should be decremented
	if (physics->getDecrementFruitCount()) {
		//Decrememnt the fruit count
		fruitRemaining--;
		//If there are no more fruit
		if (fruitRemaining == 0) {
			//If the froggo hasnt already been spawned
			if (!spawnedFroggo) {
				//Create the froggo, set its position, add its collider and add the object
				froggo = new Froggo(player, currentMap);
				froggo->SetPosition(Vector2(370, 287));
				froggo->AutoAddCollider();
				AddNewObject(froggo);
				//Set the spawned froggo bool to true and add the froggo to the pixie avoidance list
				spawnedFroggo = true;
				pixie->AddOtherObjects(froggo);
			}
			//Increment the score for collecting all the fruit
			currentScore += 5000;
			//Reset the fruit count
			fruitRemaining = 16;
			//Set the delete fruit to be true
			deleteFruit = true;

			//Get a random valid spawn location
			int randPos = rand() % currentMap->getValidSpawnPositions()->size() / 2;
			int xPos, yPos;
			//Set the positions to the valid location
			xPos = currentMap->getValidSpawnPositions()->at(randPos * 2);
			yPos = currentMap->getValidSpawnPositions()->at((randPos * 2) + 1);

			//Create a new guard and set its position
			Guard* newGuard = new Guard();
			newGuard->SetPosition(Vector2((xPos * 16) + 8, (yPos * 16) + 16));
			newGuard->setStartingPos();
			//Call function to add collider to guard
			newGuard->AutoAddCollider();
			//Set the player in the guard object
			newGuard->setPlayer(player);
			//Add the guard
			AddNewObject(newGuard);
			//Add the froggo to the pixie avoidance list
			pixie->AddOtherObjects(newGuard);

			//Remove the valid spawn location once it has been used
			currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
			currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
		}
	}
	//If the dust count should be incremented, increment the dust count
	if (physics->getIncrementDustCount()) {
		dustCount++;
	}
	//If the magic count should be incremented, increment the magic count
	if (physics->getIncrementMagicCount()) {
		magicCount++;
	}
	//If the player should lose a life
	if (physics->getLoseLife()) {
		//Decrement lives
		lives--;
		//Reset the players position
		player->SetPosition(Vector2(32, 35));
		//Set the players collider to the players new position
		player->GetCollider()->setPosition(Vector2(32, 35));
		//Delete the fruit to respawn
		deleteFruit = true;

		//If pixie mode is active
		if (pixieMode) {
			//For all of the boids
			for (int i = 0; i < pixie->getBoids().size(); i++) {
				//If the boid is a pixie
				if (pixie->getBoids().at(i)->GetCollider()->getObjectType() == ObjectTypes::Pixie) {
					//Set the pixie to be deleted
					pixie->getBoids().at(i)->setToDeleteObject();
				}
			}
		}
	}
	//If there is a dust to be deleted and the froggo has been spawned
	if (physics->getDustToDelete() != nullptr && spawnedFroggo) {
		//Remove the dust from the froggos dust list
		froggo->RemoveDust(physics->getDustToDelete());
	}
	//Reset all the gameplay event variables
	physics->resetGameEventVariables();

	//If the lives is less than or equal to 0
	if (lives <= 0) {
		//Set the game to be restarted
		restartGame = true;
	}
	


	renderer->DrawString("Score:" + std::to_string(currentScore),
		Vector2(32, 12), Vector4(1, 1, 1, 1), 100.0f);
	renderer->DrawString("Lives:" + std::to_string(lives),
		Vector2(144, 12), Vector4(1, 0, 0, 1), 100.0f);
	renderer->DrawString("Magic:" + std::to_string(magicCount),
		Vector2(256, 12), Vector4(1, 0, 0.5f, 1), 100.0f);
	renderer->DrawString("Dust:" + std::to_string(dustCount),
		Vector2(366, 12), Vector4(0.5f, 0.3f, 0.8f, 1), 100.0f);

	/*
	Some examples of debug rendering!
	These all use coordinates in the same 'space' as the game positions
	*/

	//Draw the players collider
	/*
	renderer->DrawBox(player->GetCollider()->getPosition(), player->GetCollider()->getHalfSize(), Vector4(1, 0, 0, 1));
	*/

	//Path points
	
	//If the froggo has been spawned
	if (spawnedFroggo) {
		//For each of the points in the path
		for (int i = 0; i < froggo->GetPath()->size(); i++) {
			//Draw a circle at that position
			renderer->DrawCircle(froggo->GetPath()->at(i), 1, Vector4(1, 0, 0, 1));
		}
	}
	
	

	/*// Walls
	//Main Left Wall
	renderer->DrawBox(Vector2(8, 160), Vector2(8, 160), Vector4(0, 0, 0, 1));
	//Main Right Wall
	renderer->DrawBox(Vector2(472, 160), Vector2(8, 160), Vector4(0, 0, 0, 1));
	*/
	/*
	// Floors
	//Floor 1
	renderer->DrawBox(Vector2(240, 8), Vector2(240, 8), Vector4(0, 0, 0, 1));
	//Floor 2 Column 1
	renderer->DrawBox(Vector2(56, 72), Vector2(40, 8), Vector4(0, 0, 0, 1));
	//Floor 2 Column 2
	renderer->DrawBox(Vector2(136, 72), Vector2(8, 8), Vector4(0, 0, 0, 1));
	//Floor 2 Column 3
	renderer->DrawBox(Vector2(208, 72), Vector2(32, 8), Vector4(0, 0, 0, 1));
	//Floor 2 Column 4
	renderer->DrawBox(Vector2(368, 72), Vector2(96, 8), Vector4(0, 0, 0, 1));
	//Floor 3 Column 1
	renderer->DrawBox(Vector2(264, 136), Vector2(88, 8), Vector4(0, 0, 0, 1));
	//Floor 3 Column 2
	renderer->DrawBox(Vector2(424, 136), Vector2(40, 8), Vector4(0, 0, 0, 1));
	//Floor 4 Column 1
	renderer->DrawBox(Vector2(112, 200), Vector2(64, 8), Vector4(0, 0, 0, 1));
	//Floor 4 Column 2
	renderer->DrawBox(Vector2(216, 200), Vector2(8, 8), Vector4(0, 0, 0, 1));
	//Floor 4 Column 3
	renderer->DrawBox(Vector2(280, 200), Vector2(8, 8), Vector4(0, 0, 0, 1));
	//Floor 4 Column 4
	renderer->DrawBox(Vector2(344, 200), Vector2(24, 8), Vector4(0, 0, 0, 1));
	//Floor 5 Column 1
	renderer->DrawBox(Vector2(48, 264), Vector2(32, 8), Vector4(0, 0, 0, 1));
	//Floor 5 Column 2
	renderer->DrawBox(Vector2(120, 264), Vector2(8, 8), Vector4(0, 0, 0, 1));
	//Floor 5 Column 3
	renderer->DrawBox(Vector2(312, 264), Vector2(104, 8), Vector4(0, 0, 0, 1));
	//Floor 5 Column 3
	renderer->DrawBox(Vector2(456, 264), Vector2(8, 8), Vector4(0, 0, 0, 1));
	*/
	

	/*// Ladders
	//Row 1 Column 1 Ladder
	renderer->DrawBox(Vector2(112, 48), Vector2(16, 32), Vector4(0, 0, 0, 1));
	//Row 1 Column 2 Ladder
	renderer->DrawBox(Vector2(256, 48), Vector2(16, 32), Vector4(0, 0, 0, 1));
	//Row2and3 Column 1 Ladder
	renderer->DrawBox(Vector2(32, 144), Vector2(16, 64), Vector4(0, 0, 0, 1));
	//Row 2 Column 2 Ladder
	renderer->DrawBox(Vector2(368, 112), Vector2(16, 32), Vector4(0, 0, 0, 1));
	//Row 3 Column 2 Ladder
	renderer->DrawBox(Vector2(192, 176), Vector2(16, 32), Vector4(0, 0, 0, 1));
	//Row 3 Column 3 Ladder
	renderer->DrawBox(Vector2(304, 176), Vector2(16, 32), Vector4(0, 0, 0, 1));
	//Row 4 Column 1 Ladder
	renderer->DrawBox(Vector2(96, 240), Vector2(16, 32), Vector4(0, 0, 0, 1));
	//Row 3and4 Column 2 Ladder
	renderer->DrawBox(Vector2(432, 208), Vector2(16, 64), Vector4(0, 0, 0, 1));
	*/

	/* Available spawn locations
	for (int i = 0; i < currentMap->getValidSpawnPositions()->size() - 1; i += 2) {
		int temp1, temp2;
		temp1 = currentMap->getValidSpawnPositions()->at(i) * 16;
		temp2 = currentMap->getValidSpawnPositions()->at(i + 1) * 16;
		renderer->DrawBox(Vector2(temp1+8, temp2+8), Vector2(8, 8), Vector4(0, 1, 0, 1));
	}
	*/
	renderer->Render();
}

//Function to add environment colliders
void FruitWizardGame::AddEnvironmentCollisions() {
	
	Environment* wallColliders = new Environment();
	Environment* floorColliders = new Environment();
	Environment* ladderColliders = new Environment();

	//Create volumes for the left and right walls
	CollisionVolume* leftWall = new Rectangle(8, 160, Vector2(8, 160), "Rectangle", true, ObjectTypes::Wall, wallColliders);
	CollisionVolume* rightWall = new Rectangle(8, 160, Vector2(472, 160), "Rectangle", true, ObjectTypes::Wall, wallColliders);
	
	//Add the colliders to the physics list
	physics->AddCollider(leftWall);
	physics->AddCollider(rightWall);

	//Create list of floor colliders
	CollisionVolume* floors[15];
	floors[0] = new Rectangle(240, 8, Vector2(240, 8), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[1] = new Rectangle(40, 8, Vector2(56, 72), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[2] = new Rectangle(8, 8, Vector2(136, 72), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[3] = new Rectangle(32, 8, Vector2(208, 72), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[4] = new Rectangle(96, 8, Vector2(368, 72), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[5] = new Rectangle(88, 8, Vector2(264, 136), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[6] = new Rectangle(40, 8, Vector2(424, 136), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[7] = new Rectangle(64, 8, Vector2(112, 200), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[8] = new Rectangle(8, 8, Vector2(216, 200), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[9] = new Rectangle(8, 8, Vector2(280, 200), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[10] = new Rectangle(24, 8, Vector2(344, 200), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[11] = new Rectangle(32, 8, Vector2(48, 264), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[12] = new Rectangle(8, 8, Vector2(120, 264), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[13] = new Rectangle(104, 8, Vector2(312, 264), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	floors[14] = new Rectangle(8, 8, Vector2(456, 264), "Rectangle", true, ObjectTypes::Floor, floorColliders);
	
	//For every collider
	for (CollisionVolume* floor : floors)
	{
		//Add it to the physics list
		physics->AddCollider(floor);
	}


	//Create list of ladder colliders
	CollisionVolume* ladders[8];
	ladders[0] = new Rectangle(16, 32, Vector2(112, 48), "Rectangle", true, ObjectTypes::Ladder, ladderColliders);
	ladders[1] = new Rectangle(16, 32, Vector2(256, 48), "Rectangle", true, ObjectTypes::Ladder, ladderColliders);
	ladders[2] = new Rectangle(16, 64, Vector2(32, 144), "Rectangle", true, ObjectTypes::Ladder, ladderColliders);
	ladders[3] = new Rectangle(16, 32, Vector2(368, 112), "Rectangle", true, ObjectTypes::Ladder, ladderColliders);
	ladders[4] = new Rectangle(16, 32, Vector2(192, 176), "Rectangle", true, ObjectTypes::Ladder, ladderColliders);
	ladders[5] = new Rectangle(16, 32, Vector2(304, 176), "Rectangle", true, ObjectTypes::Ladder, ladderColliders);
	ladders[6] = new Rectangle(16, 32, Vector2(96, 240), "Rectangle", true, ObjectTypes::Ladder, ladderColliders);
	ladders[7] = new Rectangle(16, 64, Vector2(432, 208), "Rectangle", true, ObjectTypes::Ladder, ladderColliders);
	//For every collider
	for (CollisionVolume* ladder : ladders)
	{
		//Add it to the physics list
		physics->AddCollider(ladder);
	}
}

void FruitWizardGame::InitialiseGame() {
	//Set the restart game bool and spawned froggo bool to false
	restartGame = false;
	spawnedFroggo = false;

	delete currentMap;
	for (auto o : gameObjects) {
		delete o;
	}
	gameObjects.clear();

	currentMap = new GameMap("FruitWizardMap.txt", gameObjects, *texManager);

	renderer->SetScreenProperties(16, currentMap->GetMapWidth(), currentMap->GetMapHeight());

	//Call function to add environment collisions
	AddEnvironmentCollisions();
	
	//Create the player and set its position
	player = new PlayerCharacter();
	player->SetPosition(Vector2(32, 35));
	//Call function to add collider to player
	player->AutoAddCollider();
	AddNewObject(player);

	//For each of the 4 guards to spawn
	for (int i = 0; i < 4; i++) {
		//Get a random valid spawn location
		int randPos = rand() % currentMap->getValidSpawnPositions()->size() / 2;
		int xPos, yPos;
		//Set the positions to the valid location
		xPos = currentMap->getValidSpawnPositions()->at(randPos * 2);
		yPos = currentMap->getValidSpawnPositions()->at((randPos * 2) + 1);

		//Create a new guard and set its position
		Guard* testGuard = new Guard();
		testGuard->SetPosition(Vector2((xPos * 16), (yPos * 16) + 16));
		testGuard->setStartingPos();
		//Call function to add collider to guard
		testGuard->AutoAddCollider();
		//Set the guards player variable
		testGuard->setPlayer(player);
		AddNewObject(testGuard);
		//Add the guard to the pixies boid list
		pixie->AddOtherObjects(testGuard);

		//Remove the valid spawn location once it has been used
		currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
		currentMap->getValidSpawnPositions()->erase(currentMap->getValidSpawnPositions()->begin() + (randPos * 2));
	}
	
	//Initialise gameplay variables and game time
	gameTime = 0;
	currentScore = 0;
	magicCount = 4;
	dustCount = 0;
	lives = 3;

	//Set chance passed to false
	chancePassed = false;
	//Set number of fruits to 16
	fruitRemaining = 16;

	deleteFruit = false;
	pixieMode = false;

	//Place the fruit
	placeFruit();
}

void FruitWizardGame::AddNewObject(SimObject* object) {
	newObjects.emplace_back(object);
	physics->AddRigidBody(object);
	if (object->GetCollider()) {
		physics->AddCollider(object->GetCollider());
	}
}

