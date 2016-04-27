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
	
	void setEnabled(bool enable);

private:
	SpriteSheet* spriteSheet_;
	bool enabled_;

	float getHpPercent();
};

#endif // HEALTH_BAR_H

