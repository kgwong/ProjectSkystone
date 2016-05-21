#include "PlayerRopeSegmentBuilder.h"

#include "Components/Render/SpriteRenderer.h"

PlayerRopeSegmentBuilder::PlayerRopeSegmentBuilder()
{
}


PlayerRopeSegmentBuilder::~PlayerRopeSegmentBuilder()
{
}

std::shared_ptr<GameObject> PlayerRopeSegmentBuilder::build(ComponentSystem& componentSystem, const std::string& name)
{
	auto ropeSeg = std::make_shared<GameObject>();
	auto& ropeSegment = *ropeSeg;

	ropeSegment.setType(GameObject::Type::ROPE_SEGMENT);
	std::shared_ptr<SpriteRenderer> spriteRenderer_ptr = componentSystem.getNew<SpriteRenderer>(ropeSegment, "Assets/Animations/4x2String.png");
	ropeSegment.addComponent(spriteRenderer_ptr);


	return ropeSeg;
}
