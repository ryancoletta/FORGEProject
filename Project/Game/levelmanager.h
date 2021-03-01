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
	
	void undo(int turn);
	void reset();

	void update(int deltaTimeMs);

private:
	void clear();

	int _levelIndex;
	Uint32 _nextLevelEvent;
	Level* _currentLevel;
	std::vector<std::string> _levelPaths = { 
		"Assets/debug.tmx",
		"Assets/1.tmx",
		"Assets/2.tmx",
		"Assets/3.tmx",
		"Assets/4.tmx",
		"Assets/5.tmx",
		"Assets/6.tmx",
		"Assets/7.tmx",
		"Assets/8.tmx",
		"Assets/9.tmx",
		"Assets/10.tmx",
		"Assets/11.tmx",
		"Assets/12.tmx",
		"Assets/13.tmx",
		"Assets/14.tmx",
		"Assets/15.tmx",
	};
};

