#include "ColliderComponent.h"

#include "Components/Render/RenderComponent.h"
#include "Components/Render/SpriteRenderer.h"

ColliderComponent::ColliderComponent(GameObject& owner)
	: NonUpdatingComponent(owner),
	_collider{0, 0, 0 ,0}, _offsetX(0), _offsetY(0)
{
	//by default, use the size of the sprite
	RenderComponent* render = owner.getComponent<SpriteRenderer>();
	if (render != nullptr)
		_collider = { 0, 0, (float)render->getWidth(), (float)render->getHeight() };
}

ColliderComponent::ColliderComponent(GameObject& owner, float offsetX, float offsetY, float width, float height)
	: NonUpdatingComponent(owner),
	_collider{0, 0, width, height}, _offsetX(offsetX), _offsetY(offsetY)
{

}

ColliderComponent::ColliderComponent(GameObject& owner, BoxCollider collider)
	: NonUpdatingComponent(owner), _offsetX(0), _offsetY(0)
{
	_collider = collider;
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::update()
{
	_collider.x = owner_.getPosX() + _offsetX;
	_collider.y = owner_.getPosY() + _offsetY;
}


void ColliderComponent::setCollider(BoxCollider newCollider)
{
	_collider = newCollider;
}



float ColliderComponent::getHeight()
{
	return _collider.height;
}

float ColliderComponent::getWidth()
{
	return _collider.width;
}

float ColliderComponent::getTop()
{
	this->update();
	return _collider.y;
}

float ColliderComponent::getBottom()
{
	this->update();
	return _collider.y + _collider.height;
}

float ColliderComponent::getLeft()
{
	this->update();
	return _collider.x;
}

float ColliderComponent::getRight()
{
	this->update();
	return _collider.x + _collider.width;
}

float ColliderComponent::getOffsetX()
{
	return _offsetX;
}

float ColliderComponent::getOffsetY()
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
	
	//Updating collider's position is only before checking collision
	this->update();
	other->update();

	float topOther = other->getTop();
	float topSelf = getTop(); 

	float bottomOther = other->getBottom();
	float bottomSelf = getBottom();

	float leftOther = other->getLeft();
	float leftSelf = getLeft(); 

	float rightOther = other->getRight();
	float rightSelf = getRight(); 

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