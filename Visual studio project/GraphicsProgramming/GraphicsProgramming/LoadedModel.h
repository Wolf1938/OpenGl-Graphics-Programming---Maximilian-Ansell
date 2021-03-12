// Loaded Model Class

#pragma once
#include "Mesh.h"

class LoadedModel : public Mesh
{
public:
	LoadedModel(char* _modelName, GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
	~LoadedModel();

private:
	bool loadModel(char* _modelName);
};

