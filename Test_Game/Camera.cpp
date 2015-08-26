#include "Camera.h"

#include <algorithm>
#include <limits>

Camera::Camera(int width, int height)
	:maxX_(std::numeric_limits<int>::max()),
	maxY_(std::numeric_limits<int>::max())
{
	setWidth(width);
	setHeight(height);
}

Camera::~Camera()
{
}

void Camera::setLevelBounds(int maxX, int maxY)
{
	maxX_ = maxX;
	maxY_ = maxY;
}

void Camera::followObject(const GameObject& object)
{
	setCenterPos(object);
	stayInLevelBounds();
}

void Camera::stayInLevelBounds()
{
	position.x = std::max(0, position.x);
	position.x = std::min(position.x, maxX_ - width_);

	position.y = std::max(0, position.y);
	position.y = std::min(position.y, maxY_ - height_);
}
