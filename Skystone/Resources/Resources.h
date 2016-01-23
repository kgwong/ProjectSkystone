#ifndef RESOURCES_H
#define RESOURCES_H

#include "TextureLoader.h"
#include "SpriteSheet.h"
#include "Path.h"

#include <string>
#include <unordered_map>

class Resources
{
public:
	static TextureLoader textureLoader;

public:
	static SpriteSheet* getSpriteSheet(const std::string& basepath);


private:
	static std::unordered_map<std::string, SpriteSheet> spriteSheets_;


};

#endif //RESOURCES_H