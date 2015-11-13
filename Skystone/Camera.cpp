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
	position_.x = std::max(0, position_.x);
	position_.x = std::min(position_.x, maxX_ - width_);

	position_.y = std::max(0, position_.y);
	position_.y = std::min(position_.y, maxY_ - height_);
}
