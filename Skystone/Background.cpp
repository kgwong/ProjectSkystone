#include "Background.h"
#include "Path.h"

Background::Background(SpriteRenderer* spriteRenderer)
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