#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Components/NonUpdatingComponent.h"

class ColliderComponent : public NonUpdatingComponent
{
public:
	struct BoxCollider
	{
		float x;
		float y;
		float width;
		float height;
	};

public:
	ColliderComponent(GameObject& owner);
	ColliderComponent(GameObject& owner, float offsetX, float offsetY, float width, float height);
	ColliderComponent(GameObject& owner, BoxCollider collider);
	virtual ~ColliderComponent();

	virtual void start(Scene& scene) {};
	void update();

	void setCollider(BoxCollider newCollider); 

	float getHeight();
	float getWidth();

	float getTop();
	float getBottom();
	float getLeft();
	float getRight();

	float getOffsetX();
	float getOffsetY();

	bool checkCollision(GameObject& other);
	bool checkCollision(ColliderComponent* other);

private:
	BoxCollider _collider;
	float _offsetX, _offsetY;
};

#endif //COLLIDERCOMPONENT_H
