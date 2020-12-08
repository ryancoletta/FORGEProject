#pragma once
#include <string>
#include <vector>
#include <SDL.h>

class Level;
class Graphics;
class EntityManager;
class SpriteManager;

class LevelManager
{
public:
	LevelManager(Uint32 nextLevelEvent);
	~LevelManager();
	bool loadLevel(int levelIndex, Graphics* graphics, EntityManager* entityManager, SpriteManager* spriteManager);
	bool loadNextLevel(Graphics* graphics, EntityManager* entityManager, SpriteManager* spriteManager);
	void draw();
	void levelComplete();
private:
	void clear();
	std::vector<std::string> _levelPaths = { 
		"Assets/level1.tmx",
		"Assets/level2.tmx",
		"Assets/level3.tmx"
	};
	Uint32 _nextLevelEvent;
	int _levelIndex;
	Level* _currentLevel;
};

