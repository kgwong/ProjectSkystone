#include "DieOnCollision.h"



DieOnCollision::DieOnCollision(GameObject& owner)
	: Component(owner)
{
}


DieOnCollision::~DieOnCollision()
{
}

void DieOnCollision::handleEvent(const CollisionEvent& e)
{
	owner_.kill();
}
