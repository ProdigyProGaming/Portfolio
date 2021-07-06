#pragma once
#include <vector>
#include "../../Common/Vector2.h"
#include "SimObject.h"

namespace NCL {
	
	namespace CSC3222 {
		class RigidBody;
		class CollisionVolume;
		
		//Collision pair definition
		struct CollisionPair
		{
			//Collision volume pointers
			CollisionVolume* a = nullptr;
			CollisionVolume* b = nullptr;
			//Vector2 to store the collision normal
			NCL::Maths::Vector2 normal = NCL::Maths::Vector2(0, 0);
			//Float to store the penetration distance
			float penetration;
			
		};
		
		class GameSimsPhysics	{
		public:
			GameSimsPhysics();
			~GameSimsPhysics();

			void Update(float dt);

			void AddRigidBody(RigidBody* b);
			void RemoveRigidBody(RigidBody* b);

			void AddCollider(CollisionVolume* c);
			void RemoveCollider(CollisionVolume* c);

			//Function to reset any gameplay trigger variables
			void resetGameEventVariables() {
				pointsToAdd = 0;
				decrementFruitCount = false;
				spawnGuard = false;
				incrementDustCount = false;
				loseLife = false;
				incrementMagicCount = false;
				dustToDelete = nullptr;
			}

			//Getters for gameplay event triggers
			int getPointsToAdd() const {
				return pointsToAdd;
			}
			bool getDecrementFruitCount() const {
				return decrementFruitCount;
			}
			bool getIncrementDustCount() const {
				return incrementDustCount;
			}
			bool getLoseLife() const {
				return loseLife;
			}
			bool getIncrementMagicCount() const {
				return incrementMagicCount;
			}
			RigidBody* getDustToDelete() const {
				return dustToDelete;
			}

		protected:
			//Functions for physic steps
			void Integration(float dt);
			void IntegrateVelocity(float dt);
			void CollisionDetection(float dt);
			void CollisionResolution(float dt);
			void InsertionSort();
			void NarrowPhase(CollisionVolume* volume1, CollisionVolume* volume2);

			//Float for fixed update
			float timeRemaining = 0;

			std::vector<RigidBody*>		allBodies;
			std::vector<CollisionVolume*>	allColliders;
			//Vector to store all collisions
			std::vector<CollisionPair>		collisions;

			//Gameplay event triggers
			int pointsToAdd = 0;
			bool decrementFruitCount = false;
			bool spawnGuard = false;
			bool incrementDustCount = false;
			bool loseLife = false;
			bool incrementMagicCount = false;
			RigidBody* dustToDelete = nullptr;
		};
	}
}

