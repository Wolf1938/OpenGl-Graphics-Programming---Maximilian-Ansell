#include "Primitive.h"
Primitive::Primitive()
{

}

Primitive::~Primitive()
{

}

Primitive::Plane::Plane(int _hSubdivisions, int _vSubdivisions, GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	float horizontalStep = 1.0f / (float)_hSubdivisions;
	float verticalStep = 1.0f / (float)_vSubdivisions;

	for (int y = 0; y < _hSubdivisions; y++)
	{
		for (int x = 0; x < _vSubdivisions; x++)
		{
			verticies.insert(verticies.end(), {
				-0.5f + verticalStep * x, 0.0f, -0.5f + horizontalStep * y,
				-0.5f + verticalStep * x, 0.0f, -0.5f + horizontalStep * (y + 1),
				-0.5f + verticalStep * (x + 1),  0.0f, -0.5f + horizontalStep * (y + 1),
				-0.5f + verticalStep * (x + 1),  0.0f, -0.5f + horizontalStep * y
				});

			normals.insert(normals.end(), {
				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f
				});

			textureCOORDs.insert(textureCOORDs.end(), {
				verticalStep * x, -horizontalStep * y, 0.0f,
				verticalStep * x, -horizontalStep * (y + 1), 0.0f,
				verticalStep * (x + 1), -horizontalStep * (y + 1), 0.0f,
				verticalStep * (x + 1), -horizontalStep * y, 0.0f,
				});
		}
	}

	verticies.insert(verticies.end(), {
		-0.5f, -0.01f, 0.5f,
		-0.5f, -0.01f, -0.5f,
		0.5f,  -0.01f, -0.5f,
		0.5f,  -0.01f, 0.5f
		});

	normals.insert(normals.end(), {
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
		});

	textureCOORDs.insert(textureCOORDs.end(), {
		0, 1, 0.0f,
		0, 0, 0.0f,
		1, 0, 0.0f,
		1, 1, 0.0f
		});

	polygon_Layout = GL_QUADS;
}

