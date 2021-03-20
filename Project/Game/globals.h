#pragma once

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
	#define DBG_NEW new
#endif

#include <stdlib.h>
#include <crtdbg.h> // replaces malloc with a way to track
#include <math.h>
#include <map>
#include <glm/glm.hpp>
namespace globals {
	const float PI = 3.14159265359f;
	const float TAU = 6.28318530718f;
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
	const int SPRITE_SCALE = 3;
	const int WINDOW_WIDTH = 256 * SPRITE_SCALE;
	const int WINDOW_HEIGHT = 256 * SPRITE_SCALE;
	const float SPRITE_FADE_TIME = 1000.0f;
	const float BETWEEN_SCENES_TIME = 1000.0f;
	const float DISPLAY_HELP_TEXT_TIME = 5000.0f;
}


// adding constants
static const glm::vec2 zero() { return glm::vec2(0, 0); }
static const glm::vec2 up() { return glm::vec2(0, 1); }
static const glm::vec2 right() { return glm::vec2(1, 0); }
static const glm::vec2 down() { return glm::vec2(0, -1); }
static const glm::vec2 left() { return glm::vec2(-1, 0); }

static glm::vec2 rotate(glm::vec2 v, float degrees) {
	const float degreesToRadians = globals::TAU / 360;
	float s = sin(degrees * degreesToRadians);
	float c = cos(degrees * degreesToRadians);

	float tx = v.x;
	float ty = v.y;
	v.x = glm::round((c * tx) - (s * ty));
	v.y = glm::round((s * tx) + (c * ty));
	return v;
}

enum EntityType {
	ENTITY_NULL = 0,
	ENTITY_NONE = 1 << 0,
	ENTITY_BOX = 1 << 1,
	ENTITY_BAT = 1 << 2,
	ENTITY_PLAYER = 1 << 3,
	ENTITY_SWORD = 1 << 4,
	ENTITY_GROUNDED = ENTITY_BOX | ENTITY_PLAYER,
	ENTITY_VULNERABLE = ENTITY_BAT,
};

enum TileType {
	TILE_WALL = 1 << 0,
	TILE_OPEN = 1 << 1,
	TILE_GOAL = 1 << 2,
	TILE_SWITCH = 1 << 3,
	TILE_SPIKE = 1 << 4,
	TILE_HOLE = 1 << 5,
};

inline EntityType operator|(EntityType a, EntityType b)
{
	return static_cast<EntityType>(static_cast<int>(a) | static_cast<int>(b));
}

inline EntityType operator&(EntityType a, EntityType b)
{
	return static_cast<EntityType>(static_cast<int>(a) & static_cast<int>(b));
}

//struct glm::vec2 {
//	int x, y;
//	glm::vec2() : x(0), y(0) {}
//	glm::vec2(int x, int y) : x(x), y(y) {}
//
//	float magnitude() { return sqrt(x * x + y * y); }
//	inline glm::vec2& normalize(void) {
//		x / magnitude(); 
//		y / magnitude();
//		return *this;
//	}
//	// returns an angle 0-360
//	static float angle(glm::vec2 a, glm::vec2 b) {
//		float angleInRadians = atan2(determinant(a,b), dot(a, b));
//		return angleInRadians * 180 / globals::PI;
//	}
//	static float determinant(const glm::vec2& a, const glm::vec2& b) {
//		return a.x * b.y - a.y * b.x;
//	}
//	static float dot(const glm::vec2& a, const glm::vec2& b) {
//		return a.x * b.x + a.y * b.y;
//	}
//
//	static glm::vec2 rotate(glm::vec2 v, float degrees) {
//		const float degreesToRadians = globals::TAU / 360;
//		float s = sin(degrees * degreesToRadians);
//		float c = cos(degrees * degreesToRadians);
//
//		float tx = v.x;
//		float ty = v.y;
//		v.x = (c * tx) - (s * ty);
//		v.y = (s * tx) + (c * ty);
//		return v;
//	}
//
//	//glm::vec2 CONSTANTS
//	static const glm::vec2 zero() { return glm::vec2(0, 0); }
//	static const glm::vec2 up() { return glm::vec2(0, 1); }
//	static const glm::vec2 right() { return glm::vec2(1, 0); }
//	static const glm::vec2 down() { return glm::vec2(0, -1); }
//	static const glm::vec2 left() { return glm::vec2(-1, 0); }
//
//	//ASSINGMENT AND EQUALITY OPERATIONS
//	inline glm::vec2& operator = (const glm::vec2& v) { x = v.x; y = v.y; return *this; }
//	inline glm::vec2 operator - (void) { return glm::vec2(-x, -y); }
//	inline bool operator == (const glm::vec2& v) const { return (x == v.x) && (y == v.y); }
//	inline bool operator != (const glm::vec2& v) const { return (x != v.x) || (y != v.y); }
//
//	//glm::vec2 TO glm::vec2 OPERATIONS
//	inline const glm::vec2 operator + (const glm::vec2& v) const { return glm::vec2(x + v.x, y + v.y); }
//	inline const glm::vec2 operator - (const glm::vec2& v) const { return glm::vec2(x - v.x, y - v.y); }
//	inline const glm::vec2 operator * (const glm::vec2& v) const { return glm::vec2(x * v.x, y * v.y); }
//	inline const glm::vec2 operator / (const glm::vec2& v) const { return glm::vec2(x / v.x, y / v.y); }
//
//	//glm::vec2 TO THIS OPERATIONS
//	inline glm::vec2& operator += (const glm::vec2& v) { x += v.x; y += v.y; return *this; }
//	inline glm::vec2& operator -= (const glm::vec2& v) { x -= v.x; y -= v.y; return *this; }
//	inline glm::vec2& operator *= (const glm::vec2& v) { x *= v.x; y *= v.y; return *this; }
//	inline glm::vec2& operator /= (const glm::vec2& v) { x /= v.x; y /= v.y; return *this; }
//
//	//SCALER TO glm::vec2 OPERATIONS
//	inline const glm::vec2 operator + (int v) const { return glm::vec2(x + v, y + v); }
//	inline const glm::vec2 operator - (int v) const { return glm::vec2(x - v, y - v); }
//	inline const glm::vec2 operator * (int v) const { return glm::vec2(x * v, y * v); }
//	inline const glm::vec2 operator / (int v) const { return glm::vec2(x / v, y / v); }
//
//	//SCALER TO THIS OPERATIONS
//	inline glm::vec2& operator += (int v) { x += v; y += v; return *this; }
//	inline glm::vec2& operator -= (int v) { x -= v; y -= v; return *this; }
//	inline glm::vec2& operator *= (int v) { x *= v; y *= v; return *this; }
//	inline glm::vec2& operator /= (int v) { x /= v; y /= v; return *this; }
//};
