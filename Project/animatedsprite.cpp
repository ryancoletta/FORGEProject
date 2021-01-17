#include "globals.h"
#include "animatedsprite.h"
#include "graphics.h"
#include "animation.h"
#include "material.h"

AnimatedSprite::AnimatedSprite(Graphics* graphics, Material* material, Vector2 origin) :
	SpriteInstance(graphics, material, origin),
	_frameIndex(0),
	_timeElapsed(0), 
	_visible(true), 
	_isLoop(false), 
	_currentAnimationName("")
{}

void AnimatedSprite::setVisible(bool visible) { _visible = visible; }

void AnimatedSprite::addAnimation(Animation* animation) { _animations.insert(std::pair<std::string, Animation*>(animation->getName(), animation)); }

void AnimatedSprite::playAnimation(std::string animationName, bool isLoop) {
	_isLoop = isLoop;
	if (_currentAnimationName != animationName && _animations.count(animationName) > 0) {
		_currentAnimationName = animationName;
		_frameIndex = 0;
	}
}

void AnimatedSprite::resetAnimations() { _animations.clear(); }

void AnimatedSprite::stopAnimation() {
	_frameIndex = 0;
	onAnimationDone(_currentAnimationName);
}

void AnimatedSprite::update(int deltaTime) {
	SpriteInstance::update(deltaTime);

	if (_currentAnimationName == "") { return; }

	_timeElapsed += deltaTime;

	Animation* currentAnimation = _animations[_currentAnimationName];
	if (_timeElapsed > currentAnimation->getMilisecondsPerFrame()) {
		_timeElapsed -= currentAnimation->getMilisecondsPerFrame();
		int totalFrames = currentAnimation->getFrames() - 1;
		if (_frameIndex < totalFrames) {
			_frameIndex++;
		}
		else {
			if (!_isLoop) {
				onAnimationDone(_currentAnimationName);
			}
			_frameIndex = 0;
		}
	}
}

void AnimatedSprite::draw(Vector2 position, const float clockWiseAngleRotation) {
	if (_animations.empty() || _currentAnimationName == "") {
		SpriteInstance::draw(position);
		return;
	}

	if (_visible) {
		SDL_Rect destRect = {
			position.x - _origin.x,
			position.y - _origin.y,
			_material->getSourceRect().w* globals::SPRITE_SCALE,
			_material->getSourceRect().h* globals::SPRITE_SCALE
		};
		SDL_Rect sourceRect = _animations[_currentAnimationName]->getFrameRect(_frameIndex);
		_graphics->draw(_material, sourceRect, destRect, clockWiseAngleRotation); // TODO this is why we must pass source rect in a draw!!
	}
}