Primitive::Cube::Cube(int _hSubdivisions, int _vSubdivisions, GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	float horizontalStep = 1.0f / (float)_vSubdivisions;
	float verticalStep = 1.0f / (float)_hSubdivisions;

	for (int x = 0; x < _vSubdivisions; x++)
	{
		for (int y = 0; y < _vSubdivisions; y++)
		{
			// Top
			verticies.insert(verticies.end(), {
				-0.5f + horizontalStep * x,			0.5f,	-0.5f + horizontalStep * y,
				-0.5f + horizontalStep * x,			0.5f,	-0.5f + horizontalStep * (y + 1),
				-0.5f + horizontalStep * (x + 1),	0.5f,	-0.5f + horizontalStep * (y + 1),
				-0.5f + horizontalStep * (x + 1),	0.5f,	-0.5f + horizontalStep * y
				});
			normals.insert(normals.end(), {
				0, 1, 0,
				0, 1, 0,
				0, 1, 0,
				0, 1, 0
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				horizontalStep * x / 4.0f + 0.75f,			-horizontalStep * y / 4.0f,			0.0f,
				horizontalStep * x / 4.0f + 0.75f,			-horizontalStep * (y + 1) / 4.0f,	0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.75f,	-horizontalStep * (y + 1) / 4.0f,	0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.75f,	-horizontalStep * y / 4.0f,			0.0f
				});

			// Bottom
			verticies.insert(verticies.end(), {
				-0.5f + horizontalStep * x,			-0.5f,	-0.5f + horizontalStep * y,
				-0.5f + horizontalStep * (x + 1),	-0.5f,	-0.5f + horizontalStep * y,
				-0.5f + horizontalStep * (x + 1),	-0.5f,	-0.5f + horizontalStep * (y + 1),
				-0.5f + horizontalStep * x,			-0.5f,	-0.5f + horizontalStep * (y + 1)
				});
			normals.insert(normals.end(), {
				0, -1, 0,
				0, -1, 0,
				0, -1, 0,
				0, -1, 0
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				horizontalStep * x / 4.0f + 0.75f,			-horizontalStep * y / 4.0f + 0.5f,			0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.75f,	-horizontalStep * y / 4.0f + 0.5f,			0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.75f,	-horizontalStep * (y + 1) / 4.0f + 0.5f,	0.0f,
				horizontalStep * x / 4.0f + 0.75f,			-horizontalStep * (y + 1) / 4.0f + 0.5f,	0.0f
				});
		}

		for (int y = 0; y < _hSubdivisions; y++)
		{
			// Front
			verticies.insert(verticies.end(), {
				-0.5f + horizontalStep * x,			0.5f - verticalStep * y,		0.5f,
				-0.5f + horizontalStep * x,			0.5f - verticalStep * (y + 1),	0.5f,
				-0.5f + horizontalStep * (x + 1),	0.5f - verticalStep * (y + 1),	0.5f,
				-0.5f + horizontalStep * (x + 1),	0.5f - verticalStep * y,		0.5f
				});
			normals.insert(normals.end(), {
				0, 0, 1,
				0, 0, 1,
				0, 0, 1,
				0, 0, 1,
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				horizontalStep * x / 4.0f + 0.25f,			-verticalStep * y / 4.0f - 0.25f,			0.0f,
				horizontalStep * x / 4.0f + 0.25f,			-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.25f,	-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.25f,	-verticalStep * y / 4.0f - 0.25f,			0.0f
				});

			// Back
			verticies.insert(verticies.end(), {
				-0.5f + horizontalStep * x,			0.5f - verticalStep * y,			-0.5f,
				-0.5f + horizontalStep * (x + 1),	0.5f - verticalStep * y,			-0.5f,
				-0.5f + horizontalStep * (x + 1),	0.5f - verticalStep * (y + 1),		-0.5f,
				-0.5f + horizontalStep * x,			0.5f - verticalStep * (y + 1),		-0.5f
				});
			normals.insert(normals.end(), {
				0, 0, -1,
				0, 0, -1,
				0, 0, -1,
				0, 0, -1,
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				-horizontalStep * x / 4.0f,			-verticalStep * y / 4.0f - 0.25f,			0.0f,
				-horizontalStep * (x + 1) / 4.0f,	-verticalStep * y / 4.0f - 0.25f,			0.0f,
				-horizontalStep * (x + 1) / 4.0f,	-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				-horizontalStep * x / 4.0f,			-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f
				});

			// Left
			verticies.insert(verticies.end(), {
				-0.5f,	0.5f - verticalStep * y,		-0.5f + horizontalStep * x,
				-0.5f,	0.5f - verticalStep * (y + 1),	-0.5f + horizontalStep * x,
				-0.5f,	0.5f - verticalStep * (y + 1),	-0.5f + horizontalStep * (x + 1),
				-0.5f,	0.5f - verticalStep * y,		-0.5f + horizontalStep * (x + 1)
				});
			normals.insert(normals.end(), {
				-1, 0, 0,
				-1, 0, 0,
				-1, 0, 0,
				-1, 0, 0,
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				horizontalStep * x / 4.0f,			-verticalStep * y / 4.0f - 0.25f,			0.0f,
				horizontalStep * x / 4.0f,			-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				horizontalStep * (x + 1) / 4.0f,	-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				horizontalStep * (x + 1) / 4.0f,	-verticalStep * y / 4.0f - 0.25f,			0.0f
				});

			// Right
			verticies.insert(verticies.end(), {
				0.5f,	0.5f - verticalStep * y,		-0.5f + horizontalStep * x,
				0.5f,	0.5f - verticalStep * y,		-0.5f + horizontalStep * (x + 1),
				0.5f,	0.5f - verticalStep * (y + 1),	-0.5f + horizontalStep * (x + 1),
				0.5f,	0.5f - verticalStep * (y + 1),	-0.5f + horizontalStep * x
				});
			normals.insert(normals.end(), {
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				1, 0, 0,
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				-horizontalStep * x / 4.0f - 0.25f,			-verticalStep * y / 4.0f - 0.25f,			0.0f,
				-horizontalStep * (x + 1) / 4.0f - 0.25f,		-verticalStep * y / 4.0f - 0.25f,			0.0f,
				-horizontalStep * (x + 1) / 4.0f - 0.25f,		-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				-horizontalStep * x / 4.0f - 0.25f,			-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f
				});
		}
	}

	polygon_Layout = GL_QUADS;
}

