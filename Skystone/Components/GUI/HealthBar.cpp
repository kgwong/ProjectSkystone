#include "HealthBar.h"


HealthBar::HealthBar(GameObject& owner, GameObject& player)
	: RenderComponent(owner), player_(player)
{
}


HealthBar::~HealthBar()
{
}

void HealthBar::render(GameWindow& window, float percBehind)
{
	// render based on % player health
	
}
