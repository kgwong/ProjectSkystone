#ifndef TEMP_GAME_OVER_SCREEN_H
#define TEMP_GAME_OVER_SCREEN_H

class TextureLoader;
class TextureSheet;

class TempGameOverScreen
{
public:
	TempGameOverScreen(TextureLoader* textureLoader_);
	~TempGameOverScreen();
	void render();
private:
	TextureSheet* textureSheet_;
};


#endif //TEMP_GAME_OVER_SCREEN_H