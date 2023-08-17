#pragma once
#include <math.h>

float Lerp(float value1, float value2, float amount)
{
	return value1 + (value2 - value1) * amount;
}

struct Matrix
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;

	void Reset() {
		_11 = 0;
		_12 = 0;
		_13 = 0;
		_14 = 0;
		_21 = 0;
		_22 = 0;
		_23 = 0;
		_24 = 0;
		_31 = 0;
		_32 = 0;
		_33 = 0;
		_34 = 0;
		_41 = 0;
		_42 = 0;
		_43 = 0;
		_44 = 0;
	}
};

struct quat {
	float x, y, z, w;

	void Reset() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
};

struct vec3 {
	float X;
	float Y;
	float Z;

	vec3() {
		X = 0;
		Y = 0;
		Z = 0;
	}

	vec3(float x, float y, float z) {
		X = x;
		Y = y;
		Z = z;
	}

	void Reset() {
		X = 0;
		Y = 0;
		Z = 0;
	}

	float Magnitude() {
		return (float)sqrt((double)(this->X * this->X + this->Y * this->Y + this->Z * this->Z));
	}

	vec3 Normalized() {
		float magnitude = Magnitude();

		bool flag = magnitude > 1E-05f;

		vec3 result;

		static vec3 _this;
		_this.X = X;
		_this.Y = Y;
		_this.Z = Z;

		if (flag)
			result = _this / magnitude;
		else
			result = vec3(0,0,0);

		return result;
	}

	bool operator != (vec3 other) {
		bool result = X != other.X || Y != other.Y || Z != other.Z;
		return result;
	}

	bool operator == (vec3 other) {
		return X == other.X && Y == other.Y && Z == other.Z;
	}

	vec3 operator -= (vec3 other) {
		static vec3 buf;
		buf.X = X;
		buf.Y = Y;
		buf.Z = Z;

		buf.X -= other.X;
		buf.Y -= other.Y;
		buf.Z -= other.Z;

		return buf;
	}

	vec3 operator * (float other)
	{
		static vec3 buf;
		buf.X = X;
		buf.Y = Y;
		buf.Z = Z;
		buf.X = buf.X * other;
		buf.Y = buf.Y * other;
		buf.Z = buf.Z * other;
		return buf;
	}
	vec3 operator + (float other)
	{
		static vec3 buf;
		buf.X = X;
		buf.Y = Y;
		buf.Z = Z;
		buf.X += other;
		buf.Y += other;
		buf.Z += other;
		return buf;
	}
	vec3 operator - (vec3 other)
	{
		static vec3 buf;
		buf.X = X;
		buf.Y = Y;
		buf.Z = Z;
		buf.X = X - other.X;
		buf.Y = Y - other.Y;
		buf.Z = Z - other.Z;
		return buf;
	}
	vec3 operator + (vec3 other)
	{
		static vec3 buf;
		buf.X = X + other.X;
		buf.Y = Y + other.Y;
		buf.Z = Z + other.Z;
		return buf;
	}
	vec3 operator += (vec3 other)
	{
		static vec3 buf;
		buf.X = X;
		buf.Y = Y;
		buf.Z = Z;

		buf.X += other.X;
		buf.Y += other.Y;
		buf.Z += other.Z;
		return buf;
	}
	vec3 operator / (float other)
	{
		static vec3 buf;
		buf.X = X / other;
		buf.Y = Y / other;
		buf.Z = Z / other;
		return buf;
	}
	vec3& operator *= (float other)
	{
		static vec3 buf;
		buf.X = X;
		buf.Y = Y;
		buf.Z = Z;

		buf.X *= other;
		buf.Y *= other;
		buf.Z *= other;
		return *this;
	}
	float get_length_sqr(void) const
	{
		float buf;
		buf += (X * X);
		buf += (Y * Y);
		buf += (Z * Z);

		return buf;
	}
};

struct vec2 {
	float X;
	float Y;

	void Reset() {
		X = 0;
		Y = 0;
	}

	float Magnitude() {
		return (float)sqrt((double)(this->X * this->X + this->Y * this->Y));
	}

	vec2(float x, float y) {
		X = x;
		Y = y;
	}

	vec2() {
		X = 0;
		Y = 0;
	}

	vec2 Normalized() {
		float magnitude = Magnitude();

		bool flag = magnitude > 1E-05f;

		vec2 result;

		vec2 _this = vec2(this->X, this->Y);

		if (flag)
			result = _this / magnitude;
		else
			result = vec2(0, 0);

		return result;
	}

	bool operator != (vec2 other) {
		bool result = X != other.X || Y != other.Y;
		return result;
	}

	bool operator == (vec2 other) {
		return X == other.X && Y == other.Y;
	}

	vec2 operator -= (vec2 other) {
		vec2 buf = vec2(X,Y);

		buf.X -= other.X;
		buf.Y -= other.Y;

		return buf;
	}

	vec2 operator * (float other)
	{
		vec2 buf;
		buf.X *= other;
		buf.Y *= other;
		return buf;
	}
	vec2 operator + (float other)
	{
		vec2 buf;
		buf.X += other;
		buf.Y += other;
		return buf;
	}
	vec2 operator - (vec2 other)
	{
		vec2 buf;
		buf.X = X - other.X;
		buf.Y = Y - other.Y;
		return buf;
	}
	vec2 operator + (vec2 other)
	{
		vec2 buf;
		buf.X = X + other.X;
		buf.Y = Y + other.Y;
		return buf;
	}
	vec2 operator += (vec2 other)
	{
		vec2 buf;
		buf.X = X;
		buf.Y = Y;

		buf.X += other.X;
		buf.Y += other.Y;
		return buf;
	}
	vec2 operator / (float other)
	{
		vec2 buf;
		buf.X /= other;
		buf.Y /= other;
		return buf;
	}
	vec2& operator *= (float other)
	{
		X *= other;
		Y *= other;
		return *this;
	}
	float get_length_sqr(void) const
	{
		float buf;
		buf += (X * X);
		buf += (Y * Y);

		return buf;
	}
};

typedef quat UQuaternion;
typedef vec3 UVector3;
typedef vec2 UVector2;