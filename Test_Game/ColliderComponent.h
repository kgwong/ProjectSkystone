#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"
#include "GameObject.h"

class ColliderComponent : public Component
{
private:
	struct BoxCollider
	{
		int x;
		int y;
		int w;
		int h;
	};

public:
	ColliderComponent();
	virtual ~ColliderComponent();

	void setCollider(BoxCollider newCollider); 

	virtual void update(GameObject& owner);

	bool checkCollision(GameObject& other);
	bool checkCollision(ColliderComponent* other);

private:
	BoxCollider collider;
};

#endif //COLLIDERCOMPONENT_H
