// DefaultCamera Class
// Used WASD to move forward, back, left, and right
// Q and E for up and down
// Mouse input to Yaw and pitch.

#pragma once
#include "Camera.h"
class DefaultCamera :
    public Camera
{
public:
    DefaultCamera(Input* _input, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    ~DefaultCamera();

#pragma region Functions
    void handleInput(float _deltaTime) override;
    void lookAt() override;
#pragma endregion

#pragma region Variables
private:
    float moveSpeed = 15;
    float rotationSpeed = 1.5f;
#pragma endregion
};

