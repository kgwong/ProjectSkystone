#ifndef TRIPLE_SHOT_AI_COMPONENT_H
#define TRIPLE_SHOT_AI_COMPONENT_H

#include "AIComponent.h"

class TripleShotAIComponent :
	public AIComponent
{
public:
	const double DEFAULT_SHOT_DELAY = 0.3;
	


public:
	TripleShotAIComponent(GameObject & owner);
	virtual ~TripleShotAIComponent();

	virtual void start(Scene & scene);
	virtual void update(Scene & scene);

private:
	double delay_;
};

#endif //TRIPLE_SHOT_AI_COMPONENT_H