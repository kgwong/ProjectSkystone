#include "ScrollingTextRenderer.h"
#include "Application/Path.h"
#include "Game/GameTime.h"
#include "Game/GameConstants.h"
#include "Components/GUI/ScrollingTextLine.h"
#include "Util/vector_util.h"
#include <fstream>

#define STARTY_OFFSET 120

const static float UPDATE_INTERVAL = .1f;
const static int LINE_SIZE = Constants::SCREEN_WIDTH - PAD_X;

namespace
{
int getTextWidth(const std::string& text)
{
	TextRenderer dummy{GameObject{}};
	int w;
	TTF_SizeText(dummy.getFont(), text.c_str(), &w, nullptr);
	return w;
}
}

ScrollingTextRenderer::ScrollingTextRenderer(GameObject& owner, const std::string& relScriptPath)
	: RenderComponent(owner), timeSinceLastScroll_(0)
{
	readScript(relScriptPath);
}


ScrollingTextRenderer::~ScrollingTextRenderer()
{
}

void ScrollingTextRenderer::render(GameWindow& window, float percBehind)
{
	if (needToScroll())
	{
		scroll();
		timeSinceLastScroll_ = 0;
	}
	else
	{
		timeSinceLastScroll_ += Time::getElapsedUpdateTimeSeconds();
	}
	renderLines(window, percBehind);
}

void ScrollingTextRenderer::renderLines(GameWindow& window, float percBehind)
{
	auto updateFunc = [&window, percBehind, this](std::shared_ptr<GameObject> go) {updateLine(window, percBehind, go);};
	auto remFunc = [this](std::shared_ptr<GameObject> go) {return remPred(go);};
	util::vector::update_or_remove <std::shared_ptr<GameObject>>(lines_, remFunc, updateFunc);
}

void ScrollingTextRenderer::readScript(const std::string& relPath)
{
	std::ifstream ifs(Path::getFullPath(relPath));
	std::string dummy, line;

	while (ifs >> dummy)
	{
		if (getTextWidth(line + dummy) >= LINE_SIZE)
		{
			addLine(line);
			line = dummy + ' ';
		}
		else
		{
			line += dummy + ' ';
		}
	}
	addLine(line);
}

void ScrollingTextRenderer::addLine(const std::string& line)
{
	int lineNumber = lines_.size() + 1;
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>(0, STARTY_OFFSET);
	go->addComponent(std::make_shared<ScrollingTextLine>(*go, lineNumber, line));
	lines_.push_back(go);
}

bool ScrollingTextRenderer::needToScroll()
{
	return timeSinceLastScroll_ >= UPDATE_INTERVAL;
}

void ScrollingTextRenderer::updateLine(GameWindow& window, float percBehind, std::shared_ptr<GameObject> go)
{
	auto line = go->getComponent<ScrollingTextLine>();
	line->render(window, percBehind);
}

bool ScrollingTextRenderer::remPred(std::shared_ptr<GameObject> go)
{
	return go->getComponent<ScrollingTextLine>()->finished();
}

void ScrollingTextRenderer::scroll()
{
	for (auto& line : lines_)
	{
		auto textLine = line->getComponent<ScrollingTextLine>();
		textLine->scroll();
	}
}
