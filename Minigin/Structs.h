#pragma once
#include <math.h>

struct Vector
{
	float x, y;
};

struct Rect
{
	float x, y, w, h;
};

struct Circle
{
	Vector center;
	float radius;
};

struct Ellipse
{
	Vector center;
	float radiusX, radiusY;
};

inline bool IsPointInRect(const Rect& rect, float x, float y)
{
	return x > rect.x&& x < rect.x + rect.w && y > rect.y&& y < rect.y + rect.h;
}

inline bool IsPointInRect(const Rect& rect, const Vector& point)
{
	return IsPointInRect(rect, point.x, point.y);
}

inline float Dot(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y;
}

inline bool IsPointInCircle(const Circle& circle, const Vector& point)
{
	return Dot(circle.center, point) < circle.radius * circle.radius;
}

inline bool IsPointInEllipse(const Ellipse& ellipse, const Vector& point)
{
	float x = point.x - ellipse.center.x;
	x *= x;
	float y = point.y - ellipse.center.y;
	y *= y;
	float res = x / ellipse.radiusX + y / ellipse.radiusY;
	return !(res > 1);
}

inline float Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - b.x * a.x;
}

inline float Distance(const Vector& a, const Vector& b)
{
	return sqrtf(Dot(a, b));
}


