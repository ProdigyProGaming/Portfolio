#pragma once
#include <vector>

namespace NCL::CSC3222 {
	class GameMap;
	class SimObject;
	class GameSimsRenderer;
	class GameSimsPhysics;
	class TextureBase;
	class TextureManager;
	class PlayerCharacter;
	class Froggo;

	class FruitWizardGame {
	public:
		FruitWizardGame();
		~FruitWizardGame();

		void Update(float dt);

		//Function to decrement magic count
		void DecrementMagicCount();
		//Getter for magic count
		int GetMagicCount();

		void AddNewObject(SimObject* object);

		//Getter for fruit remaining
		int getFruitRemaining() const;
		//Function to decrement fruit remaining
		void decrementFruitRemaining();
		//Function to place fruit in game
		void placeFruit();

		//Getter for fruit deletion bool
		bool getDeleteFruit() const;
		//Getter for current map
		GameMap* getCurrentMap() const;
		//Getter for game time
		float getGameTime() const;
		//Getter for restart game trigger
		bool getRestartGame() const;

	protected:
		void InitialiseGame();
		//Function to add environment collisions
		void AddEnvironmentCollisions();

		TextureManager*		texManager;
		GameSimsRenderer*	renderer;
		GameSimsPhysics*	physics;
		GameMap* currentMap;

		PlayerCharacter* player;
		Froggo* froggo;

		//Game time
		float gameTime;
		//Bool for chance of spawning items after time
		bool chancePassed;

		int currentScore;
		int magicCount;
		int dustCount;
		int lives;
		//Value for number of fruit remaining
		int fruitRemaining;
		//Bool for fruit deletion
		bool deleteFruit;

		std::vector<SimObject*> gameObjects;
		std::vector<SimObject*> newObjects;

		//Bool to restart the game
		bool restartGame;
		//Bool for whether the froggo has been spawned
		bool spawnedFroggo;
		//Bool for pixie mode
		bool pixieMode;
	};
}