#include "globals.h"
#include "animatedsprite.h"
#include "graphics.h"
#include "animation.h"
#include "shader.h"
#include "texture.h"

AnimatedSprite::AnimatedSprite(Graphics* graphics, const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, Vector2 sourcePosition, Vector2 sourceScale, glm::vec2 offset) :
	Sprite(graphics, texturePath, vertPath, fragPath, sourcePosition, sourceScale, offset),
	_frameIndex(0),
	_timeElapsed(0), 
	_visible(true), 
	_isLoop(false), 
	_currentAnimationName(""),
	_active(false)
{}

void AnimatedSprite::setVisible(bool visible) { _visible = visible; }

void AnimatedSprite::addAnimation(Animation* animation) { 
	std::string animationName = animation->getName();
	_animations.insert(std::pair<std::string, Animation*>(animationName, animation));
}

void AnimatedSprite::playAnimation(std::string animationName, bool isLoop, bool resetFrameIndex, bool inReverse) {
	if (_animations.count(animationName) == 0) {
		printf("Error: animation not found");
	}
	_active = true;
	_isLoop = isLoop;
	_inReverse = inReverse;
	_currentAnimationName = animationName;

	int numFrames = _animations[_currentAnimationName]->getFrames() - 1;
	if (resetFrameIndex) { 
		if (_inReverse) {
			_frameIndex = numFrames;
		}
		else {
			_frameIndex = 0;
		}
	}
	else {
		// in cases of animations of differing lengths
		_frameIndex %= numFrames;
	}
}

void AnimatedSprite::jumpToFrame(std::string animationName, int frame)
{
	if (_animations.count(animationName) == 0) {
		printf("Error: animation not found");
	}
	_currentAnimationName = animationName;

	int totalFrames = _animations[animationName]->getFrames() - 1;
	if (frame > totalFrames) {
		printf("Error: attempting to jump to a nonexistant frame in %s\n", animationName.c_str());
		return;
	}
	_frameIndex = frame;
	_active = false;
}

void AnimatedSprite::resetAnimations() { _animations.clear(); }

void AnimatedSprite::stopAnimation() {
	_frameIndex = 0;
	onAnimationDone(_currentAnimationName);
}

void AnimatedSprite::update(int deltaTime) {
	if (_currentAnimationName == "" || !_active) { 
		return; 
	}

	_timeElapsed += deltaTime;

	Animation* currentAnimation = _animations[_currentAnimationName];
	if (_timeElapsed > currentAnimation->getMilisecondsPerFrame()) {
		_timeElapsed -= currentAnimation->getMilisecondsPerFrame();
		int totalFrames = currentAnimation->getFrames() - 1;
		
		if (_inReverse) {
			if (_frameIndex > 0) {
				_frameIndex--;
			}
			else {
				if (!_isLoop) {
					_active = false;
					onAnimationDone(_currentAnimationName);
				}
				else {
					_frameIndex = totalFrames;
				}
			}
		}
		else {
			if (_frameIndex < totalFrames) {
				_frameIndex++;
			}
			else {
				if (!_isLoop) {
					_active = false;
					onAnimationDone(_currentAnimationName);
				}
				else {
					_frameIndex = 0;
				}
			}
		}
	}
}

void AnimatedSprite::draw(Vector2 position, const float clockWiseAngleRotation) {
	if (_animations.empty() || _currentAnimationName == "") {
		Sprite::draw(position);
		return;
	}

	if (_visible) {
		_shader->bind();
		_texture->bind(0);

		SDL_Rect destRect = {
			position.x + _offset.x,
			position.y + _offset.y,
			_sourceRect.w* globals::SPRITE_SCALE,
			_sourceRect.h* globals::SPRITE_SCALE
		};
		SDL_Rect sourceRect = _animations[_currentAnimationName]->getFrameRect(_frameIndex);
		_graphics->draw(_texture, _shader, sourceRect, destRect, clockWiseAngleRotation);
	}
}