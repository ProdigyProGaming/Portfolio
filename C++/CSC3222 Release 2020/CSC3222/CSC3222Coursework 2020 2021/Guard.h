#pragma once
#include "SimObject.h"

namespace NCL::CSC3222 {
	class Guard : public SimObject	{
	public:
		Guard();
		~Guard();

		bool UpdateObject(float dt) override;

		//Function to add collider
		void AutoAddCollider();

		//Function to set the starting position
		void setStartingPos();
		//Function to set the player
		void setPlayer(SimObject* newPlayer);

		//State functions
		void Stun(float dt);
		void Chase();
		void Patrol();
		void Attack();

		

	protected:
		//Enumeration for the guard state
		enum class GuardState {
			Stun,
			Chase,
			Patrol,
			Attack
		};
		//Variable to store the state
		GuardState state;

		//Timer for being stunned
		float stunTimer;
		//Variable for the starting position
		Vector2 startingPos;
		//Variable to store the player
		SimObject* player;
		//How much to move the collider
		int colliderMover;
	};
}