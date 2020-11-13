#pragma once
#include "sprite.h"
#include <vector>
#include "globals.h"
class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics* graphics, const std::string &filePath, Vector2 sourcePosition, Vector2 sourceScale, int msPerFrame);
	void update(int deltaTime) override;
	void draw() override;
	void playAnimation(std::string animation, bool isLoop = false);
	void addAnimation(std::string name, int frames, Vector2 firstFramePosition, Vector2 frameScale);
	void resetAnimations();
	void stopAnimation();
	void setVisible(bool visible);
	virtual void setupAnimations();
	virtual void onAnimationDone(std::string currentAnimation);
protected:
	float _msPerFrame;
	bool _isLoop;
	std::string _currentAnimation;



private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	int _frameIndex;
	int _timeElapsed;
	bool _visible;
};

