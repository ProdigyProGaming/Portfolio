#pragma once
#include "SimObject.h"
//Environment class for potnetially storing world collisions (ladders and walls)
namespace NCL::CSC3222 {
	class Environment : public SimObject {
	public:
		Environment();
		~Environment();

		bool UpdateObject(float dt) override;

	protected:

	};
}

