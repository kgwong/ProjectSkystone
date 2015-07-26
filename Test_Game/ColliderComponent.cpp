#include "ColliderComponent.h"


ColliderComponent::ColliderComponent()
{
	collider.x = 0;
	collider.y = 0;
	collider.w = 0;
	collider.h = 0;
}


ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::setCollider(int x, int y, int w, int h)
{
	collider.x = x;
	collider.y = y;
	collider.w = w;
	collider.h = h;
}

void ColliderComponent::update(GameObject& owner)
{
	//default to owner's attributes
	setCollider(owner.getPosX(), owner.getPosY(), owner.getWidth(), owner.getHeight());
}

bool ColliderComponent::checkCollision(GameObject& other)
{
	return checkCollision( static_cast<ColliderComponent*> (other.getComponent(COLLIDER) ) );
}

bool ColliderComponent::checkCollision(ColliderComponent* other)
{
	if (other == this) return false; //do not detect collision with itself
	if (other == nullptr) return false; //no collision detected with nonexistant collider

	int topOther = other->collider.y;
	int topSelf = collider.y; 

	int bottomOther = other->collider.y + other->collider.h;
	int bottomSelf = collider.y + collider.h; 

	int leftOther = other->collider.x;
	int leftSelf = collider.x; 

	int rightOther = other->collider.x + other->collider.w;
	int rightSelf = collider.x + collider.w; 

	if (topSelf >= bottomOther)
		return false;
	if (bottomSelf <= topOther)
		return false;
	if (leftSelf >= rightOther)
		return false;
	if (rightSelf <= leftOther)
		return false;

	return true;
}