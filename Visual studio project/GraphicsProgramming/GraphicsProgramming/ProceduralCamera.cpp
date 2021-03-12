#include "ProceduralCamera.h"

ProceduralCamera::ProceduralCamera(Input* _input, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Camera::Camera(_input, _static, _position, _rotation, _scale)
{
	sequences.push_back(new Sequence(Vector3(-25, 10, -8), Vector3(9, 10, -8), Vector3(0, -0.5f, -1)));
	sequences.push_back(new Sequence(Vector3(9, 10, 8), Vector3(-25, 10, 8), Vector3(0, -0.5f, 1)));
	sequences.push_back(new Sequence(Vector3(20, 13, 18), Vector3(20, 13, -18), Vector3(-1, -0.5f, 0)));

	setPosition(sequences[sequenceIndex]->startPosisiton);
}

ProceduralCamera::~ProceduralCamera()
{
	for (unsigned int sequence = 0; sequence < sequences.size(); sequence++)
	{
		delete(sequences[sequence]);
	}
}

ProceduralCamera::Sequence::Sequence(Vector3 _startPosisiton, Vector3 _endPosition, Vector3 _direction)
{
	startPosisiton = _startPosisiton;
	endPosition = _endPosition;
	direction = _direction.normalised();
}

Vector3 ProceduralCamera::forward()
{
	return sequences[sequenceIndex]->direction;
}

void ProceduralCamera::update(float _deltaTime)
{
	Vector3 direction = sequences[sequenceIndex]->endPosition - position;

	if (direction.length() > 0.1f)
	{
		Transform::addPosition(direction.normalised() * moveSpeed * _deltaTime);
	}
	else
	{
		sequenceIndex = sequenceIndex < sequences.size() - 1 ? sequenceIndex + 1 : 0;
		setPosition(sequences[sequenceIndex]->startPosisiton);
	}
}

void ProceduralCamera::lookAt()
{		
	Vector3 target = position + forward();
	gluLookAt(position.getX(), position.getY(), position.getZ(), target.getX(), target.getY(), target.getZ(), up().getX(), up().getY(), up().getZ());
}