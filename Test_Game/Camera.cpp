#include "Camera.h"

#include <algorithm>

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
	position.x = std::max(0, position.x);
	position.x = std::min(position.x, maximumX - width);

	position.y = std::max(0, position.y);
	position.y = std::min(position.y, maximumY - height);
}
