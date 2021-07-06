#pragma once
#include "SimObject.h"

namespace NCL::CSC3222 {
	class Pixie : public SimObject	{
	public:
		
		Pixie();
		~Pixie();

		bool UpdateObject(float dt) override;
		
		//Function to add other objects to the boid list
		void AddOtherObjects(SimObject* newObject);
		//Function to get the boid list
		std::vector<SimObject*> getBoids();
		//Function to add collider
		void AutoAddCollider();

		//Function to set the pixie count
		void SetPixieCount(int count);
		//Function to get the pixie count
		int GetPixieCount();
		
	protected:

		//Flocking functions
		Vector2 Alignment();
		Vector2 Seperation();
		Vector2 Cohesion();
		Vector2 Avoidance();

		//Static boid list
		static std::vector<SimObject*> allBoids;
		//Static count
		static int pixieCount;
	};
}