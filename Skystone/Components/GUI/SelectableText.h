#ifndef SELECTABLE_TEXT_H
#define SELECTABLE_TEXT_H

#include "Components/Render/TextRenderer.h"
#include "Scene/Scene.h"

class SelectableText : public TextRenderer
{
public:
	SelectableText(GameObject& owner);
	~SelectableText();

	bool isSelected();
	void setSelected(bool selected);
	void render(GameWindow& window, float percBehind);
	
	void setSceneOnSelection(SceneID next);
	SceneID getSceneOnSelection();

private:
	bool selected_;
	SceneID sceneOnSelection_;
};

#endif // SELECTABLE_TEXT_H
