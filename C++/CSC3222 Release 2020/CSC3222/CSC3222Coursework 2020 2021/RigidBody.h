#pragma once
#include "../../Common/Vector2.h"

namespace NCL {
	using namespace Maths;
	namespace CSC3222 {
		class RigidBody	{
			friend class GameSimsPhysics;
		public:
			RigidBody();
			~RigidBody();

			Vector2 GetPosition() const {
				return position;
			}

			void SetPosition(const Vector2& newPosition) {
				position = newPosition;
			}

			Vector2 GetVelocity() const {
				return velocity;
			}

			void SetVelocity(const Vector2& newVelocity) {
				velocity = newVelocity;
			}

			void AddForce(const Vector2& newForce) {
				force += newForce;
			}

			//Function to add impulse
			void AddImpulse(const Vector2& newImpulse) {
				//Manipulates velocity directly based on impulse given and inverse mass
				velocity += newImpulse * inverseMass;
				if (velocity.x > 100) {
					velocity.x = 100;
				}
				else if (velocity.x < -100) {
					velocity.x = -100;
				}
				if (velocity.y > 100) {
					velocity.y = 100;
				}
				else if (velocity.y < -100) {
					velocity.y = -100;
				}
			}

			//Setter for the dampening factor
			void setDampeningFactor(const float newDampeningFactor) {
				dampeningFactor = newDampeningFactor;
			}
			//Setter for the inverse mass
			void setInverseMass(const float newInverseMass) {
				inverseMass = newInverseMass;
			}
			float getInverseMass() const {
				return inverseMass;
			}

			//Setter for deleting this object
			void setToDeleteObject() {
				deleteThisObject = true;
			}
			//Setter for climbable
			void setClimbable(bool newValue) {
				clibmable = newValue;
			}
			//Getter for climable
			bool getClimbable() {
				return clibmable;
			}
			//Setter for going right
			void setGoingRight(bool newValue) {
				goingRight = newValue;
			}

			//Virtual function for incrementing bounces
			virtual void incrementBounces() {}

			//Getter for last wall that was collided with
			Vector2 GetLastWallCollided() {
				return lastFrameCollided;
			}
			//Setter for last wall that was collided with
			void SetLastWallCollided(Vector2 value) {
				lastFrameCollided = value;
			}
			//Function to set the stunned trigger and direction
			void SetStunned(int dir) {
				setStunned = true;
				stunDir = dir;
			}
			//Getter for the stunned trigger
			bool GetStunned() {
				return setStunned;
			}
			
		protected:
			Vector2 position;
			Vector2 velocity;
			Vector2 force;
			
			float inverseMass;
			float elasticity;
			//Variable to store the dampening factor for each object
			float dampeningFactor;


			bool deleteThisObject;
			bool clibmable;
			bool goingRight;
			bool setStunned;
			int stunDir;
			Vector2 lastFrameCollided;
		};
	}
}
