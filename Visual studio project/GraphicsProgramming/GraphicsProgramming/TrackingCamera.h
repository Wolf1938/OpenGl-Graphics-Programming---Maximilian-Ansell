// Tracking Camera
// Will orbit around a target position
// Can become gimble locked when looking straght up or down

#pragma once
#include "Camera.h"
class TrackingCamera :
    public Camera
{
public:
    TrackingCamera(Transform* _target, Input* _input, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    ~TrackingCamera();

#pragma region Functions
    Vector3 forward() override;

    void setTarget(Transform* _target) { target = _target; }
    Transform* getTarget() { return target; }

    void handleInput(float _deltaTime) override;
    void lookAt() override;
#pragma endregion

#pragma region Variables
private:
    Transform* target = nullptr;
    float moveSpeed = 15;
    float rotationSpeed = 1.5f;
#pragma endregion
};