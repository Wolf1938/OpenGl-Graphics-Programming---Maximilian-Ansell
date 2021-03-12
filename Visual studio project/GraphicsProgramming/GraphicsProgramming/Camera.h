// Default Camera Class
// Inherits from transform so has a position, rotation, and scale
// Expands from transform to add user inputs for movement and rotation

#pragma once
#include "Transform.h"
#include "Input.h"

class Camera : public Transform
{
public:
	Camera(Input* _input, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
	~Camera();

#pragma region Functions
	void addPosition(Vector3 _vector) override;
	void setCentre(int _centre_X, int _centre_Y) { centreX = _centre_X; centreY = _centre_Y; }

	virtual void handleInput(float _deltaTime);

	// Converts camera transfrom vector3s into GLfloats
	virtual void lookAt() {};

	int polygonMode() { return wireFrame ? GL_LINE : GL_FILL; }
	bool showShadowVolumes() { return shadowVolmes; }
#pragma endregion

#pragma region Variables
protected:
	Input* input;
	int centreX = 0;
	int centreY = 0;
	bool showCursor = false;

private:
	bool wireFrame = false;
	bool shadowVolmes = false;
#pragma endregion
};