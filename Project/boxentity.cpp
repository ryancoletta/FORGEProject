#include "boxentity.h"
#include "animatedsprite.h"

void BoxEntity::fall(int turn)
{
	static_cast<AnimatedSprite*>(_sprite)->playAnimation("box_fall", false);
	_fallenTurn = turn; // TODO uh oh
}

void BoxEntity::undo(int turn)
{
	if (turn <= _fallenTurn) {
		static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("box_fall", 0);
	}
}

void BoxEntity::reset()
{
	static_cast<AnimatedSprite*>(_sprite)->jumpToFrame("box_fall", 0);
}
