#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"

class ColliderComponent : public Component
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
	ColliderComponent();
	ColliderComponent(GameObject& owner);
	ColliderComponent(int offsetX, int offsetY, int width, int height);
	ColliderComponent(BoxCollider collider);
	virtual ~ColliderComponent();

	virtual void start(GameObject& owner, Level& level) {};
	virtual void update(GameObject& owner, Level& level);

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
