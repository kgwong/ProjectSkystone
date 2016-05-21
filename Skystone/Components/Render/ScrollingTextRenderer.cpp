#include "ScrollingTextRenderer.h"
#include "Application/Path.h"
#include "Game/GameTime.h"
#include <fstream>

const static float UPDATE_INTERVAL = .2f;

namespace
{
std::string readScript(const std::string relPath)
{
	std::string result = "";
	std::ifstream ifs(Path::getFullPath(relPath));
	
	std::string dummy;
	
	while (std::getline(ifs, dummy))
		result += dummy;
	return result;
}
}



ScrollingTextRenderer::ScrollingTextRenderer(GameObject& owner, const std::string& relScriptPath)
	: TextRenderer(owner), timeSinceLastUpdate_(0)
{
	TextRenderer::setText(readScript(relScriptPath));
	setRenderMode(TextRenderer::RenderMode::RENDER_FROM_TOP_LEFT);
}


ScrollingTextRenderer::~ScrollingTextRenderer()
{
}

void ScrollingTextRenderer::render(GameWindow& window, float percBehind)
{
	if ((timeSinceLastUpdate_ += Time::getElapsedUpdateTimeSeconds()) >= UPDATE_INTERVAL)
	{
		owner_.setPosY(owner_.getPosY() - 1);
	}
		
	TextRenderer::render(window, percBehind);
}