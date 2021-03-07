#pragma once
#include "globals.h"
#include <map>
#include <string>
class Animation;

class AnimationManager
{
public:
	~AnimationManager();

	Animation* loadAnimation(std::string name, int frames, int framesPerSecond, glm::vec2 firstFramePosition, glm::vec2 frameScale);

private:
	std::map<std::string, Animation*> _loadedAnimations;
};

