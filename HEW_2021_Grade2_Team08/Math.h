#pragma once
#ifndef MATH_H
#define MATH_H
// DirectX11 �֘A
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)

//*****************************************************************************
// ���C�u�����̃����N
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
        ,y_(0)
    {}

    explicit Vec2(float x, float y)
        :x_(x)
        ,y_(y)
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

#endif
#endif // !MATH_H
