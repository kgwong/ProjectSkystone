#ifndef COLLISION_INFO_H
#define COLLISION_INFO_H

class Level;
class GameObject;
class ColliderComponent;

struct CollisionInfo
{
	Level& level;
	GameObject& other;
	ColliderComponent& otherCollider;
};


#endif //COLLISION_INFO_H