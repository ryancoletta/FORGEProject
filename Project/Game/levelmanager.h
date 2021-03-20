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
		//"Assets/Levels/debug.tmx",
		"Assets/Levels/1.tmx",
		"Assets/Levels/2.tmx",
		"Assets/Levels/3.tmx",
		"Assets/Levels/4.tmx",
		"Assets/Levels/5.tmx",
		"Assets/Levels/6.tmx",
		"Assets/Levels/7.tmx",
		"Assets/Levels/8.tmx",
		"Assets/Levels/9.tmx",
		"Assets/Levels/10.tmx",
		"Assets/Levels/11.tmx",
		"Assets/Levels/12.tmx",
		"Assets/Levels/13.tmx",
		"Assets/Levels/14.tmx",
		"Assets/Levels/15.tmx",
	};
};