Primitive::Sphere::Sphere(int _segments, GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	float horizontalStep = 1.0f / (float)_segments;
	float verticalStep = 1.0f / (float)_segments;

	for (int x = 0; x < _segments; x++)
	{
		for (int y = 0; y < _segments; y++)
		{
			// Top
			verticies.insert(verticies.end(), {
				-0.5f + horizontalStep * x,			0.5f,	-0.5f + horizontalStep * y,
				-0.5f + horizontalStep * x,			0.5f,	-0.5f + horizontalStep * (y + 1),
				-0.5f + horizontalStep * (x + 1),	0.5f,	-0.5f + horizontalStep * (y + 1),
				-0.5f + horizontalStep * (x + 1),	0.5f,	-0.5f + horizontalStep * y
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				horizontalStep * x / 4.0f + 0.75f,			-horizontalStep * y / 4.0f,			0.0f,
				horizontalStep * x / 4.0f + 0.75f,			-horizontalStep * (y + 1) / 4.0f,	0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.75f,	-horizontalStep * (y + 1) / 4.0f,	0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.75f,	-horizontalStep * y / 4.0f,			0.0f
				});

			// Bottom
			verticies.insert(verticies.end(), {
				-0.5f + horizontalStep * x,			-0.5f,	-0.5f + horizontalStep * y,
				-0.5f + horizontalStep * (x + 1),	-0.5f,	-0.5f + horizontalStep * y,
				-0.5f + horizontalStep * (x + 1),	-0.5f,	-0.5f + horizontalStep * (y + 1),
				-0.5f + horizontalStep * x,			-0.5f,	-0.5f + horizontalStep * (y + 1)
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				horizontalStep * x / 4.0f + 0.75f,			-horizontalStep * y / 4.0f + 0.5f,			0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.75f,	-horizontalStep * y / 4.0f + 0.5f,			0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.75f,	-horizontalStep * (y + 1) / 4.0f + 0.5f,	0.0f,
				horizontalStep * x / 4.0f + 0.75f,			-horizontalStep * (y + 1) / 4.0f + 0.5f,	0.0f
				});

			// Front
			verticies.insert(verticies.end(), {
				-0.5f + horizontalStep * x,			0.5f - verticalStep * y,		0.5f,
				-0.5f + horizontalStep * x,			0.5f - verticalStep * (y + 1),	0.5f,
				-0.5f + horizontalStep * (x + 1),	0.5f - verticalStep * (y + 1),	0.5f,
				-0.5f + horizontalStep * (x + 1),	0.5f - verticalStep * y,		0.5f
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				horizontalStep * x / 4.0f + 0.25f,			-verticalStep * y / 4.0f - 0.25f,			0.0f,
				horizontalStep * x / 4.0f + 0.25f,			-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.25f,	-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				horizontalStep * (x + 1) / 4.0f + 0.25f,	-verticalStep * y / 4.0f - 0.25f,			0.0f
				});

			// Back
			verticies.insert(verticies.end(), {
				-0.5f + horizontalStep * x,			0.5f - verticalStep * y,			-0.5f,
				-0.5f + horizontalStep * (x + 1),	0.5f - verticalStep * y,			-0.5f,
				-0.5f + horizontalStep * (x + 1),	0.5f - verticalStep * (y + 1),		-0.5f,
				-0.5f + horizontalStep * x,			0.5f - verticalStep * (y + 1),		-0.5f
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				-horizontalStep * x / 4.0f,			-verticalStep * y / 4.0f - 0.25f,			0.0f,
				-horizontalStep * (x + 1) / 4.0f,	-verticalStep * y / 4.0f - 0.25f,			0.0f,
				-horizontalStep * (x + 1) / 4.0f,	-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				-horizontalStep * x / 4.0f,			-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f
				});

			// Left
			verticies.insert(verticies.end(), {
				-0.5f,	0.5f - verticalStep * y,		-0.5f + horizontalStep * x,
				-0.5f,	0.5f - verticalStep * (y + 1),	-0.5f + horizontalStep * x,
				-0.5f,	0.5f - verticalStep * (y + 1),	-0.5f + horizontalStep * (x + 1),
				-0.5f,	0.5f - verticalStep * y,		-0.5f + horizontalStep * (x + 1)
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				horizontalStep * x / 4.0f,			-verticalStep * y / 4.0f - 0.25f,			0.0f,
				horizontalStep * x / 4.0f,			-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				horizontalStep * (x + 1) / 4.0f,	-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				horizontalStep * (x + 1) / 4.0f,	-verticalStep * y / 4.0f - 0.25f,			0.0f
				});

			// Right
			verticies.insert(verticies.end(), {
				0.5f,	0.5f - verticalStep * y,		-0.5f + horizontalStep * x,
				0.5f,	0.5f - verticalStep * y,		-0.5f + horizontalStep * (x + 1),
				0.5f,	0.5f - verticalStep * (y + 1),	-0.5f + horizontalStep * (x + 1),
				0.5f,	0.5f - verticalStep * (y + 1),	-0.5f + horizontalStep * x
				});
			textureCOORDs.insert(textureCOORDs.end(), {
				-horizontalStep * x / 4.0f - 0.25f,			-verticalStep * y / 4.0f - 0.25f,			0.0f,
				-horizontalStep * (x + 1) / 4.0f - 0.25f,		-verticalStep * y / 4.0f - 0.25f,			0.0f,
				-horizontalStep * (x + 1) / 4.0f - 0.25f,		-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f,
				-horizontalStep * x / 4.0f - 0.25f,			-verticalStep * (y + 1) / 4.0f - 0.25f,		0.0f
				});
		}
	}

	polygon_Layout = GL_QUADS;

	for (unsigned int vert = 0; vert < verticies.size(); vert += 3)
	{
		Vector3 vertex = Vector3(verticies[vert], verticies[vert + 1], verticies[vert + 2]);
		vertex.normalise();

		normals.insert(normals.end(), { vertex.getX(), vertex.getY(), vertex.getZ() });

		// Make sure it's a unit sphere
		vertex = vertex / 2.0f;

		verticies[vert] = vertex.getX();
		verticies[vert + 1] = vertex.getY();
		verticies[vert + 2] = vertex.getZ();
	}

	setUVScale(2);
	polygon_Layout = GL_QUADS;
}

