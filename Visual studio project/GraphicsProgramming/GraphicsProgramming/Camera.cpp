#include "Camera.h"

Camera::Camera(Input* _input, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale) 
	: Transform::Transform(_static, _position, _rotation, _scale)
{
	input = _input;
}

Camera::~Camera()
{

}

void Camera::addPosition(Vector3 _vector)
{
	Transform::addPosition(_vector);

	// Limit X
	if (getPosition().getX() > 22.5f)	{
		setPosition(Vector3(22.5f, getPosition().getY(), getPosition().getZ()));
	}
	else if (getPosition().getX() < -22.5f)	{
		setPosition(Vector3(-22.5f, getPosition().getY(), getPosition().getZ()));
	}

	// Limit Y
	if (getPosition().getY() > 16) {
		setPosition(Vector3(getPosition().getX(), 16, getPosition().getZ()));
	}
	else if (getPosition().getY() < 0.5f) {
		setPosition(Vector3(getPosition().getX(), 0.5f, getPosition().getZ()));
	}

	// Limit Z
	if (getPosition().getZ() > 22.5f) {
		setPosition(Vector3(getPosition().getX(), getPosition().getY(), 22.5f));
	}
	else if (getPosition().getZ() < -22.5f) {
		setPosition(Vector3(getPosition().getX(), getPosition().getY(), -22.5f));
	}
}

void Camera::handleInput(float _deltaTime)
{
	// Show Cursor
	if (input->isKeyDown('f'))
	{
		input->setKeyUp('f');

		glutSetCursor(showCursor ? GLUT_CURSOR_NONE : GLUT_CURSOR_LEFT_ARROW);
		showCursor = !showCursor;
	}

	if (input->isMouseLDown())
	{
		input->setMouseLDown(false);
		if (showCursor)
		{
			showCursor = false;
			glutSetCursor(GLUT_CURSOR_NONE);
		}
	}

	// Wireframe
	if (input->isKeyDown('r'))
	{
		input->setKeyUp('r');

		wireFrame = !wireFrame;

		if (wireFrame) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_TEXTURE_2D);
		}
	}

	//Show shadow volumes
	if (input->isKeyDown('t'))
	{
		input->setKeyUp('t');
		shadowVolmes = !shadowVolmes;
	}
}