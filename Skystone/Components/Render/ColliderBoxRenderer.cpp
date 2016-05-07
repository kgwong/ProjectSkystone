#include "ColliderBoxRenderer.h"

#include "Resources/Resources.h"

ColliderBoxRenderer::ColliderBoxRenderer(GameObject& owner)
	:RenderComponent(owner),
	spriteSheet_(Resources::getSpriteSheet("Assets/collider.png"))
{
}


ColliderBoxRenderer::~ColliderBoxRenderer()
{
}

void ColliderBoxRenderer::start(Scene& scene)
{
	collider_ = owner_.getComponent<ColliderComponent>();
}

void ColliderBoxRenderer::render(GameWindow& window, float percBehind)
{
	SDL_Rect drawDest = { owner_.getPosX() + collider_->getOffsetX(),
							owner_.getPosY() + collider_->getOffsetY(),
							collider_->getWidth(),
							collider_->getHeight() };

	window.render(spriteSheet_->getTexture(), spriteSheet_->getFrameRect(0), &drawDest);
}

int ColliderBoxRenderer::getWidth()
{
	return collider_->getWidth();
}

int ColliderBoxRenderer::getHeight()
{
	return collider_->getHeight();
}

int ColliderBoxRenderer::getRenderLayer()
{
	return 9; //magic number
}
