#include "DieOnCollision.h"



DieOnCollision::DieOnCollision(GameObject& owner)
	: NonUpdatingComponent(owner)
{
}


DieOnCollision::~DieOnCollision()
{
}

void DieOnCollision::handleEvent(const CollisionEvent& e)
{
	owner_.kill();
}
