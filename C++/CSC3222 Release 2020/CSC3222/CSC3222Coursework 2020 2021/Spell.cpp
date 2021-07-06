#include "Spell.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"

#include "CollisionVolume.h"
#include "Circle.h"

#include "../../Common/Maths.h"

#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"

using namespace NCL;
using namespace CSC3222;

Vector4 activeFrames[] = {
	Vector4(512,384, 32, 32),
	Vector4(512,384, 32, 32),
	Vector4(512,384, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(384,416, 32, 32),
};

Vector4 explodeFrames[] = {
	Vector4(512,384, 32, 32),
	Vector4(384,416, 32, 32),
	Vector4(416,416, 32, 32),
	Vector4(448,416, 32, 32),
	Vector4(480,416, 32, 32),
	Vector4(512,416, 32, 32),	
};

Spell::Spell(Vector2 direction) : SimObject()	{
	texture		= texManager->GetTexture("FruitWizard\\mini_fantasy_sprites_oga_ver.png");
	velocity	= direction;
	animFrameCount = 6;
	currentLifeTime = 0;
	//Set bounces to 0
	bounces = 0;
	//Set trigger for if a bounce has been added to false
	incrementedBounces = false;
	//Add impulse in specific direction
	AddImpulse(Vector2(copysign(10, velocity.x), velocity.y));
	//Set dampening factor to 1 so no dampening occurs
	dampeningFactor = 1;
}

Spell::~Spell()	{
}

//Function to add collider (cant be in the constructor as position hasnt been set yet)
void Spell::AutoAddCollider() {
	//Create collision volume for the spell
	CollisionVolume* cv3 = new Circle(8, GetPosition(), "Circle", false, ObjectTypes::Spell, this);
	//Set the spells collider
	SetCollider(cv3);
}

//Function to increment number of bounces
void Spell::incrementBounces() {
	//Incrememnt bounce count
	bounces++;
}

void Spell::DrawObject(GameSimsRenderer &r) {
	Vector4	texData = explodeFrames[currentanimFrame];
	Vector2 texPos	= Vector2(texData.x, texData.y);
	Vector2 texSize = Vector2(texData.z, texData.w);
	r.DrawTextureArea((OGLTexture*)texture, texPos, texSize, position);
}

bool Spell::UpdateObject(float dt) {
	//Increase lifetime variable by dt
	currentLifeTime += dt;
	//If the spell has been active for more than 5 seconds or if the object is to be deleted or if it has bounced 3 times
	if (currentLifeTime >= 5.0f || deleteThisObject || bounces > 2) {
		//Return false to remove the spell from the game
		return false;
	}
	animFrameData = explodeFrames[currentanimFrame];
	//Update the colliders position
	GetCollider()->setPosition(this->GetPosition());
	return true;
}