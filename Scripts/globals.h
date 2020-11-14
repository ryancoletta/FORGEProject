#pragma once

namespace globals {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	const float SPRITE_SCALE = 2.0f;
}

struct Vector2 {
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int x, int y) : x(x), y(y) {}
	static const Vector2 zero() { return Vector2(0, 0); }
	static const Vector2 up() { return Vector2(0, 1); }
	static const Vector2 right() { return Vector2(1, 0); }
	static const Vector2 down() { return Vector2(0, -1); }
	static const Vector2 left() { return Vector2(-1, 0); }

	//ASSINGMENT AND EQUALITY OPERATIONS
	inline Vector2& operator = (const Vector2& v) { x = v.x; y = v.y; return *this; }
	inline Vector2& operator = (const float& f) { x = f; y = f; return *this; }
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
	inline const Vector2 operator + (float v) const { return Vector2(x + v, y + v); }
	inline const Vector2 operator - (float v) const { return Vector2(x - v, y - v); }
	inline const Vector2 operator * (float v) const { return Vector2(x * v, y * v); }
	inline const Vector2 operator / (float v) const { return Vector2(x / v, y / v); }

	//SCALER TO THIS OPERATIONS
	inline Vector2& operator += (float v) { x += v; y += v; return *this; }
	inline Vector2& operator -= (float v) { x -= v; y -= v; return *this; }
	inline Vector2& operator *= (float v) { x *= v; y *= v; return *this; }
	inline Vector2& operator /= (float v) { x /= v; y /= v; return *this; }
};