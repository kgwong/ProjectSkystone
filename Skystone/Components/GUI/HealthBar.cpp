#include "HealthBar.h"
#include "Components/Common/HealthComponent.h"
#include "Resources/Resources.h"


static const std::string healthBarPath = "Images/healthBar.png";
static const Point renderLoc{10, 10};

HealthBar::HealthBar(GameObject& owner)
	: RenderComponent(owner), spriteSheet_(Resources::getSpriteSheet(healthBarPath)), enabled_(true)
{
}


HealthBar::~HealthBar()
{
}

void HealthBar::render(GameWindow& window, float percBehind)
{
	if(enabled_ && spriteSheet_ != nullptr)
	{
		float hpPerc = getHpPercent();
		SDL_Rect* max = spriteSheet_->getFrameRect(0);
		SDL_Rect src = {0, 0, max->w*hpPerc, max->h};
		SDL_Rect dest = {renderLoc.x, renderLoc.y, src.w, src.h};
		window.renderOnCamera(spriteSheet_->getTexture(), &src, &dest);
	}
}

void HealthBar::setEnabled(bool enable)
{
	enabled_ = enable;
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