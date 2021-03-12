#include "DefaultCamera.h"

DefaultCamera::DefaultCamera(Input* _input, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Camera::Camera(_input, _static, _position, _rotation, _scale)
{

}

DefaultCamera::~DefaultCamera()
{

}

void DefaultCamera::handleInput(float _deltaTime)
{
	Camera::handleInput(_deltaTime);

	#pragma region Movement
	// Forward
	if (input->isKeyDown('w'))
	{
		addPosition(forward() * moveSpeed * _deltaTime);
	}
	// Backward
	else if (input->isKeyDown('s'))
	{
		addPosition(back() * moveSpeed * _deltaTime);
	}

	// Left
	if (input->isKeyDown('a'))
	{
		addPosition(left() * moveSpeed * _deltaTime);
	}
	// Right
	else if (input->isKeyDown('d'))
	{
		addPosition(right() * moveSpeed * _deltaTime);
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

	#pragma region Rotation
	// If the cursor is visable don't do any rotations
	if (showCursor)
	{
		return;
	}

	int x_Direction = input->getMouseX() - centreX;
	int y_Direction = input->getMouseY() - centreY;
	glutWarpPointer(centreX, centreY);

	// Yaw
	addRotation(Vector3(0, x_Direction * rotationSpeed * _deltaTime, 0));

	// Pitch 
	addRotation(Vector3(-y_Direction * rotationSpeed * _deltaTime, 0, 0));

	#pragma endregion
}

void DefaultCamera::lookAt()
{
	Vector3 target = getPosition() + forward();

	gluLookAt(position.getX(), position.getY(), position.getZ(), target.getX(), target.getY(), target.getZ(), up().getX(), up().getY(), up().getZ());
}