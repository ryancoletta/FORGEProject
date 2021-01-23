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

	int getLevelIndex();
	
	bool loadLevel(int levelIndex, Graphics* graphics, EntityManager* entityManager, SpriteManager* spriteManager);
	bool loadNextLevel(Graphics* graphics, EntityManager* entityManager, SpriteManager* spriteManager);
	void levelComplete();
	void draw();
	void update(int deltaTimeMs);

private:
	void clear();

	int _levelIndex;
	Uint32 _nextLevelEvent;
	Level* _currentLevel;
	std::vector<std::string> _levelPaths = { 
		"Assets/1.tmx"
	};
};

