// Shadoow Class
// Is derived from mesh so it can be rendered
// Given a lights position and a mesh it will calculate the shadow volume that mesh casts using edge detection and extrusion
// Saves a pointer to the mesh that casts the volume so that mesh can be excluded from it's own shadow

#pragma once
#include "Mesh.h"

class ShadowVolume : public Mesh
{
public:
	ShadowVolume(GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));

#pragma region Functions	
	// Uses the lights postion and the mesh to calcualte the shadow volume
	void buildShadowVolume(Vector3 _lightPosition, Mesh* _mesh, float _extrusion = 5.0f);

	// Return the mesh that is casting the volume
	Mesh* getMesh() { return mesh; }
private:
	// Used to calcualte if an edge is a contour edge
	bool containsEdge(std::vector<Mesh::Edge*>* _edges, Mesh::Edge* _edge);
#pragma endregion

#pragma region Variables
private:
	Mesh* mesh = nullptr;
#pragma endregion
};