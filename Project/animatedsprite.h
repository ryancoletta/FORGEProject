#pragma once
#include <vector>
#include <map>
#include "globals.h"
#include "sprite.h"

class Animation;

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics* graphics, const std::string &filePath, Vector2 sourcePosition, Vector2 sourceScale);
	~AnimatedSprite();
	void update(int deltaTime) override;
	void draw(Vector2 position) override;
	void playAnimation(std::string animation, bool isLoop = false);
	void addAnimation(Animation* animation);
	void resetAnimations();
	void stopAnimation();
	void setVisible(bool visible);
	virtual void onAnimationDone(std::string currentAnimationName);
private:
	bool _isLoop;
	std::string _currentAnimationName;
	std::map<std::string, Animation*> _animations;
	int _frameIndex;
	int _timeElapsed;
	bool _visible;
};

