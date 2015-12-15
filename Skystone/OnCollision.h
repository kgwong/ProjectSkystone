#ifndef ON_COLLISION_H
#define ON_COLLISION_H

#include "Component.h"

class OnCollision : public Component
{
public:
	OnCollision();
	virtual ~OnCollision();

	virtual void start(Level& level);
	virtual void update(Level& level);

	virtual void execute(Level& level);
};

#endif //ON_COLLISION_H