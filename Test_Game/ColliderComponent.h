#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"
#include "GameObject.h"

class ColliderComponent : public Component
{
public:
	ColliderComponent();
	virtual ~ColliderComponent();

	void setCollider(int x, int y, int w, int h); 

	virtual void update(GameObject& owner);

	bool checkCollision(ColliderComponent& other); //maybe take a ColliderComponent* ?


private:
	struct BoxCollider
	{
		int x;
		int y;
		int w;
		int h;
	};

private:
	BoxCollider collider;
};

#endif //COLLIDERCOMPONENT_H
