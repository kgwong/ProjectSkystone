#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <iostream>

#include "Point.h"
#include "Component.h"
#include "EntityType.h"

#include "ComponentType.h"

class Level;

class GameObject
{
public:
	GameObject();
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

	int getWidth() const;
	int getHeight() const;

	void setCenterPos(const GameObject& other);
	void setCenterPos(Point newCenterPos);
	void setCenterPosX(int x);
	void setCenterPosY(int y);

	Point getCenterPos() const;
	int getCenterPosX() const;
	int getCenterPosY() const;

	//throw stuff
	virtual Component* getComponent(ComponentType type);
	virtual std::string getName() const;
	virtual EntityType getType() const;
	virtual void onCollision(GameObject& other) {};
	virtual void onDeath(Level& level) {};

protected:
	Point position;
	int width;
	int height;
};

#endif //GAME_OBJECT_H