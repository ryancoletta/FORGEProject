#pragma once
#include "globals.h"
#include <map>
#include <string>
class Animation;

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();
	Animation* loadAnimation(std::string name, int frames, int framesPerSecond, Vector2 firstFramePosition, Vector2 frameScale);
private:
	std::map<std::string, Animation*> _loadedAnimations;
};

