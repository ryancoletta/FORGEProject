#pragma once
#include "globals.h"
#include <string>
#include <vector>

class Graphics;
class Font;
class Text;
class HudImage;
class SpriteManager;
enum TextAlignment;

class HudManager
{
public:
	HudManager(Graphics* graphics, SpriteManager* spriteManager);
	~HudManager();

	void draw();
	Text* writeText(std::string text, glm::vec2 position, TextAlignment alignment);
	HudImage* spawnImage(std::string spriteName, const std::string& texturePath, const std::string& palettePath, const std::string& vertexPath, const std::string& fragmentPath, glm::vec2 sourcePosition, glm::vec2 sourceScale, glm::vec2 destinationPosition);
	void clearScreen();
private:
	SpriteManager* _spriteManager;
	Font* _font;
	std::vector<Text*> _allText;
	std::vector<HudImage*> _allImages;
};

