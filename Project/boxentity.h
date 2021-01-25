#pragma once
#include "entity.h"
class BoxEntity : public Entity
{
public:
	void fall(int turn);
	void undo(int turn) override;
	void reset() override;
private:
	int _fallenTurn;
};

