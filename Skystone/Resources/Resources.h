#ifndef RESOURCES_H
#define RESOURCES_H

#include "AudioPlayer.h"
#include "TextureLoader.h"
#include "SpriteSheet.h"
#include "Application/Path.h"

#include <string>
#include <unordered_map>

class Resources
{
public:
	static TextureLoader textureLoader;
	static AudioPlayer audioPlayer;

public:
	static SpriteSheet* getSpriteSheet(const std::string& basepath);


private:
	static std::unordered_map<std::string, SpriteSheet> spriteSheets_;


};

#endif //RESOURCES_H