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

namespace globals {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
	const int WINDOW_WIDTH = 960;
	const int WINDOW_HEIGHT = 720;
	const int SPRITE_SCALE = 3;
}

struct Vector2 {
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}

	float magnitude() { return sqrt(x * x + y * y); }
	void normalize() { 
		x / magnitude(); 
		y / magnitude();
	}
	
	static float dot(const Vector2& a, const Vector2& b) {
		return a.x * b.x + a.y * b.y;
	}

	//VECTOR2 CONSTANTS
	static const Vector2 zero() { return Vector2(0, 0); }
	static const Vector2 up() { return Vector2(0, 1); }
	static const Vector2 right() { return Vector2(1, 0); }
	static const Vector2 down() { return Vector2(0, -1); }
	static const Vector2 left() { return Vector2(-1, 0); }

	//ASSINGMENT AND EQUALITY OPERATIONS
	inline Vector2& operator = (const Vector2& v) { x = v.x; y = v.y; return *this; }
	inline Vector2& operator = (const int& f) { x = f; y = f; return *this; }
	inline Vector2& operator - (void) { x = -x; y = -y; return *this; }
	inline bool operator == (const Vector2& v) const { return (x == v.x) && (y == v.y); }
	inline bool operator != (const Vector2& v) const { return (x != v.x) || (y != v.y); }

	//VECTOR2 TO VECTOR2 OPERATIONS
	inline const Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	inline const Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	inline const Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
	inline const Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

	//VECTOR2 TO THIS OPERATIONS
	inline Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
	inline Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	inline Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
	inline Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

	//SCALER TO VECTOR2 OPERATIONS
	inline const Vector2 operator + (int v) const { return Vector2(x + v, y + v); }
	inline const Vector2 operator - (int v) const { return Vector2(x - v, y - v); }
	inline const Vector2 operator * (int v) const { return Vector2(x * v, y * v); }
	inline const Vector2 operator / (int v) const { return Vector2(x / v, y / v); }

	//SCALER TO THIS OPERATIONS
	inline Vector2& operator += (int v) { x += v; y += v; return *this; }
	inline Vector2& operator -= (int v) { x -= v; y -= v; return *this; }
	inline Vector2& operator *= (int v) { x *= v; y *= v; return *this; }
	inline Vector2& operator /= (int v) { x /= v; y /= v; return *this; }
};
