#include "ColliderComponent.h"

#include "Components/Render/RenderComponent.h"
#include "Components/Render/SpriteRenderer.h"

#include "Application/Log.h"

ColliderComponent::ColliderComponent(GameObject& owner)
	: NonUpdatingComponent(owner),
	collider_{0, 0, 0 ,0}, offsetX_(0), offsetY_(0)
{
	//by default, use the size of the sprite
	RenderComponent* render = owner.getComponent<SpriteRenderer>();
	if (render != nullptr)
		collider_ = { 0, 0, (float)render->getWidth(), (float)render->getHeight() };
}

ColliderComponent::ColliderComponent(GameObject& owner, float offsetX, float offsetY, float width, float height)
	: NonUpdatingComponent(owner),
	collider_{0, 0, width, height}, offsetX_(offsetX), offsetY_(offsetY)
{

}

ColliderComponent::ColliderComponent(GameObject& owner, BoxCollider collider)
	: NonUpdatingComponent(owner), offsetX_(0), offsetY_(0),
	collider_(collider)
{
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::update()
{	
	collider_.x = owner_.getPosX() + offsetX_;
	collider_.y = owner_.getPosY() + offsetY_;
}


void ColliderComponent::setCollider(BoxCollider newCollider)
{
	collider_ = newCollider;
}

ColliderComponent::BoxCollider ColliderComponent::getCollider()
{
	return collider_;
}

void ColliderComponent::setHeight(float height)
{
	collider_.height = height;
}

void ColliderComponent::setWidth(float width)
{
	collider_.width = width;
}

float ColliderComponent::getHeight()
{
	return collider_.height;
}

float ColliderComponent::getWidth()
{
	return collider_.width;
}

float ColliderComponent::getTop()
{
	this->update();
	return collider_.y;
}

float ColliderComponent::getBottom()
{
	this->update();
	return collider_.y + collider_.height;
}

float ColliderComponent::getLeft()
{
	this->update();
	return collider_.x;
}

float ColliderComponent::getRight()
{
	this->update();
	return collider_.x + collider_.width;
}

float ColliderComponent::getOffsetX()
{
	return offsetX_;
}

float ColliderComponent::getOffsetY()
{
	return offsetY_;
}

void ColliderComponent::setOffsetX(float offsetX)
{
	offsetX_ = offsetX;
}

void ColliderComponent::setOffsetY(float offsetY)
{
	offsetY_ = offsetY;
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