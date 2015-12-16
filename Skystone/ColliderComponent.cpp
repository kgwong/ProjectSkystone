#include "ColliderComponent.h"

#include "RenderComponent.h"
#include "SpriteRenderer.h"
#include "AnimationRenderer.h"

ColliderComponent::ColliderComponent(GameObject& owner)
	: NonUpdatingComponent(owner),
	_collider{0, 0, 0 ,0}, _offsetX(0), _offsetY(0)
{	
	//this is a hack, have only one type of Renderer.	
	RenderComponent* render = owner.getComponent<SpriteRenderer>();
	if (render == nullptr)
		render = owner.getComponent<AnimationRenderer>();
	_collider = { 0, 0, render->getWidth(), render->getHeight() };
}

ColliderComponent::ColliderComponent(GameObject& owner, int offsetX, int offsetY, int width, int height)
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
	this->update();
	return _collider.y;
}

int ColliderComponent::getBottom()
{
	this->update();
	return _collider.y + _collider.height;
}

int ColliderComponent::getLeft()
{
	this->update();
	return _collider.x;
}

int ColliderComponent::getRight()
{
	this->update();
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
	
	//Updating collider's position is only before checking collision
	this->update();
	other->update();

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