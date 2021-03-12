#include "TrackingCamera.h"

TrackingCamera::TrackingCamera(Transform* _target, Input* _input, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Camera::Camera(_input, _static, _position, _rotation, _scale)
{
	target = _target;
}

TrackingCamera::~TrackingCamera()
{

}

Vector3 TrackingCamera::forward()
{
	return target->getPosition() - position;
}

void TrackingCamera::handleInput(float _deltaTime)
{
	Camera::handleInput(_deltaTime);

	#pragma region Movement
	// Forward
	if (input->isKeyDown('w'))
	{
		addPosition(forward() * rotationSpeed * _deltaTime);
	}
	// Backward
	else if (input->isKeyDown('s'))
	{
		addPosition(back() * rotationSpeed * _deltaTime);
	}

	// Left
	if (input->isKeyDown('a'))
	{
		addPosition(left() * rotationSpeed * _deltaTime);
	}
	// Right
	else if (input->isKeyDown('d'))
	{
		addPosition(right() * rotationSpeed * _deltaTime);
	}

	// Up
	if (input->isKeyDown('e'))
	{
		addPosition(up() * moveSpeed * _deltaTime);
	}
	// Down
	else if (input->isKeyDown('q'))
	{
		addPosition(down() * moveSpeed * _deltaTime);
	}
	#pragma endregion
}

void TrackingCamera::lookAt()
{
	gluLookAt(position.getX(), position.getY(), position.getZ(), target->getPosition().getX(), target->getPosition().getY(), target->getPosition().getZ(), up().getX(), up().getY(), up().getZ());
}