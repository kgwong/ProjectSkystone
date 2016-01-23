#include "LiftComponent.h"
#include "PhysicsComponent.h"

#include <iostream>
using namespace std;

LiftComponent::LiftComponent(GameObject & owner)
	: UpdatingComponent(owner),
	xRadius_(DEFAULT_X_RADIUS)
{
	delay = 0;
}


LiftComponent::~LiftComponent()
{
}

void LiftComponent::start(Level & level)
{
	physics_ = owner_.getComponent<PhysicsComponent>();
}

void LiftComponent::update(Level & level)
{
	PhysicsComponent *playerPhysics = level.player->getComponent<PhysicsComponent>();

	if (!playerPhysics->gravityEnabled() && delay >= 50)
	{
		playerPhysics->setVelY(0);
		playerPhysics->enableGravity(true);
		delay = 0;

	}
	else
		delay++;
}

void LiftComponent::handleEvent(const CollisionEvent & other)
{

	if (other.getOtherObject().getType() == GameObject::Type::PLAYER)
	{
		ColliderComponent *playerCollider = other.getOtherObject().getComponent<ColliderComponent>();
		PhysicsComponent *playerPhysics = other.getOtherObject().getComponent<PhysicsComponent>();
		playerCollider->getTop();
		playerPhysics->enableGravity(false);
		playerPhysics->setVelY(-20);
	}
}

int LiftComponent::getDistance(Point& a, Point& b)
{
	int x2 = a.x;
	int x1 = b.x;
	int y2 = a.y;
	int y1 = b.y;
	int dist = (int)sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return dist;
}

int LiftComponent::getXDirection(Point & a, Point & b)
{
	return a.x - b.x;
}

int LiftComponent::getYDirection(Point & a, Point & b)
{
	return a.y - b.y;
}

bool LiftComponent::isNearby(int dist, int radius)
{
	return std::abs(dist) <= radius;
}
