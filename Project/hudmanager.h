#pragma once
#include <vector>

class Graphics;
class Font;
class Text;

class HudManager
{
public:
	HudManager(Graphics* graphics);
	~HudManager();
	void draw();

private:
	Font* _font;
	std::vector<Text*> _allText;
};

