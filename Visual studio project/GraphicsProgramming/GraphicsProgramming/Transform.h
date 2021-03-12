// Transform Class
// Stores 3 Vector3s that represent position, rotation, and scale. NOTE: In hierarchical modeling these are in relation to the parent
// Has utility functionality that enables movement, rotation, and scaling
// Also calcualtes direction vectors

#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include <vector>
#include "Vector3.h"

class Transform
{
public:
	Transform(bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));

#pragma region Functions
	// Called each frame, overriden by derived classes Light, Camera, and Mesh
	virtual void update(float _deltaTime);
	// Custom matrix application for manipulting the shadow volume calculations into worldspace
	virtual void applyMatrix(float _matrix[16]);
	
#pragma region Getters + Setters
	bool isStatic() { return static_Transform; }
	bool hasMoved() { return !(position == lastPosition && rotation == lastRotation); }

	Transform* getParent() { return parent; }
	void setParent(Transform* _parent) { parent = _parent; }

	Vector3 getPosition() { return position; }
	virtual void setPosition(Vector3 _position) { position = _position; }
	virtual void addPosition(Vector3 _vector) { setPosition(position + _vector); }

	Vector3 getRotation() { return rotation; }
	virtual void setRotation(Vector3 _rotation) { rotation = _rotation; }
	void addRotation(Vector3 _rotation) { setRotation(Vector3(rotation + _rotation)); }

	Vector3 getScale() { return scale; }
	virtual void setScale(Vector3 _Scale) { scale = _Scale; }

	virtual Vector3 forward();
	Vector3 back() { return forward().invert(); }

	Vector3 up();
	Vector3 down() { return up().invert(); }

	Vector3 right() { return forward().cross(up()); }
	Vector3 left() { return right().invert(); }
#pragma endregion

private:
	float cos(float _rotation) { return cosf(_rotation * 3.14159f / 180.0f); }
	float sin(float _rotation) { return sinf(_rotation * 3.14159f / 180.0f); }
#pragma endregion

#pragma region Variables
protected:
	bool static_Transform = true;

	Vector3 position = Vector3(0, 0, 0);
	Vector3 rotation = Vector3(0, 0, 0);
	Vector3 scale = Vector3(1, 1, 1);

	Transform* parent = nullptr;

private:
	Vector3 lastPosition = Vector3(0, 0, 0);
	Vector3 lastRotation = Vector3(0, 0, 0);
#pragma endregion
};