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
	ColliderComponent(GameObject& owner);
	ColliderComponent(GameObject& owner, int offsetX, int offsetY, int width, int height);
	ColliderComponent(GameObject& owner, BoxCollider collider);
	virtual ~ColliderComponent();

	virtual void start(Level& level) {};
	virtual void update(Level& level);

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
