#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <unordered_map>
#include <memory>

#include "GameTypes/Point.h"

class Scene;
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
		PLAYER_HOOK,
		GUI,
		ROPE_SEGMENT
	};
public:
	GameObject();
	GameObject(Point position);
	GameObject(int x, int y);
	virtual ~GameObject();
	
	void setPos(float x, float y);
	void setPos(Point newPosition);
	void setPosX(float x);
	void setPosY(float y);

	Point getPos() const;
	float getPosX() const;
	float getPosY() const;

	void addComponent(std::shared_ptr<Component> component);
	
	template <typename ComponentT>
	ComponentT* getComponent();

	void disownComponents();

	void registerComponents(ComponentSystem& system);

	bool alive();
	void kill();
	void setAlive(bool alive);

	virtual void setType(Type type);
	virtual Type getType() const;

	virtual void startComponents(Scene& scene);

	void broadcastEvent(const ComponentEvent& e);

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

