#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector4.h"
#include "RigidBody.h"
#include <vector>

namespace NCL {
	using namespace Maths;

	namespace Rendering {
		class TextureBase;
	}
	namespace CSC3222 {
		class GameSimsRenderer;
		class TextureManager;
		class FruitWizardGame;
		class RigidBody;
		class CollisionVolume;

		class SimObject	: public RigidBody {
		public:
			SimObject();
			~SimObject();

			//Sets the main collider
			void SetCollider(CollisionVolume* c) {
				collider = c;
			}
			//Add collider adds given collision volume to colliders list
			void AddCollider(CollisionVolume * c) {
				colliders->emplace_back() = c;
			}
			//Getter for main collider
			CollisionVolume* GetCollider() const {
				return collider;
			}
			//Getter for specific collider at index
			CollisionVolume* GetSubCollider(int index) const {
				return colliders->at(index);
			}
			//Getter for colliders list returns full list
			std::vector<CollisionVolume*>* GetColliders() const {
				return colliders;
			}

			void	UpdateAnimFrame(float dt);

			virtual bool UpdateObject(float dt) = 0;

			virtual void DrawObject(GameSimsRenderer &r);

			static void InitObjects(FruitWizardGame* game, TextureManager* manager);
			
			//Setter for spring target sets the target to the given sim object
			void setSpringTarget(SimObject* newSpringTarget) {
				springTarget = newSpringTarget;
			}
			//Getter for spring target returns the pointer
			SimObject* getSpringTarget() {
				return springTarget;
			}

			
		protected:
			CollisionVolume*				collider;
			//Store vector of collision volumes if object has multiple colliders e.g. ladders
			std::vector <CollisionVolume*>* colliders;
			Rendering::TextureBase*			texture;

			
			Vector4			animFrameData;
			int				currentanimFrame;
			bool			flipAnimFrame;
			int				animFrameCount;
			float			frameTime;
			float			frameRate;
			//Store sim object pointer as spring target
			SimObject*		springTarget;

			

			static TextureManager*  texManager;
			static FruitWizardGame*		game;
		};
	}
}

