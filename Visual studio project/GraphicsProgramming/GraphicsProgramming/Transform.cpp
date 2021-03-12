#include "Transform.h"

Transform::Transform(bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
{
	static_Transform = _static;

	setPosition(_position);
	setRotation(_rotation);
	setScale(_scale);
}

void Transform::update(float _deltaTime)
{
	if (!static_Transform)
	{
		lastPosition = position;
		lastRotation = rotation;
	}
}

void Transform::applyMatrix(float _matrix[16])
{
	Vector3 transformation = Vector3
	(
		position.getX() * _matrix[0] + position.getY() * _matrix[4] + position.getZ() * _matrix[8] + _matrix[12],
		position.getX() * _matrix[1] + position.getY() * _matrix[5] + position.getZ() * _matrix[9] + _matrix[13],
		position.getX() * _matrix[2] + position.getY() * _matrix[6] + position.getZ() * _matrix[10] + _matrix[14]
	);

	float scale = position.getX() * _matrix[3] + position.getY() * _matrix[7] + position.getZ() * _matrix[11] + _matrix[15];

	transformation.setX(transformation.getX() / scale);
	transformation.setY(transformation.getY() / scale);
	transformation.setZ(transformation.getZ() / scale);

	setPosition(transformation);
}

Vector3 Transform::forward()
{
	return Vector3(
		sin(getRotation().getY()) * cos(getRotation().getX()),
		sin(getRotation().getX()),
		cos(getRotation().getX()) * -cos(getRotation().getY())
	);
}

Vector3 Transform::up()
{
	return Vector3(
		-cos(getRotation().getY()) * sin(getRotation().getZ()) - sin(getRotation().getY()) * sin(getRotation().getX()) * cos(getRotation().getZ()),
		cos(getRotation().getX()) * cos(getRotation().getZ()),
		-sin(getRotation().getY()) * sin(getRotation().getZ()) - sin(getRotation().getX()) * cos(getRotation().getZ()) * -cos(getRotation().getY())
	);
}