#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Components/NonUpdatingComponent.h"

class ColliderComponent : public NonUpdatingComponent
{
public:
	struct BoxCollider
	{
		int x;
		int y;
		int width;
		int height;
	};

public:
	ColliderComponent(GameObject& owner);
	ColliderComponent(GameObject& owner, int offsetX, int offsetY, int width, int height);
	ColliderComponent(GameObject& owner, BoxCollider collider);
	virtual ~ColliderComponent();

	virtual void start(Level& level) {};
	virtual void update();

	void setCollider(BoxCollider newCollider); 

	int getHeight();
	int getWidth();

	int getTop();
	int getBottom();
	int getLeft();
	int getRight();

	int getOffsetX();
	int getOffsetY();

	bool checkCollision(GameObject& other);
	bool checkCollision(ColliderComponent* other);

private:
	BoxCollider _collider;
	int _offsetX, _offsetY;
};

#endif //COLLIDERCOMPONENT_H
