#pragma once
#include <vector>
#include <map>
#include <string>
#include "globals.h"
#include "sprite.h"
#include <functional>

class Animation;

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(Graphics* graphics, const std::string& texturePath, const std::string& palettePath, const std::string& vertPath, const std::string& fragPath, glm::vec2 sourcePosition, glm::vec2 sourceScale, glm::vec2 offset = glm::vec2(0));

	void setVisible(bool visible);

	// pass funciton parameter
	// function pointers
	virtual void onAnimationDone(std::string currentAnimationName) {}

	void addAnimation(Animation* animation);
	void playAnimation(std::string animationName, bool isLoop = false, bool resetFrameIndex = false, bool inReverse = false);
	void jumpToFrame(std::string animationName, int frame);
	void resetAnimations();
	void stopAnimation();
	void update(int deltaTime) override;
	void draw(glm::vec2 position, const float clockWiseAngleRotation = 0) override;

private:
	int _frameIndex;
	int _timeElapsed;
	bool _visible;
	bool _isLoop;
	bool _active;
	bool _inReverse;
	std::string _currentAnimationName;
	std::map<std::string, Animation*> _animations;
};