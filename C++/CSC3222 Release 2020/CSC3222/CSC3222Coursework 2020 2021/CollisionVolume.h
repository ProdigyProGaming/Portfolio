#pragma once
#include "RigidBody.h"
#include <vector>
#include "GameSimsPhysics.h"
namespace NCL {
	namespace CSC3222 {
		enum class ObjectTypes {
			Player,
			Wall,
			Floor,
			Ladder,
			King,
			Guard,
			Pixie,
			Dust,
			Spell,
			Fruit
		};
		class CollisionVolume {
		public:

			CollisionVolume(Vector2 position, std::string newType, bool newIsStatic, ObjectTypes newObjectType, RigidBody* newBody);
			~CollisionVolume();

			//Getters for the sizes of collision volumes
			virtual float getHalfWidth() const { return 0; };
			virtual float getHalfHeight() const { return 0; };
			virtual Vector2 getHalfSize() const { return {}; };
			virtual float getRadius() const { return 0; };

			virtual void setHalfWidth(float) {};
			virtual void setHalfHeight(float) {};
			virtual void setRadius(float) {};

			//Getter for other relevant veriables
			Vector2 getPosition() const;
			std::string getType() const;
			bool getIsStatic() const;
			ObjectTypes getObjectType() const;

			//Function to add sub collision volume
			void addChildVolume(CollisionVolume* newChildVolume);
			//Return list of sub collision volumes
			std::vector<CollisionVolume*>* getChildrenVolumes() const {
				return childCollisionVolumes;
			};

			//Setter for position
			void setPosition(Vector2 newPosition);
			//Function for clamping values
			float clamp(float value, float minValue, float maxValue);
			
			//Function to check collision
			bool CheckCollision(CollisionVolume* volume1, CollisionPair* cp);

			
			RigidBody* getBody() const;


		protected:
			//Vector to store all sub colliders
			std::vector<CollisionVolume*>* childCollisionVolumes;
			//Relevant variables for a collision volume
			Vector2 position;
			std::string type;
			bool isStatic;

			ObjectTypes objectType;

			RigidBody* body;

		};
	}
}