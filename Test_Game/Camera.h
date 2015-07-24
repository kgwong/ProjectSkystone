#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

//only render what is visible by camera!
//create a collider for camera and only render objects colliding with camera
//assuming that rendering costs more than collision detection...

class Camera : public GameObject
{
public:
	Camera();
	virtual ~Camera();
	
	void setLevelBounds(int maximumX, int maximumY);
	void followObject(const GameObject& object);
	void stayInLevelBounds();

private:
	int maximumX;
	int maximumY;
};

#endif //CAMERA_H