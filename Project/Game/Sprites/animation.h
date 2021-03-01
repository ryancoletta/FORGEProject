#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include "globals.h"

class Animation
{
public:
	Animation(std::string name, int frames, int framesPerSecond, Vector2 firstFramePosition, Vector2 frameScale);

	std::string getName() const;
	int getFrames() const;
	int getMilisecondsPerFrame() const;
	SDL_Rect getFrameRect(int frame);

private:
	int _frames;
	int _milisecondsPerFrame;
	std::string _name;
	Vector2 _firstFramePosition;
	Vector2 _frameScale;
	std::vector<SDL_Rect> _frameRects;
};

