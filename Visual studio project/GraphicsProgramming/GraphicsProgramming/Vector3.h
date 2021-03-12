// Vector3 class
// Repesents a vector 3 object, storing x, y and z. Provided functions for vector maths and manipulation
// @author Paul Robertson
// Operators added

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>

class Vector3 {

public:
	Vector3(float _x = 0, float _y = 0, float _z = 0);

#pragma region Functions
	Vector3 copy() { return Vector3(x, y, z); }

	void add(const Vector3& _v1, float _scale = 1.0);
	void subtract(const Vector3& _v1, float _scale = 1.0);
	Vector3 invert() { return Vector3(-x, -y, -z); }

	float dot(const Vector3& _v2);
	Vector3 cross(const Vector3& _v2);

	void normalise();
	Vector3 normalised();
	float length();
	float lengthSquared();

	bool equals(const Vector3& _v2, float _epsilon);
	bool equals(const Vector3& _v2);

#pragma region Getters + Setters
	void set(float _x, float _y, float _z);

	float getX() { return x; }
	void setX(float _x) { x = _x; }

	float getY() { return y; }
	void setY(float _y) { y = _y; }

	float getZ() { return z; }
	void setZ(float _z) { z = _z; }
#pragma endregion

#pragma region Operators
	Vector3 operator+(const Vector3& _v2);
	Vector3 operator-(const Vector3& _v2);
	Vector3 operator*(const Vector3& _v2);
	Vector3 operator*(const float& _float);
	Vector3 operator/(const Vector3& _v2);
	Vector3 operator/(const float& _float);

	bool operator==(const Vector3& _v2);
	Vector3& operator+=(const Vector3& _v2);
	Vector3& operator-=(const Vector3& _v2);
	Vector3& operator*=(const Vector3& _v2);
#pragma endregion
#pragma endregion

#pragma region Variables
	float x;
	float y;
	float z;
#pragma endregion
};
#endif