#pragma once
#include <vector>
#include <map>
#include <string>
#include "globals.h"
#include "sprite.h"

class Animation;

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(Graphics* graphics, const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale, glm::vec2 offset = glm::vec2(0));

	void setVisible(bool visible);

	virtual void onAnimationDone(std::string currentAnimationName) {}

	void addAnimation(Animation* animation);
	void playAnimation(std::string animation, bool isLoop = false, bool resetFrameIndex = false, bool inReverse = false);
	void resetAnimations();
	void stopAnimation();
	void update(int deltaTime) override;
	void draw(Vector2 position, const float clockWiseAngleRotation = 0) override;

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