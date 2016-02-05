#include "Resources.h"

TextureLoader Resources::textureLoader;
AudioPlayer Resources::audioPlayer;
std::unordered_map<std::string, SpriteSheet> Resources::spriteSheets_;

SpriteSheet* Resources::getSpriteSheet(const std::string & relPath)
{
	std::string fullpath = Path::getFullPath(relPath);

	if (spriteSheets_.count(relPath) == 0)
	{
		spriteSheets_.insert({ relPath, SpriteSheet(textureLoader.loadTexture(fullpath), fullpath) });
	}
	return &spriteSheets_.at(relPath);
}
