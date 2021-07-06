#pragma once

#include "CollisionVolume.h"

//Circle class to manage circle colliders
namespace NCL {
	namespace CSC3222 {
		class Circle : public CollisionVolume
		{
		public:
			//Constructor
			Circle(float newRadius, Vector2 newPosition, std::string newType, bool newIsStatic, ObjectTypes newObjectType, RigidBody* newBody);

			//Getter for radius
			float getRadius() const override;

			//Setter for radius
			void setRadius(float newRadius);

		protected:
			//Float to store radius value
			float radius;
		};
	}
}