#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <unordered_map>
#include <memory>

#include "GameTypes/Point.h"

class Level;
class Component;
class ComponentEvent;
class CollisionEvent;
class ComponentSystem;

class GameObject
{
public:
	enum class Type
	{
		PLAYER,
		PLAYER_PROJECTILE,
		ENEMY,
		ENEMY_PROJECTILE,
		TILE,
		DROP,
		BACKGROUND,
		UNKNOWN,
		PLAYER_HOOK
	};
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

	void disownComponents();

	void registerComponents(ComponentSystem& system);

	bool alive();
	void kill();

	virtual void setType(Type type);
	virtual Type getType() const;

	virtual void startComponents(Level& level);

	void broadcastEvent(const ComponentEvent& e);
	//FIX THIS LATER!!
	//http://stackoverflow.com/questions/6897662/matching-an-overloaded-function-to-its-polymorphic-argument
	void broadcastEvent(const CollisionEvent& e);

protected:
	Point position_;
	std::unordered_map<const std::type_info*, std::shared_ptr<Component>> components_;

	bool alive_;
	Type type_;
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

