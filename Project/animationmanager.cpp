#include "animationmanager.h"
#include "animation.h"

Animation* AnimationManager::loadAnimation(std::string name, int frames, int framesPerSecond, Vector2 firstFramePosition, Vector2 frameScale) {
	// these sprites all are uniform (no branching animations) so theres no need to create individual instances
	Animation* newAnimation;
	if (_loadedAnimations.count(name) == 0) {
		newAnimation = DBG_NEW Animation(name, frames, framesPerSecond, firstFramePosition, frameScale);
		_loadedAnimations.insert(std::pair<std::string, Animation*>(name, newAnimation));
	}
	else { return _loadedAnimations.find(name)->second; }
	return newAnimation;
}

AnimationManager::~AnimationManager() {
	std::map<std::string, Animation*>::iterator it;
	for (it = _loadedAnimations.begin(); it != _loadedAnimations.end(); it++)
	{
		delete it->second;
	}
	_loadedAnimations.clear();
}
