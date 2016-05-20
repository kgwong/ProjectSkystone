#ifndef PLAYER_ROPE_SEGMENT_BUILDER_H
#define PLAYER_ROPE_SEGMENT_BUILDER_H

#include <string>
#include <memory>

class GameObject;
class ComponentSystem;

class PlayerRopeSegmentBuilder
{
public:
	PlayerRopeSegmentBuilder();
	~PlayerRopeSegmentBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& name);
};

#endif

