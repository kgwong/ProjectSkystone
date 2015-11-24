#include "Background.h"
#include "Path.h"

Background::Background(std::shared_ptr<SpriteRenderer> spriteRenderer)
	: spriteRenderer_(spriteRenderer)
{
}


Background::~Background()
{
}

void Background::render(Level& level)
{
	spriteRenderer_->update(*this, level);
}