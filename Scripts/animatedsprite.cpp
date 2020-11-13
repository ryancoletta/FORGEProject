#include "animatedsprite.h"
AnimatedSprite::AnimatedSprite() : _frameIndex(0), _msPerFrame(0), _timeElapsed(0), _visible(false), _isLoop(false), _currentAnimation("")
{

}
AnimatedSprite::AnimatedSprite(Graphics* graphics, const std::string& filePath, Vector2 sourcePosition, Vector2 sourceScale, int msPerFrame) :
	Sprite(graphics, filePath, sourcePosition, sourceScale), _frameIndex(0), _msPerFrame(msPerFrame), _timeElapsed(0), _visible(true), _isLoop(false), _currentAnimation("")
{

}
void AnimatedSprite::update(int deltaTime) {
	Sprite::update(deltaTime);

	_timeElapsed += deltaTime;
	if (_timeElapsed > _msPerFrame) {
		_timeElapsed -= _msPerFrame;
		int totalFrames = _animations[_currentAnimation].size() - 1;
		if (_frameIndex < totalFrames) {
			_frameIndex++;
		}
		else {
			if (!_isLoop) {
				setVisible(false);
				onAnimationDone(_currentAnimation);
			}
			_frameIndex = 0;
		}
	}
}
void AnimatedSprite::draw() {
	if (_visible) {
		SDL_Rect destRect = {
			_position.x,
			_position.y,
			_sourceRect.w * globals::SPRITE_SCALE,
			_sourceRect.h * globals::SPRITE_SCALE
		};
		SDL_Rect sourceRect = _animations[_currentAnimation][_frameIndex];
		_graphics->blitSurface(_spriteSheet, &sourceRect, &destRect);
	}
}
// TODO temp
void AnimatedSprite::setupAnimations() {
	addAnimation("Test", 2, Vector2(0,0), Vector2(16, 16));
}
void AnimatedSprite::playAnimation(std::string animation, bool isLoop) {
	_isLoop = isLoop;
	if (_currentAnimation != animation) {
		_currentAnimation = animation;
		_frameIndex = 0;
	}
}
// TODO assumption here that animations are all on the same row
void AnimatedSprite::addAnimation(std::string name, int frames, Vector2 firstFramePosition, Vector2 frameScale) {
	std::vector<SDL_Rect> rects;
	for (int i = 0; i < frames; i++) {
		int xPos = i * frameScale.x + firstFramePosition.x;
		SDL_Rect newRect = { xPos, firstFramePosition.y, frameScale.x, frameScale.y };
		rects.push_back(newRect);
	}
	_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rects));
}
void AnimatedSprite::resetAnimations() {
	_animations.clear();
}
void AnimatedSprite::stopAnimation() {
	_frameIndex = 0;
	onAnimationDone(_currentAnimation);
}
void AnimatedSprite::setVisible(bool visible) {
	_visible = visible;
}
void AnimatedSprite::onAnimationDone(std::string currentAnimation) {

}