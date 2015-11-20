#include "Background.h"
#include "Path.h"

Background::Background(TextureLoader* textureLoader)
	: spriteRenderer_(new SpriteRenderer(textureLoader->getTextureSheet("Assets/backgroundTest.png")))
{
}


Background::~Background()
{
}

void Background::render(Level& level)
{
	spriteRenderer_->update(*this, level);
}