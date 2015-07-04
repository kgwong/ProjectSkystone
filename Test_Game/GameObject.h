#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point.h"

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

protected:
	Point position;
	int width;
	int height;
};

#endif //GAMEOBJECT_H