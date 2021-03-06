#pragma once
#include <math.h>

namespace tait
{
	const float PI{ 3.141592653589793238462643383279502884197169399375105820974944592307816406286f };

	struct Vector
	{
		float x, y;
	};

	struct Vector3
	{
		float x, y, z;
	};

	inline float DotV3(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

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

	struct TRSMatrix
	{
		float 
			x1y1{}, x2y1{}, x3y1{},
			x1y2{}, x2y2{}, x3y2{},
			x1y3{}, x2y3{}, x3y3{};
	};

	inline bool IsFloatNOTZero(float f)
	{
		return f < -FLT_EPSILON || f > FLT_EPSILON;
	}

	inline bool IsFloatZero(float f)
	{
		return !IsFloatNOTZero(f);
	}

	inline Vector OneVector(const Vector& v)
	{
		return Vector{ IsFloatNOTZero(v.x) ? v.x / abs(v.x) : 0, IsFloatNOTZero(v.y) ? v.y / abs(v.y) : 0 };
	}

	inline bool IsFloatEqual(float f, float equalTo)
	{
		return abs(f - equalTo) < FLT_EPSILON;
	}

	inline float DegToRad(float angleInDeg)
	{
		return angleInDeg * PI / 180;
	}

	inline float RadToDeg(float angleInRad)
	{
		return angleInRad * 180 / PI;
	}

	inline Vector operator/(Vector v, float s)
	{
		if (s > FLT_EPSILON || s < -FLT_EPSILON)
		{
			v.x /= s;
			v.y /= s;
		}
		return v;
	}

	inline Vector operator*(Vector v, float s)
	{
		v.x *= s;
		v.y *= s;
		return v;
	}

	inline Vector operator-(Vector v1, const Vector& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		return v1;
	}

	inline Vector operator-(Vector v)
	{
		v.x *= -1;
		v.y *= -1;
		return v;
	}

	inline TRSMatrix operator*(const TRSMatrix& m1, float s)
	{
		TRSMatrix result{};
		result.x1y1 = m1.x1y1 * s;
		result.x1y2 = m1.x1y2 * s;
		result.x1y3 = m1.x1y3 * s;
		result.x2y1 = m1.x2y1 * s;
		result.x2y2 = m1.x2y2 * s;
		result.x2y3 = m1.x2y3 * s;
		result.x3y1 = m1.x3y1 * s;
		result.x3y2 = m1.x3y2 * s;
		result.x3y3 = m1.x3y3 * s;
		return result;
	}

	inline TRSMatrix operator*(const TRSMatrix& m1, const TRSMatrix& m2)
	{
		TRSMatrix result{};
		Vector3 m1v1{ m1.x1y1, m1.x2y1, m1.x3y1 };
		Vector3 m1v2{ m1.x1y2, m1.x2y2, m1.x3y2 };
		Vector3 m1v3{ m1.x1y3, m1.x2y3, m1.x3y3 };

		Vector3 m2v1{ m2.x1y1, m2.x1y2, m2.x1y3 };
		Vector3 m2v2{ m2.x2y1, m2.x2y2, m2.x2y3 };
		Vector3 m2v3{ m2.x3y1, m2.x3y2, m2.x3y3 };

		result.x1y1 = DotV3(m1v1, m2v1);
		result.x2y1 = DotV3(m1v1, m2v2);
		result.x3y1 = DotV3(m1v1, m2v3);

		result.x1y2 = DotV3(m1v2, m2v1);
		result.x2y2 = DotV3(m1v2, m2v2);
		result.x3y2 = DotV3(m1v2, m2v3);

		result.x1y3 = DotV3(m1v3, m2v1);
		result.x2y3 = DotV3(m1v3, m2v2);
		result.x3y3 = DotV3(m1v3, m2v3);

		return result;
	}

	inline Vector3 operator*(const TRSMatrix& m, const Vector3& v)
	{
		Vector3 result{};
		result.x = m.x1y1 * v.x + m.x2y1 * v.y + m.x3y1 * v.z;
		result.y = m.x1y2 * v.x + m.x2y2 * v.y + m.x3y2 * v.z;
		result.z = m.x1y3 * v.x + m.x2y3 * v.y + m.x3y3 * v.z;
		return result;
	}

	inline float GetDeterminantScalar(const TRSMatrix& m)
	{
		float diag1 = m.x1y1 * m.x2y2 * m.x3y3;
		float diag2 = m.x2y1 * m.x3y2 * m.x1y3;
		float diag3 = m.x3y1 * m.x1y2 * m.x2y3;
		float diag4 = m.x1y3 * m.x2y2 * m.x3y1;
		float diag5 = m.x2y3 * m.x3y2 * m.x1y1;
		float diag6 = m.x3y3 * m.x1y2 * m.x2y1;
		return (diag1 + diag2 + diag3) - (diag4 + diag5 + diag6);
	}

	inline TRSMatrix&& GetCrossedMatrix(const TRSMatrix& m)
	{
		TRSMatrix n{};
		n.x1y1 = m.x2y2 * m.x3y3 - m.x2y3 * m.x3y2;
		n.x2y1 = -(m.x1y2 * m.x3y3 - m.x1y3 * m.x3y2);
		n.x3y1 = m.x1y2 * m.x2y3 - m.x1y3 * m.x2y2;
		n.x1y2 = -(m.x2y1 * m.x3y3 - m.x3y1 * m.x2y3);
		n.x2y2 = m.x2y1 * m.x3y3 - m.x3y1 * m.x2y3;
		n.x3y2 = -(m.x1y1 * m.x2y3 - m.x2y1 * m.x1y3);
		n.x1y3 = m.x2y1 * m.x3y2 - m.x3y1 * m.x2y2;
		n.x2y3 = -(m.x1y1 * m.x3y2 - m.x3y1 * m.x1y2);
		n.x3y3 = m.x1y1 * m.x2y2 - m.x2y1 * m.x1y2;
		return std::move(n);
	}

	inline void MirrorMatrix(TRSMatrix& m)
	{
		float temp{m.x2y1};
		m.x2y1 = m.x1y2;
		m.x1y2 = temp;
		temp = m.x3y1;
		m.x3y1 = m.x1y3;
		m.x1y3 = temp;
		temp = m.x3y2;
		m.x3y2 = m.x2y3;
		m.x2y3 = temp;
	}

	inline void InvertTRS(TRSMatrix& m)
	{
		float det = GetDeterminantScalar(m);
		TRSMatrix n = GetCrossedMatrix(m);
		MirrorMatrix(n);
		det = 1 / det;
		m = n * det;
	}

	inline TRSMatrix&& GetTrsMatrix(const Vector& pos, float angleInRad, const Vector& scale)
	{
		TRSMatrix transM{};
		transM.x1y1 = 1;
		transM.x2y2 = 1;
		transM.x3y3 = 1;
		transM.x3y1 = pos.x;
		transM.x3y2 = pos.y;

		TRSMatrix rotM{};
		rotM.x3y3 = 1;
		rotM.x1y1 = cosf(angleInRad);
		rotM.x2y1 = -sinf(angleInRad);
		rotM.x1y2 = sinf(angleInRad);
		rotM.x2y2 = cosf(angleInRad);

		TRSMatrix scaleM{};
		scaleM.x3y3 = 1;
		scaleM.x1y1 = scale.x;
		scaleM.x2y2 = scale.y;
		TRSMatrix ret = transM * rotM * scaleM;
		return std::move(ret);
	}

	inline Vector operator+(const Vector& a, const Vector& b)
	{
		return Vector{ a.x + b.x, a.y + b.y };
	}

	inline Vector operator*(const Vector& a, const Vector& b)
	{
		return Vector{ a.x * b.x, a.y * b.y };
	}

	inline bool AreRectOverlapping(const Rect& r1, const Rect& r2)
	{
		return r1.x < r2.x + r2.w && r1.x > r2.x - r1.w && r1.y < r2.y + r2.h && r1.y > r2.y - r1.h;
	}

	inline bool IsPointInRect(const Rect& rect, float x, float y)
	{
		return x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h;
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

	inline float SquareDistance(const Vector& a, const Vector& b)
	{
		Vector d = b + (-a);
		return abs(Dot(d, d));
	}

	inline float Distance(const Vector& a, const Vector& b)
	{
		return sqrtf(SquareDistance(a,b));
	}

	inline bool IsEllipseInRect(const Rect& r, const Ellipse& e)
	{
		if (IsPointInEllipse(e, Vector{ r.x,r.y }))
			return true;
		if (IsPointInEllipse(e, Vector{ r.x,r.y + r.h }))
			return true;
		if (IsPointInEllipse(e, Vector{ r.x + r.w,r.y }))
			return true;
		if (IsPointInEllipse(e, Vector{ r.x + r.w,r.y + r.h }))
			return true;
		if (IsPointInRect(Rect{ r.x - e.radiusX, r.y - e.radiusY, r.w + e.radiusX * 2, r.h + e.radiusY * 2 }, e.center))
			return true;
		return false;
	}

	inline bool IsCircleInRect(const Rect& r, const Circle& c)
	{
		if (IsPointInCircle(c, Vector{ r.x,r.y }))
			return true;
		if (IsPointInCircle(c, Vector{ r.x,r.y + r.h }))
			return true;
		if (IsPointInCircle(c, Vector{ r.x + r.w,r.y }))
			return true;
		if (IsPointInCircle(c, Vector{ r.x + r.w,r.y + r.h }))
			return true;
		if (IsPointInRect(Rect{ r.x - c.radius, r.y - c.radius, r.w + c.radius * 2, r.h + c.radius * 2 }, c.center))
			return true;
		return false;
	}

	inline bool AreCircleOverlapping(const Circle& c1, const Circle& c2)
	{
		float sqrR = c1.radius + c2.radius;
		sqrR *= sqrR;
		return SquareDistance(c1.center, c2.center) < sqrR;
	}

}