#pragma once
#include "SimObject.h"

namespace NCL {
	namespace Maths {
		class Vector2;
	}
	namespace CSC3222 {
		class Spell : public SimObject {
		public:
			Spell(Vector2 direction);
			~Spell();

			void DrawObject(GameSimsRenderer &r) override;
			bool UpdateObject(float dt) override;
			//Function to add collider
			void AutoAddCollider();
			//Function to increment bounces
			void incrementBounces();

		protected:
			//Lifetime variable to store how long the spell has been active
			float currentLifeTime;
			//Variable to store bounce count
			int bounces;
			//Bool to track if bounce has been added
			bool incrementedBounces;
		};
	}
}

