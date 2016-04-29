#include "HealthBar.h"
#include "Components/Common/HealthComponent.h"
#include "Resources/Resources.h"


static const std::string healthBarOutlinePath = "Images/health_bar_outline.png";
static const std::string healthBarPath = "Images/health_bar_fill.png";

static const Point outlineLoc{10, 10};
static const Point healthBarLoc{10, 10};

HealthBar::HealthBar(GameObject& owner)
	: RenderComponent(owner),
	outlineSheet_(Resources::getSpriteSheet(healthBarOutlinePath)),
	barSheet_(Resources::getSpriteSheet(healthBarPath)), 
	enabled_(true)
{
}


HealthBar::~HealthBar()
{
}

void HealthBar::render(GameWindow& window, float percBehind)
{
	if(enabled_ && outlineSheet_ != nullptr && barSheet_ != nullptr)
	{
		renderBar(window, percBehind);
		renderOutline(window, percBehind);
	}
}

void HealthBar::enable()
{
	enabled_ = true;
}

void HealthBar::disable()
{
	enabled_ = false;
}

float HealthBar::getHpPercent()
{
	auto healthComponent = owner_.getComponent<HealthComponent>();
	if (healthComponent != nullptr)
	{
		return static_cast<float>(healthComponent->getHealth()) / healthComponent->getMaxHealth();
	}
	else
	{
		return 1.0f;
	}
}

void HealthBar::renderBar(GameWindow& window, float percBehind)
{
	float hpPerc = getHpPercent();
	SDL_Rect* max = barSheet_->getFrameRect(0);
	SDL_Rect src = { 0, 0, max->w*hpPerc, max->h };
	SDL_Rect dest = {healthBarLoc.x, healthBarLoc.y, src.w, src.h };
	window.renderOnCamera(barSheet_->getTexture(), &src, &dest);
}

void HealthBar::renderOutline(GameWindow& window, float percBehind)
{
	SDL_Rect src = { 0, 0, outlineSheet_->getFrameRect(0)->w, outlineSheet_->getFrameRect(0)->h};
	SDL_Rect dest = { outlineLoc.x, outlineLoc.y, src.w, src.h };
	window.renderOnCamera(outlineSheet_->getTexture(), &src, &dest);
}

