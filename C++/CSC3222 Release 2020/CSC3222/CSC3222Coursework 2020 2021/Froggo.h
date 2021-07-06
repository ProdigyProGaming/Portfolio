#pragma once
#include "SimObject.h"
#include "GameMap.h"

namespace NCL::CSC3222 {
	class Froggo : public SimObject {
	public:
		Froggo(SimObject* targetPlayer, GameMap* map);
		~Froggo();

		bool UpdateObject(float dt) override;

		//Function to add collider
		void AutoAddCollider();

		//Getter for the path
		std::vector<Vector2>* GetPath();
		//Function to reset the path
		void ResetPath();

		//Functions for managing dust spawns and collections
		void SetDustSpawned();
		void RemoveDust(RigidBody* dustToRemove);
		void AddToDusts(RigidBody* newDust);

		//Function to generate paths
		void GeneratePath(Vector2 target, float dt);

		//State functions
		void Stun(float dt);
		Vector4* Chase(float dt);
		Vector4* Defend(float dt);
		void Attack();
		

		Vector4* Move(Vector2 target, float dt);


	protected:
		//Enumeration for the froggos state
		enum class FroggoState {
			Stun,
			Chase,
			Defend,
			Attack
		};
		//Variable to store the state
		FroggoState state;
		
		//Timer for being stunned
		float stunTimer;
		//Variable to store the player object
		SimObject* player;
		//The current path
		std::vector<Vector2>* path;
		//The path counter
		int pathWaypointCounter;
		//The path point on the froggo
		Vector2 pathPoint;
		//The game map
		GameMap* currentMap;
		//Trigger for dust spawned
		bool dustSpawned;
		//Vector to store all dusts after froggo was spawned
		vector<RigidBody*> dusts;
		//How much to move the collider
		int colliderMover;
		//The path generator delay
		float pathGenDelay;
	};
}