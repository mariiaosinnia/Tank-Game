#pragma once
#include <cmath>

class Vector2 {
public:
	float x = 0;
	float y = 0;
	Vector2() = default;
	Vector2(float x_, float y_) : x(x_), y(y_) {}

	float length() const;
	Vector2 normalized() const;

	Vector2 operator-(const Vector2& other) const;
	Vector2 operator/(float scalar) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator*=(float scalar);
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	bool operator!=(const Vector2& other) const;
};