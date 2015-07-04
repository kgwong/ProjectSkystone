#include "Camera.h"


Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setLevelBounds(int maxX, int maxY)
{
	maximumX = maxX;
	maximumY = maxY;
}

void Camera::followObject(const GameObject& object)
{
	setCenterPos(object);
	stayInLevelBounds();
}

void Camera::stayInLevelBounds()
{
	if (position.x < 0)
		position.x = 0;
	if (position.y < 0)
		position.y = 0;
	if (position.x > maximumX - width)
		position.x = maximumX - width;
	if (position.y > maximumY - height)
		position.y = maximumY - height;
}
