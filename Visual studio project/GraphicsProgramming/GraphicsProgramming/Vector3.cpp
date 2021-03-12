#include "Vector3.h"

Vector3::Vector3(float _x, float _y, float _z) {
	set(_x, _y, _z);
}

bool Vector3::equals(const Vector3& v2, float _epsilon) {
	return ((fabsf(this->x - v2.x) < _epsilon) &&
		(fabsf(this->y - v2.y) < _epsilon) &&
		(fabsf(this->z - v2.z) < _epsilon));
}

bool Vector3::equals(const Vector3& _v2)
{
	return equals(_v2, 0.00001f);
}

float Vector3::length() {
	return (float)sqrt(this->lengthSquared());
}

float Vector3::lengthSquared() {
	return (
		x * x +
		y * y +
		z * z
		);
}

void Vector3::normalise() {
	float mag = length();
	if (mag) {
		float multiplier = 1.0f / mag;
		x *= multiplier;
		y *= multiplier;
		z *= multiplier;
	}
}

Vector3 Vector3::normalised()
{
	Vector3 norm(x, y, z);
	norm.normalise();
	return norm;
}

Vector3 Vector3::cross(const Vector3& _v2) {
	Vector3 cross(
		(y * _v2.z - z * _v2.y),
		(z * _v2.x - x * _v2.z),
		(x * _v2.y - y * _v2.x)
		);
	return cross;
}

void Vector3::subtract(const Vector3& _v1, float scale) {
	x -= (_v1.x*scale);
	y -= (_v1.y*scale);
	z -= (_v1.z*scale);
}

void Vector3::set(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

float Vector3::dot(const Vector3& _v2) {
	return (x * _v2.x +
			y * _v2.y +
			z * _v2.z
			);
}

void Vector3::add(const Vector3& _v1, float _scale) {
	x += (_v1.x * _scale);
	y += (_v1.y * _scale);
	z += (_v1.z * _scale);
}

Vector3 Vector3::operator+(const Vector3& _v2) {
	return Vector3(x + _v2.x, y + _v2.y, z + _v2.z);
}

Vector3 Vector3::operator-(const Vector3& _v2) {
	return Vector3(x - _v2.x, y - _v2.y, z - _v2.z);
}

Vector3 Vector3::operator*(const Vector3& _v2) {
	return Vector3(x * _v2.x, y * _v2.y, z * _v2.z);
}

Vector3 Vector3::operator*(const float& _float) {
	return Vector3(x * _float, y * _float, z * _float);
}

Vector3 Vector3::operator/(const Vector3& _v2) {
	return Vector3(x / _v2.x, y / _v2.y, z / _v2.z);
}

Vector3 Vector3::operator/(const float& _float) {
	return Vector3(x / _float, y / _float, z / _float);
}

bool Vector3::operator==(const Vector3& _v2)
{
	if (x == _v2.x && y == _v2.y && z == _v2.z)
	{
		return true;
	}
	return false;
}

Vector3& Vector3::operator+=(const Vector3& _v2) {
	x += _v2.x;
	y += _v2.y;
	z += _v2.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& _v2) {
	x -= _v2.x;
	y -= _v2.y;
	z -= _v2.z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& _v2) {
	x *= _v2.x;
	y *= _v2.y;
	z *= _v2.z;
	return *this;
}