Primitive::Disk::Disk(int _segments, GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	float theta = 2 * PI / (float)_segments;

	for (int i = 0; i < _segments; i++)
	{
		// Top Tri
		verticies.insert(verticies.end(), {
			0,						0,	0,
			sinf(theta * i),		0,	cosf(theta * i),
			sinf(theta * (i + 1)),	0,	cosf(theta * (i + 1))
			});

		normals.insert(normals.end(), {
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			});

		textureCOORDs.insert(textureCOORDs.end(), {
			0.5f,									0.5f,									0,
			(sinf(-theta * i) / 2) + 0.5f,			(cosf(-theta * i) / 2) + 0.5f,			0,
			(sinf(-theta * (i + 1)) / 2) + 0.5f,	(cosf(-theta * (i + 1)) / 2) + 0.5f,	0
			});

		// Bottom Tri
		verticies.insert(verticies.end(), {
			0,						-0.01f,		0,
			sinf(theta * (i + 1)),	-0.01f,		cosf(theta * (i + 1)),
			sinf(theta * i),		-0.01f,		cosf(theta * i)
			});

		normals.insert(normals.end(), {
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			});

		textureCOORDs.insert(textureCOORDs.end(), {
			0.5f,									0.5f,									0,
			(sinf(-theta * (i + 1)) / 2) + 0.5f,	(cosf(-theta * (i + 1)) / 2) + 0.5f,	0,
			(sinf(-theta * i) / 2) + 0.5f,			(cosf(-theta * i) / 2) + 0.5f,			0
			});
	}

	polygon_Layout = GL_TRIANGLES;
}

