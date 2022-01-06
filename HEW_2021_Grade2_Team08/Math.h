#pragma once
#ifndef MATH_H
#define MATH_H
// DirectX11 関連
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
//*****************************************************************************

#include <cmath>
#include <memory.h>
#include <limits>

//using Vec2 = D3DXVECTOR2;
#if 0
struct Vec2
{
	float x_;
	float y_;

	Vec2()
		:x_(0)
		, y_(0)
	{}

	explicit Vec2(float x, float y)
		:x_(x)
		, y_(y)
	{}

	void Set(class Vec2 vec2)
	{
		x_ = vec2.x_;
		y_ = vec2.y_;
	}

	friend Vec2 operator+(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.x_ + b.x_, a.y_ + b.y_);
	}

	// Vector subtraction (a - b)
	friend Vec2 operator-(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.x_ - b.x_, a.y_ - b.y_);
	}

	// Component-wise multiplication
	// (a.x_ * b.x_, ...)
	friend Vec2 operator*(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.x_ * b.x_, a.y_ * b.y_);
	}

	// Scalar multiplication
	friend Vec2 operator*(const Vec2& vec, float scalar)
	{
		return Vec2(vec.x_ * scalar, vec.y_ * scalar);
	}

	// Scalar multiplication
	friend Vec2 operator*(float scalar, const Vec2& vec)
	{
		return Vec2(vec.x_ * scalar, vec.y_ * scalar);
	}

	// Scalar *=
	Vec2& operator*=(float scalar)
	{
		x_ *= scalar;
		y_ *= scalar;
		return *this;
	}

	// Vector +=
	Vec2& operator+=(const Vec2& right)
	{
		x_ += right.x_;
		y_ += right.y_;
		return *this;
	}

	// Vector -=
	Vec2& operator-=(const Vec2& right)
	{
		x_ -= right.x_;
		y_ -= right.y_;
		return *this;
	}
};
#else


inline bool NearZero(float val, float epsilon = 0.001f)
{
	if (fabs(val) <= epsilon)
		return true;
	else
		return false;
}

struct Vec2
{
public:
	float x_;
	float y_;

	Vec2() = default;
	Vec2(float x_, float y_)
		:x_(x_)
		, y_(y_)
	{}

	// Vector addition (a + b)
	friend Vec2 operator+(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.x_ + b.x_, a.y_ + b.y_);
	}

	// Vector subtraction (a - b)
	friend Vec2 operator-(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.x_ - b.x_, a.y_ - b.y_);
	}

	// Component-wise multiplication
	// (a.x_ * b.x_, ...)
	friend Vec2 operator*(const Vec2& a, const Vec2& b)
	{
		return Vec2(a.x_ * b.x_, a.y_ * b.y_);
	}

	// Scalar multiplication
	friend Vec2 operator*(const Vec2& vec, float scalar)
	{
		return Vec2(vec.x_ * scalar, vec.y_ * scalar);
	}

	// Scalar multiplication
	friend Vec2 operator*(float scalar, const Vec2& vec)
	{
		return Vec2(vec.x_ * scalar, vec.y_ * scalar);
	}

	// Scalar *=
	Vec2& operator*=(float scalar)
	{
		x_ *= scalar;
		y_ *= scalar;
		return *this;
	}

	// Vector +=
	Vec2& operator+=(const Vec2& right)
	{
		x_ += right.x_;
		y_ += right.y_;
		return *this;
	}

	// Vector -=
	Vec2& operator-=(const Vec2& right)
	{
		x_ -= right.x_;
		y_ -= right.y_;
		return *this;
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x_ * x_ + y_ * y_);
	}

	// Length of vector
	float Length() const
	{
		return (sqrtf(LengthSq()));
	}

	// Normalize this vector
	void Normalize()
	{
		float length = Length();
		x_ /= length;
		y_ /= length;
	}

	// Normalize the provided vector
	static Vec2 Normalize(const Vec2& vec)
	{
		Vec2 temp = vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vec2& a, const Vec2& b)
	{
		return (a.x_ * b.x_ + a.y_ * b.y_);
	}

	// Lerp from A to B by f
	static Vec2 Lerp(const Vec2& a, const Vec2& b, float f)
	{
		return Vec2(a + f * (b - a));
	}

	static const Vec2 Zero;
};

struct Rect
{
	Rect() = default;
	Rect(Vec2 pos_center, Vec2 size)
		:center_(pos_center)
		, size_(size)
		, topleft_(pos_center.x_ - size.x_ * 0.5f, pos_center.y_ - size.y_ * 0.5f)
		, bottomright_(pos_center.x_ + size.x_ * 0.5f, pos_center.y_ + size.y_ * 0.5f) {}

	Vec2 center_;
	Vec2 size_;
	Vec2 topleft_;
	Vec2 bottomright_;

	friend Rect operator+(const Rect& a, const Rect& b)
	{
		return {
			a.center_ + b.center_,
			a.size_ + b.size_  ,
		};
	}
	friend Rect operator-(const Rect& a, const Rect& b)
	{
		return {
			a.center_ - b.center_,
			a.size_ - b.size_  ,
		};
	}
	friend Rect operator*(const Rect& a, const Rect& b)
	{
		return {
			a.center_ * b.center_,
			a.size_ * b.size_  ,
		};
	}
	friend Rect operator*(const Rect& a, const float scalar)
	{
		return {
			a.center_ * scalar,
			a.size_ * scalar,
		};
	}
	friend Rect operator*(const float scalar, const Rect& a)
	{
		return {
			a.center_ * scalar,
			a.size_ * scalar,
		};
	}
	Rect& operator*=(const float scalar)
	{
		size_ *= scalar;
		center_ *= scalar;
		topleft_ *= scalar;
		bottomright_ *= scalar;
		return *this;
	}
	Rect& operator+=(const Rect& r)
	{
		//size_ += r.size_;
		center_ += r.center_;
		topleft_ += r.topleft_;
		bottomright_ += r.bottomright_;
		return *this;
	}
	Rect& operator-=(const Rect& r)
	{
		//size_ -= r.size_;
		center_ -= r.center_;
		topleft_ -= r.topleft_;
		bottomright_ -= r.bottomright_;
		return *this;
	}
};
//bool CollisionRC(Rect const& const rect, Rect const& const center, int rindex, int lindex);
// ★矩形の範囲(Rect)と矩形の中心(Center)で当たり判定
bool CollisionRC(class Actor const* const rect, class Actor const* const center);
// ★矩形の範囲(Rect)と矩形の範囲(Rect)で当たり判定
bool CollisionRR(class Actor const* const rect, class Actor const* const center);

// ★矩形の範囲(Rect)と矩形の範囲(Rect)で当たり判定(インデックスを判定に入れない)
bool CollisionRC_NoInd(class Actor const* const rect, class Actor const* const center);
#endif
#endif // !MATH_H
