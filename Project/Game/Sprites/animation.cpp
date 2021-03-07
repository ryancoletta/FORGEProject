#include "globals.h"
#include "animation.h"

Animation::Animation(std::string name, int frames, int framesPerSecond, glm::vec2 firstFramePosition, glm::vec2 frameScale) :
	_name(name),
	_frames(frames),
	_milisecondsPerFrame(framesPerSecond),
	_firstFramePosition(firstFramePosition),
	_frameScale(frameScale)
{
	for (int i = 0; i < frames; i++) {
		int xPos = i * frameScale.x + firstFramePosition.x;
		SDL_Rect newRect = { 
			xPos, 
			static_cast<int>(firstFramePosition.y), 
			static_cast<int>(frameScale.x), 
			static_cast<int>(frameScale.y) 
		};
		_frameRects.push_back(newRect);
	}
}

std::string Animation::getName() const { return _name; }

int Animation::getFrames() const { return _frames; }

int Animation::getMilisecondsPerFrame() const { return _milisecondsPerFrame; }

SDL_Rect Animation::getFrameRect(int frame) { return _frameRects[frame]; } // TODO this assumes all on the same line rn, add a wrapping behaviour
