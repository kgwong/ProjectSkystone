#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <iostream>
#include <unordered_map>

#include "Point.h"
#include "Component.h"
#include "EntityType.h"

#include "CollisionInfo.h"

class Level;

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

	void setWidth(int w);
	void setHeight(int h);

	Point getPos() const;
	int getPosX() const;
	int getPosY() const;

	int getWidth() const; //remove later?
	int getHeight() const;

	void setCenterPos(const GameObject& other);
	void setCenterPos(Point newCenterPos);
	void setCenterPosX(int x);
	void setCenterPosY(int y);

	Point getCenterPos() const;
	int getCenterPosX() const;
	int getCenterPosY() const;

	void addComponent(Component* component);
	
	template <typename ComponentT>
	ComponentT* getComponent();

	virtual std::string getName() const;
	virtual EntityType getType() const;
	virtual void onCollision(CollisionInfo& collision) {};
	virtual void onDeath(Level& level) {};

	virtual void callStartOnComponents(Level& level);

protected:
	Point position_;
	int width_;
	int height_;

	std::unordered_map<const std::type_info*, Component*> components_;
};

//http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components

template<typename ComponentT>
ComponentT* GameObject::getComponent()
{
	if (components_.count(&typeid(ComponentT)))
		return static_cast<ComponentT*>(components_[&typeid(ComponentT)]);
	else
		return nullptr;
}


#endif //GAME_OBJECT_H

