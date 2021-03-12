// ProceduralCamera Class
// Will translate through the scene on set trajectories

#pragma once
#include "Camera.h"
class ProceduralCamera :
    public Camera
{
public:
    ProceduralCamera(Input* _input, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    ~ProceduralCamera();

    class Sequence
    {
    public:
        Sequence(Vector3 _startPosisiton, Vector3 _endPosition, Vector3 _direction);

        Vector3 startPosisiton;
        Vector3 endPosition;
        Vector3 direction;
    };

#pragma region Functions
    Vector3 forward() override;

    void update(float _deltaTime) override;
    void lookAt() override;
#pragma endregion

#pragma region Variables
private:
    int sequenceIndex = 0;
    std::vector<Sequence*> sequences;

    float moveSpeed = 5;
#pragma endregion
};