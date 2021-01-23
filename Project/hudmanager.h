#pragma once
#include "globals.h"
#include <string>
#include <vector>

class Graphics;
class Font;
class Text;
enum TextAlignment;

class HudManager
{
public:
	HudManager(Graphics* graphics);
	~HudManager();

	void draw();
	Text* writeText(std::string text, Vector2 position, TextAlignment alignment);
	void clearScreen();
private:
	Font* _font;
	std::vector<Text*> _allText;
};

