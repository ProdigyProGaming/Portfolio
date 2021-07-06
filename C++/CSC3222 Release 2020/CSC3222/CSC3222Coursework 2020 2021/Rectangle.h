#pragma once

#include "CollisionVolume.h"

//Rectangle class to manage Rectangle colliders
namespace NCL {
	namespace CSC3222 {
		class Rectangle : public CollisionVolume
		{
			public:
				//Constructor
				Rectangle(float newHalfWidth, float newHalfHeight, Vector2 newPosition, std::string newType, bool newIsStatic, ObjectTypes newObjectType, RigidBody* newBody);

				//Getter for half sizes
				float getHalfWidth() const override;
				float getHalfHeight() const override;
				Vector2 getHalfSize() const override;

				//Setter for half sizes
				void setHalfWidth(float newHalfWidth) override;
				void setHalfHeight(float newHalfHeight) override;

			protected:
				//Vector2 to store half sizes
				Vector2 halfSize;
		};
	}
}

