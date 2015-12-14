#include "ColliderComponent.h"

#include "RenderComponent.h"
#include "SpriteRenderer.h"
#include "AnimationRenderer.h"

ColliderComponent::ColliderComponent()
	:_collider{0, 0, 0 ,0}, _offsetX(0), _offsetY(0)
{
}

ColliderComponent::ColliderComponent(GameObject & owner)
	:  _offsetX(0), _offsetY(0)
{
	//this is a hack, have only one type of Renderer.	
	RenderComponent* render = owner.getComponent<SpriteRenderer>();
	if (render == nullptr)
		render = owner.getComponent<AnimationRenderer>();
	_collider = { 0, 0, render->getWidth(), render->getHeight() };
}

ColliderComponent::ColliderComponent(int offsetX, int offsetY, int width, int height)
	: _collider{0, 0, width, height}, _offsetX(offsetX), _offsetY(offsetY)
{

}

ColliderComponent::ColliderComponent(BoxCollider collider)
	:_offsetX(0), _offsetY(0)
{
	_collider = collider;
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::update(GameObject& owner, Level& level)
{
	_collider.x = owner.getPosX() + _offsetX;
	_collider.y = owner.getPosY() + _offsetY;
	//setCollider(BoxCollider{owner.getPosX() + _offsetX, owner.getPosY() + _offsetY,
	//						owner.getWidth(), owner.getHeight()});
}

void ColliderComponent::setCollider(BoxCollider newCollider)
{
	_collider = newCollider;
}

int ColliderComponent::getHeight()
{
	return _collider.height;
}

int ColliderComponent::getWidth()
{
	return _collider.width;
}

int ColliderComponent::getTop()
{
	return _collider.y;
}

int ColliderComponent::getBottom()
{
	return _collider.y + _collider.height;
}

int ColliderComponent::getLeft()
{
	return _collider.x;
}

int ColliderComponent::getRight()
{
	return _collider.x + _collider.width;
}

int ColliderComponent::getOffsetX()
{
	return _offsetX;
}

int ColliderComponent::getOffsetY()
{
	return _offsetY;
}

bool ColliderComponent::checkCollision(GameObject& other)
{
	return checkCollision(other.getComponent<ColliderComponent>());
}

bool ColliderComponent::checkCollision(ColliderComponent* other)
{
	if (other == this) return false; //do not detect collision with itself
	if (other == nullptr) return false; //no collision detected with nonexistant collider

	int topOther = other->getTop();
	int topSelf = getTop(); 

	int bottomOther = other->getBottom();
	int bottomSelf = getBottom();

	int leftOther = other->getLeft();
	int leftSelf = getLeft(); 

	int rightOther = other->getRight();
	int rightSelf = getRight(); 

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