Primitive::Cylinder::Cylinder(int _hSubdivisions, int _vSubdivisions, GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	float theta = 2 * PI / (float)_vSubdivisions;
	float delta = 1.0f / (float)_hSubdivisions;
	float yOffset = 0.5f;

	for (float x = 0; x < _vSubdivisions; x++)
	{
		// Top tri
		verticies.insert(verticies.end(), {
			0,						0.5f,	0,
			sinf(theta * x),		0.5f,	cosf(theta * x),
			sinf(theta * (x + 1)),	0.5f,	cosf(theta * (x + 1))
			});

		normals.insert(normals.end(), {
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
			});

		textureCOORDs.insert(textureCOORDs.end(), {
			0.5f,									0.5f,									0,
			(sinf(-theta * x) / 2) / 4 + 0.5f,			(cosf(-theta * x) / 2) / 4 + 0.5f,			0,
			(sinf(-theta * (x + 1)) / 2) / 4 + 0.5f,	(cosf(-theta * (x + 1)) / 2) / 4 + 0.5f,	0
			});

		// Cylnder
		for (float y = 0; y < _hSubdivisions; y++)
		{
			verticies.insert(verticies.end(), {
				cosf(theta * x),		(delta * (y + 1)) - yOffset,	sinf(theta * x),
				cosf(theta * (x + 1)),	(delta * (y + 1)) - yOffset,	sinf(theta * (x + 1)),
				cosf(theta * (x + 1)),	(delta * y) - yOffset,			sinf(theta * (x + 1)),
				});

			normals.insert(normals.end(), {
				cosf(theta * x),		0,	sinf(theta * x),
				cosf(theta * (x + 1)),	0,	sinf(theta * (x + 1)),
				cosf(theta * (x + 1)),	0,	sinf(theta * (x + 1)),
				});

			textureCOORDs.insert(textureCOORDs.end(), {
				(1.0f / _vSubdivisions) * x,		-(1.0f / _hSubdivisions) * (y + 1) / 2,	0,
				(1.0f / _vSubdivisions) * (x + 1),	-(1.0f / _hSubdivisions) * (y + 1) / 2, 0,
				(1.0f / _vSubdivisions) * (x + 1),	-(1.0f / _hSubdivisions) * y / 2,		0,
				});

			verticies.insert(verticies.end(), {
				cosf(theta * x),		(delta * (y + 1)) - yOffset,	sinf(theta * x),
				cosf(theta * (x + 1)),	(delta * y) - yOffset,			sinf(theta * (x + 1)),
				cosf(theta * x),		(delta * y) - yOffset,			sinf(theta * x)
				});

			normals.insert(normals.end(), {
				cosf(theta * x),		0,	sinf(theta * x),
				cosf(theta * (x + 1)),	0,	sinf(theta * (x + 1)),
				cosf(theta * x),		0,	sinf(theta * x)
				});

			textureCOORDs.insert(textureCOORDs.end(), {
				(1.0f / _vSubdivisions) * x,		-(1.0f / _hSubdivisions) * (y + 1) / 2,	0,
				(1.0f / _vSubdivisions) * (x + 1),	-(1.0f / _hSubdivisions) * y / 2,		0,
				(1.0f / _vSubdivisions) * x,		-(1.0f / _hSubdivisions) * y / 2,		0
				});
		}

		// Bottom tri
		verticies.insert(verticies.end(), {
			0,						-0.5f,	0,
			sinf(theta * (x + 1)),	-0.5f,	cosf(theta * (x + 1)),
			sinf(theta * x),		-0.5f,	cosf(theta * x)
			});

		normals.insert(normals.end(), {
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f
			});

		textureCOORDs.insert(textureCOORDs.end(), {
			0.5f,									0.5f,											0,
			(sinf(-theta * (x + 1)) / 2) / 4 + 0.5f,	(cosf(-theta * (x + 1)) / 2) / 4 + 0.5f,	0,
			(sinf(-theta * x) / 2) / 4 + 0.5f,			(cosf(-theta * x) / 2) / 4 + 0.5f,			0
			});
	}

	polygon_Layout = GL_TRIANGLES;
}

