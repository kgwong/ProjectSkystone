#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <unordered_map>
#include <memory>

#include "Point.h"
#include "EntityType.h"

#include "CollisionInfo.h"

class Level;
class Component;

class GameObject
{
public:
	GameObject();
	GameObject(Point position);
	GameObject(int x, int y);
	virtual ~GameObject();
	
	void setPos(int x, int y);
	void setPos(Point newPosition);
	void setPosX(int x);
	void setPosY(int y);

	Point getPos() const;
	int getPosX() const;
	int getPosY() const;

	void addComponent(std::shared_ptr<Component> component);
	
	template <typename ComponentT>
	ComponentT* getComponent();

	void clearComponents();

	bool alive();
	void kill();

	virtual std::string getName() const; //???
	virtual EntityType getType() const; //TypeComponents
	virtual void onCollision(CollisionInfo& collision) {}; //ColliderComponent
	virtual void onDeath(Level& level) {}; //DeathComponent

	virtual void callStartOnComponents(Level& level);


protected:
	Point position_;
	std::unordered_map<const std::type_info*, std::shared_ptr<Component>> components_;

	bool alive_;
};

//http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components

template<typename ComponentT>
ComponentT* GameObject::getComponent()
{
	if (components_.count(&typeid(ComponentT)))
		return static_cast<ComponentT*>(components_[&typeid(ComponentT)].get());
	else
		return nullptr;
}


#endif //GAME_OBJECT_H

