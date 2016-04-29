#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "Components/Render/RenderComponent.h"

class SpriteSheet;

class HealthBar : public RenderComponent 
{
public:
	HealthBar(GameObject& owner);
	virtual ~HealthBar();

	virtual void render(GameWindow& window, float percBehind);
	
	void enable();
	void disable();

private:
	SpriteSheet* barSheet_;
	SpriteSheet* outlineSheet_;
	bool enabled_;

	float getHpPercent();
	void renderBar(GameWindow& window, float percBehind);
	void renderOutline(GameWindow& window, float percBehind);
};

#endif // HEALTH_BAR_H