Primitive::Cone::Cone(int _vSubdivisions, GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	float theta = 2 * PI / (float)_vSubdivisions;

	for (float i = 0; i < _vSubdivisions; i++)
	{
		Vector3 Vert1 = Vector3(0, 0.5f, 0);
		Vector3 Vert2 = Vector3(sinf(theta * i), -0.5f, cosf(theta * i));
		Vector3 Vert3 = Vector3(sinf(theta * (i + 1)), -0.5f, cosf(theta * (i + 1)));

		// Side Tri
		verticies.insert(verticies.end(), {
			Vert1.x, Vert1.y, Vert1.z,
			Vert2.x, Vert2.y, Vert2.z,
			Vert3.x, Vert3.y, Vert3.z
			});

		Vector3 normal = (Vert2 - Vert1).cross(Vert3 - Vert1);

		normals.insert(normals.end(), {
			normal.x, normal.y, normal.z,
			normal.x, normal.y, normal.z,
			normal.x, normal.y, normal.z
			});

		textureCOORDs.insert(textureCOORDs.end(), {
			0.5f,									0.5f,									0,
			(sinf(-theta * i) / 2) + 0.5f,			(cosf(-theta * i) / 2) + 0.5f,			0,
			(sinf(-theta * (i + 1)) / 2) + 0.5f,	(cosf(-theta * (i + 1)) / 2) + 0.5f,	0
			});

		Vert1 = Vector3(0, -0.5f, 0);

		// Bottom Tri
		verticies.insert(verticies.end(), {
			Vert1.x, Vert1.y, Vert1.z,
			Vert3.x, Vert3.y, Vert3.z,
			Vert2.x, Vert2.y, Vert2.z
			});

		normals.insert(normals.end(), {
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			});

		textureCOORDs.insert(textureCOORDs.end(), {
			0.5f,									0.5f,									0,
			(sinf(-theta * (i + 1)) / 2) + 0.5f,	(cosf(-theta * (i + 1)) / 2) + 0.5f,	0,
			(sinf(-theta * i) / 2) + 0.5f,			(cosf(-theta * i) / 2) + 0.5f,			0
			});
	}

	polygon_Layout = GL_TRIANGLES;
}

Primitive::Torus::Torus(int _hSubdivisions, int _vSubdivisions, GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	float outerRadius = 0.5f;
	float innerRadius = 0.25f;
	float theta = 2 * PI / (float)_vSubdivisions;
	float delta = 2 * PI / (float)_hSubdivisions;

	for (float y = 0; y < _vSubdivisions; y++)
	{
		Vector3 point1 = Vector3(sinf(theta * y), cosf(theta * y), 0.0f);
		Vector3 point2 = Vector3(sinf(theta * (y + 1)), cosf(theta * (y + 1)), 0.0f);

		for (float x = 0; x < _hSubdivisions; x++)
		{
			Vector3 vert1 = Vector3(
				(outerRadius + innerRadius * cosf(x * delta)) * cosf(theta * y),
				(outerRadius + innerRadius * cosf(x * delta)) * sinf(theta * y),
				innerRadius * sinf(x * delta)
			);

			Vector3 vert2 = Vector3(
				(outerRadius + innerRadius * cosf(x * delta)) * cosf(theta * (y+1)),
				(outerRadius + innerRadius * cosf(x * delta)) * sinf(theta * (y+1)),
				innerRadius * sinf(x * delta)
			);

			Vector3 vert3 = Vector3(
				(outerRadius + innerRadius * cosf((x+1) * delta)) * cosf(theta * (y + 1)),
				(outerRadius + innerRadius * cosf((x+1) * delta)) * sinf(theta * (y + 1)),
				innerRadius * sinf((x+1) * delta)
			);

			Vector3 vert4 = Vector3(
				(outerRadius + innerRadius * cosf((x + 1) * delta)) * cosf(theta * y),
				(outerRadius + innerRadius * cosf((x + 1) * delta)) * sinf(theta * y),
				innerRadius * sinf((x+1) * delta)
			);

			verticies.insert(verticies.end(), {
				vert1.x,vert1.y,vert1.z,
				vert2.x,vert2.y,vert2.z,
				vert3.x,vert3.y,vert3.z,
				vert4.x,vert4.y,vert4.z,
				});

			vert1 = (vert1 - point1).normalised();
			vert2 = (vert2 - point1).normalised();
			vert3 = (vert3 - point2).normalised();
			vert4 = (vert4 - point2).normalised();

			normals.insert(normals.end(), {
				vert1.x,vert1.y,vert1.z,
				vert2.x,vert2.y,vert2.z,
				vert3.x,vert3.y,vert3.z,
				vert4.x,vert4.y,vert4.z,
				});

			textureCOORDs.insert(textureCOORDs.end(), {
				(1.0f / _vSubdivisions) * x,		-(1.0f / _hSubdivisions) * y,		0,
				(1.0f / _vSubdivisions) * x,		-(1.0f / _hSubdivisions) * (y + 1),	0,
				(1.0f / _vSubdivisions) * (x + 1),	-(1.0f / _hSubdivisions) * (y + 1), 0,
				(1.0f / _vSubdivisions) * (x + 1),	-(1.0f / _hSubdivisions) * y,		0,
				});
		}
	}

	polygon_Layout = GL_QUADS;
}