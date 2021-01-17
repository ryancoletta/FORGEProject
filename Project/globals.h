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
namespace globals {
	const float PI = 3.14159265359;
	const float TAU = 6.28318530718;
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
	const int SPRITE_SCALE = 3;
	const int WINDOW_WIDTH = 256 * SPRITE_SCALE;
	const int WINDOW_HEIGHT = 256 * SPRITE_SCALE;
}

struct Vector2 {
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}

	float magnitude() { return sqrt(x * x + y * y); }
	inline Vector2& normalize(void) {
		x / magnitude(); 
		y / magnitude();
		return *this;
	}
	// returns an angle 0-360
	static float angle(Vector2 a, Vector2 b) {
		float angleInRadians = atan2(determinant(a,b), dot(a, b));
		return angleInRadians * 180 / globals::PI;
	}
	static float determinant(const Vector2& a, const Vector2& b) {
		return a.x * b.y - a.y * b.x;
	}
	static float dot(const Vector2& a, const Vector2& b) {
		return a.x * b.x + a.y * b.y;
	}

	static Vector2 rotate(Vector2 v, float degrees) {
		const float degreesToRadians = globals::TAU / 360;
		float s = sin(degrees * degreesToRadians);
		float c = cos(degrees * degreesToRadians);

		float tx = v.x;
		float ty = v.y;
		v.x = (c * tx) - (s * ty);
		v.y = (s * tx) + (c * ty);
		return v;
	}

	//VECTOR2 CONSTANTS
	static const Vector2 zero() { return Vector2(0, 0); }
	static const Vector2 up() { return Vector2(0, 1); }
	static const Vector2 right() { return Vector2(1, 0); }
	static const Vector2 down() { return Vector2(0, -1); }
	static const Vector2 left() { return Vector2(-1, 0); }

	//ASSINGMENT AND EQUALITY OPERATIONS
	inline Vector2& operator = (const Vector2& v) { x = v.x; y = v.y; return *this; }
	inline Vector2 operator - (void) { return Vector2(-x, -y); }
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
