#pragma once
#include "globals.h"
#include <string>
#include <vector>
#include <SDL.h>

class Animation
{
public:
	Animation();
	Animation(std::string name, int frames, int framesPerSecond, Vector2 firstFramePosition, Vector2 frameScale);
	std::string getName();
	int getFrames();
	int getMilisecondsPerFrame();
	SDL_Rect getFrameRect(int frame);
private:
	std::string _name;
	int _frames;
	int _milisecondsPerFrame;
	Vector2 _firstFramePosition;
	Vector2 _frameScale;
	std::vector<SDL_Rect> _frameRects;
};

