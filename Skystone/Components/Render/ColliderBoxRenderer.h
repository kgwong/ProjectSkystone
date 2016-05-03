#ifndef COLLIDER_BOX_RENDERER_H
#define COLLIDER_BOX_RENDERER_H

#include "RenderComponent.h"
#include "Components/Collider/ColliderComponent.h"

#include "Resources/SpriteSheet.h"

class ColliderBoxRenderer : public RenderComponent
{
public:
	ColliderBoxRenderer(GameObject& owner);
	virtual ~ColliderBoxRenderer();

	virtual void start(Scene& scene);
	virtual void render(GameWindow& window, float percBehind);

	virtual int getWidth();
	virtual int getHeight();

	virtual int getRenderLayer();

private:
	ColliderComponent* collider_;
	SpriteSheet* spriteSheet_;
};

#endif //COLLIDER_BOX_RENDERER_H
