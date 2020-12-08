#include "globals.h"
#include "animation.h"

Animation::Animation(std::string name, int frames, int framesPerSecond, Vector2 firstFramePosition, Vector2 frameScale) :
	_name(name),
	_frames(frames),
	_milisecondsPerFrame(framesPerSecond),
	_firstFramePosition(firstFramePosition),
	_frameScale(frameScale)
{
	for (int i = 0; i < frames; i++) {
		int xPos = i * frameScale.x + firstFramePosition.x;
		SDL_Rect newRect = { xPos, firstFramePosition.y, frameScale.x, frameScale.y };
		_frameRects.push_back(newRect);
	}
}

std::string Animation::getName() { return _name; }
int Animation::getFrames() { return _frames; }
int Animation::getMilisecondsPerFrame() { return _milisecondsPerFrame; }

// TODO this assumes all on the same line rn, add a wrapping behaviour
SDL_Rect Animation::getFrameRect(int frame) {
	return _frameRects[frame];
}
