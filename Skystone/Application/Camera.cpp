#include "Camera.h"

#include <algorithm>
#include <limits>

#include "Components/Render/SpriteRenderer.h"

Camera::Camera(int width, int height)
	:width_(width), height_(height),
	maxX_(std::numeric_limits<int>::max()),
	maxY_(std::numeric_limits<int>::max())
{
}

Camera::~Camera()
{
}

void Camera::setLevelBounds(int maxX, int maxY)
{
	maxX_ = maxX;
	maxY_ = maxY;
}

void Camera::followObject(GameObject& object, float percBehind)
{
	auto t = object.getComponent<SpriteRenderer>();

	position_ = t->getRenderPosition(percBehind);
	position_.x -= width_ / 2;
	position_.y -= height_ / 2;
	stayInLevelBounds();
}

void Camera::stayInLevelBounds()
{
	position_.x = std::max(0.0f, position_.x);
	position_.x = std::min(position_.x, (float) maxX_ - width_);

	position_.y = std::max(0.0f, position_.y);
	position_.y = std::min(position_.y, (float) maxY_ - height_);
}
