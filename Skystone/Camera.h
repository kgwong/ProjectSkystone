#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

//only render what is visible by camera!
//create a collider for camera and only render objects colliding with camera
//assuming that rendering costs more than collision detection...

class Camera : public GameObject
{
public:
	Camera(int width, int height);
	virtual ~Camera();

	void setLevelBounds(int maxX, int maxY);
	void followObject(const GameObject& object);
	void stayInLevelBounds();

private:
	int width_, height_;
	int maxX_, maxY_;
};

#endif //CAMERA_H