#include "PlayerHookBuilder.h"

#include "TextureLoader.h"
#include "SpriteRenderer.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"


PlayerHookBuilder::PlayerHookBuilder(TextureLoader* textureLoader)
	:textureLoader_(textureLoader)
{
}


PlayerHookBuilder::~PlayerHookBuilder()
{
}

//returns a shared_ptr of the gameobject hook.
std::shared_ptr<GameObject> PlayerHookBuilder::build(ComponentSystem& componentSystem, const std::string& name)
{
	//someHook is the shared ptr gameobject.
	auto someHook = std::make_shared<GameObject>();
	//hookTobuild is the actual gameobject we add components to.
	auto& hookToBuild = *someHook;

	TextureSheet* sheet = textureLoader_->getTextureSheet("Assets/Animations/playerHook.png");
	std::cout << "FRAMES: " << sheet->getNumFrames() << std::endl;
	//system("PAUSE");

	//setting components to add ~ are smart pointers


	//crash occurs at SPRITERENDERER HERE!!! ~~~~~~~~~~~~~~~~~~~~~~
	std::shared_ptr<SpriteRenderer> spriteRenderer_ptr = componentSystem.getNew<SpriteRenderer>(hookToBuild, sheet);
	std::shared_ptr<PhysicsComponent> physics_ptr = componentSystem.getNew<PhysicsComponent>(hookToBuild);
	///------------------------------------------------------------
	hookToBuild.addComponent(spriteRenderer_ptr);
	//error here too
	std::shared_ptr<ColliderComponent> collider_ptr = componentSystem.getNew<ColliderComponent>(hookToBuild);

	//adding gameobject type and components
	hookToBuild.setType(GameObject::Type::PLAYER_HOOK);

	hookToBuild.addComponent(physics_ptr);
	hookToBuild.addComponent(collider_ptr);

	return someHook;
}
