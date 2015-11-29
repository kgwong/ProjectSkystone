#include "TempGameOverScreen.h"
#include "TextureLoader.h"


TempGameOverScreen::TempGameOverScreen(TextureLoader* textureLoader_)
	: textureSheet_{textureLoader_->getTextureSheet("Assets/GameOverScreen.png")}
{
}


TempGameOverScreen::~TempGameOverScreen()
{
}

void TempGameOverScreen::render()
{
	SDL_RenderClear(textureSheet_->getWindow()->getRenderer());
	MySDL_RenderCopy(textureSheet_->getWindow()->getRenderer(), textureSheet_->getTexture(), 0, 0);
	SDL_RenderPresent(textureSheet_->getWindow()->getRenderer());
}