#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "Components/Render/RenderComponent.h"

class HealthBar : public RenderComponent 
{
public:
	HealthBar(GameObject& owner, GameObject& player);
	virtual ~HealthBar();

	virtual void render(GameWindow& window, float percBehind);
private:
	GameObject& player_;
};

#endif // HEALTH_BAR_H

