#include "PixieDust.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"

#include "Rectangle.h"

using namespace NCL;
using namespace CSC3222;

Vector4 animFrames[] = {
	Vector4(64 , 192, 32, 32),
	Vector4(96, 192, 32, 32),
	Vector4(128, 192, 32, 32),
	Vector4(160, 192, 32, 32)
};

PixieDust::PixieDust() : SimObject() {
	animFrameCount = 4;
	texture = texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
	inverseMass = 0;
}

PixieDust::~PixieDust() {
}

//Function to add collider (cant be in the constructor as position hasnt been set yet)
void PixieDust::AutoAddCollider() {
	//Create collider at position of specific size
	CollisionVolume* cv2 = new Rectangle(8, 8, GetPosition(), "Rectangle", true, ObjectTypes::Dust, this);
	//Set the collider
	SetCollider(cv2);
}

bool PixieDust::UpdateObject(float dt) {
	//If this object is to be deleted, return false
	if (deleteThisObject) {
		return false;
	}
	animFrameData = animFrames[currentanimFrame];

	return true;
}