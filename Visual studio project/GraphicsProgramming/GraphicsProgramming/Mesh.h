// Mesh Class
// Only used as a base class to Primitive and LoadedModel

#pragma once
#include "SOIL.h"
#include <stdio.h>

#include "Transform.h"

class Mesh : public Transform
{
public:
	Mesh(GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
	~Mesh();

#pragma region Sub Classes
	// Face Class
	// When the model is loaded or generated each face of the mesh gets a corresponding Face class to track it's attributes
	// Used to calculate edge detection for shadow volumes
	class Face
	{
	public:
		// List of each vert of the shape
		std::vector<Vector3> verts;
		// Average position of all the verts
		Vector3 position;
		// Average normal of all the verts
		Vector3 normal;
	};

	// Edge Class
	// A container for two Vector3s that represent an edge of a shape
	// Used to calculate edge detection for shadow volumes
	class Edge
	{
	public:
		Edge(Vector3 _vert1, Vector3 _vert2) { vert1 = _vert1; vert2 = _vert2; }

		bool operator==(const Edge& _edge2);		

		Vector3 vert1;
		Vector3 vert2;
	};
#pragma endregion

#pragma region Functions
	void update(float _deltaTime) override;
	void render(bool _excludeMesh = false);

	// Scales the UV coordinates
	void setUVScale(float _scale);
	// Custom matric application to manipulate the faces for shadow volume calculations
	void applyMatrix(float _matrix[16]) override;

	// Overiides transformations to matrices are applied to the faces vector
	void setPosition(Vector3 _position) override;
	void setRotation(Vector3 _rotation) override;
	void setScale(Vector3 _scale) override;

#pragma region Getters + Setters
	std::vector<Mesh*>* getChildren() { return &children; }
	Mesh* getChild(int _index) { return children[_index]; }
	void addChild(Mesh* _child);

	bool castShadow() { return castShadows; }
	std::vector<Face*>* getFaces() { generateFaces(); return &faces; }
#pragma endregion

protected:
	// Positions, rotates, and scales the mesh based on the transform's values
	void placeMesh();
	void generateFaces();
#pragma endregion

#pragma region Variables
protected:
	std::vector<GLfloat> verticies;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> textureCOORDs;

	std::vector<Face*> faces;

	std::vector<Mesh*> children;

	GLuint* texture = nullptr;
	int polygon_Layout = GL_TRIANGLES;

	bool castShadows = false;
#pragma endregion
};