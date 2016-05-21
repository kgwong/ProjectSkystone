#include "ScrollingTextRenderer.h"
#include "Application/Path.h"
#include <fstream>

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
	: TextRenderer(owner)
{
	TextRenderer::setText(readScript(relScriptPath));
	setRenderMode(TextRenderer::RenderMode::RENDER_FROM_TOP_LEFT);
}


ScrollingTextRenderer::~ScrollingTextRenderer()
{
}

void ScrollingTextRenderer::render(GameWindow& window, float percBehind)
{
	TextRenderer::render(window, percBehind);
}