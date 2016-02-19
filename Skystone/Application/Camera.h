#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject/GameObject.h"

//only render what is visible by camera!
//create a collider for camera and only render objects colliding with camera
//assuming that rendering costs more than collision detection...

class Camera : public GameObject
{
public:
	Camera(float width, float height);
	virtual ~Camera();

	void setLevelBounds(float maxX, float maxY);
	void followObject(GameObject& object, float percBehind);
	void stayInLevelBounds();

private:
	float width_, height_;
	float maxX_, maxY_;
};

#endif //CAMERA_H