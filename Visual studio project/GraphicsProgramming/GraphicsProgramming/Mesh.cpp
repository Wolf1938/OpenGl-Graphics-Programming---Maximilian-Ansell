#include "Mesh.h"

Mesh::Mesh(GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Transform::Transform(_static, _position, _rotation, _scale)
{
	texture = _texture;
	castShadows = _castShadows;
}

Mesh::~Mesh()
{
	for (unsigned int child = 0; child < children.size(); child++)
	{
		delete(children[child]);
	}

	for (unsigned int face = 0; face < faces.size(); face++)
	{
		delete(faces[face]);
	}
}

bool Mesh::Edge::operator==(const Edge& _edge2)
{
	if ((vert1 == _edge2.vert1 && vert2 == _edge2.vert2) || (vert1 == _edge2.vert2 && vert2 == _edge2.vert1))
	{
		return true;
	}

	return false;
}

void Mesh::setPosition(Vector3 _position)
{
	if (verticies.size() == 0)
	{
		position = _position;
		return;
	}

	// Move to origin
	float translate1[16] = {
	1,			0,			0,			0,
	0,			1,			0,			0,
	0,			0,			1,			0,
	-position.x,-position.y,-position.z,1
	};
	applyMatrix(translate1);

	position = _position;

	// Move to position
	float translate2[16] = {
	1,		    0,		    0,		    0,
	0,			1,			0,		    0,
	0,			0,			1,		    0,
	position.x, position.y, position.z, 1
	};
	applyMatrix(translate2);
}

void Mesh::setRotation(Vector3 _rotation)
{
	if (verticies.size() == 0)
	{
		rotation = _rotation;
		return;
	}

	// Move to origin
	float translate1[16] = {
	1,			0,			0,			0,
	0,			1,			0,			0,
	0,			0,			1,			0,
	-position.x,-position.y,-position.z,1
	};
	applyMatrix(translate1);

	// Rotate
	float rotateZ1[16] = {
		cosf(-rotation.z),		sinf(-rotation.z),		0,		0,
		-sinf(-rotation.z),		cosf(-rotation.z),		0,		0,
		0,						0,						1,		0,
		0,						0,						0,		1
	};
	applyMatrix(rotateZ1);

	float rotateY1[16] = {
		cosf(-rotation.y),		0,		-sinf(-rotation.y),		0,
		0,						1,		0,						0,
		sinf(-rotation.y),		0,		cosf(-rotation.y),		0,
		0,						0,		0,						1
	};
	applyMatrix(rotateY1);

	float rotateX1[16] = {
		1,		0,						0,					0,
		0,		cosf(-rotation.x),		sinf(-rotation.x),	0,
		0,		-sinf(-rotation.x),		cosf(-rotation.x),	0,
		0,		0,						0,					1
	};
	applyMatrix(rotateX1);

	rotation = _rotation;

	// Rotate
	float rotateX2[16] = {
		1,		0,						0,					0,
		0,		cosf(rotation.x),		sinf(rotation.x),	0,
		0,		-sinf(rotation.x),		cosf(rotation.x),	0,
		0,		0,						0,					1
	};
	applyMatrix(rotateX2);

	float rotateY2[16] = {
		cosf(rotation.y),		0,		-sinf(rotation.y),		0,
		0,						1,		0,						0,
		sinf(rotation.y),		0,		cosf(rotation.y),		0,
		0,						0,		0,						1
	};
	applyMatrix(rotateY2);

	float rotateZ2[16] = {
		cosf(rotation.z),		sinf(rotation.z),		0,		0,
		-sinf(rotation.z),		cosf(rotation.z),		0,		0,
		0,						0,						1,		0,
		0,						0,						0,		1
	};
	applyMatrix(rotateZ2);

	// Move to position
	float translate2[16] = {
	1,			0,			0,			0,
	0,			1,			0,			0,
	0,			0,			1,			0,
	position.x,	position.y,	position.z,	1
	};
}

void Mesh::setScale(Vector3 _scale)
{
	if (verticies.size() == 0)
	{
		scale = _scale;
		return;
	}

	// Move to origin
	float translate1[16] = {
	1,			0,			0,			0,
	0,			1,			0,			0,
	0,			0,			1,			0,
	-position.x,-position.y,-position.z,1
	};
	applyMatrix(translate1);

	// Scale to 1
	float scalar1[16] = {
	1.0f / scale.x,		0,					0,					0,
	0,					1.0f / scale.y,		0,					0,
	0,					0,					1.0f / scale.z,		0,
	0,					0,					0,					1
	};
	applyMatrix(scalar1);

	scale = _scale;

	// Scale
	float scalar2[16] = {
	scale.x, 0,		  0,	   0,
	0,		 scale.y, 0,	   0,
	0,		 0,		  scale.z, 0,
	0,		 0,		  0,	   1
	};
	applyMatrix(scalar2);

	// Move to position
	float translate2[16] = {
	1,			0,			0,			0,
	0,			1,			0,			0,
	0,			0,			1,			0,
	position.x,	position.y,	position.z,	1
	};
	applyMatrix(translate2);
}

void Mesh::setUVScale(float _scale)
{
	for (unsigned int vert = 0; vert < textureCOORDs.size(); vert ++)
	{
		textureCOORDs[vert] *= _scale;
	}
}

void Mesh::applyMatrix(float _matrix[16])
{
	for (unsigned int face = 0; face < faces.size(); face++)
	{
		for (unsigned int vert = 0; vert < faces[face]->verts.size(); vert++)
		{
			Vector3 vertex = faces[face]->verts[vert];

			Vector3 transformation = Vector3
			(
				vertex.getX() * _matrix[0] + vertex.getY() * _matrix[4] + vertex.getZ() * _matrix[8] + _matrix[12],
				vertex.getX() * _matrix[1] + vertex.getY() * _matrix[5] + vertex.getZ() * _matrix[9] + _matrix[13],
				vertex.getX() * _matrix[2] + vertex.getY() * _matrix[6] + vertex.getZ() * _matrix[10] + _matrix[14]
			);

			float scale = vertex.getX() * _matrix[3] + vertex.getY() * _matrix[7] + vertex.getZ() * _matrix[11] + _matrix[15];
			faces[face]->verts[vert] = transformation / scale;
		}
	}
}

void Mesh::generateFaces()
{
	for (unsigned int face = 0; face < faces.size(); face++)
	{
		delete(faces[face]);
	}

	faces.clear();

	if (polygon_Layout == GL_TRIANGLES)
	{
		for (unsigned int vert = 0; vert < verticies.size(); vert += 9)
		{
			Face* face = new Face();

			face->verts.insert(face->verts.end(), {
				Vector3(verticies[vert], verticies[vert + 1], verticies[vert + 2]),
				Vector3(verticies[vert + 3], verticies[vert + 4], verticies[vert + 5]),
				Vector3(verticies[vert + 6], verticies[vert + 7], verticies[vert + 8])
				});

			faces.push_back(face);
		}
	}
	else if (polygon_Layout == GL_QUADS)
	{
		for (unsigned int vert = 0; vert < verticies.size(); vert += 12)
		{
			Face* face = new Face();

			face->verts.insert(face->verts.end(), {
				Vector3(verticies[vert], verticies[vert + 1], verticies[vert + 2]),
				Vector3(verticies[vert + 3], verticies[vert + 4], verticies[vert + 5]),
				Vector3(verticies[vert + 6], verticies[vert + 7], verticies[vert + 8]),
				Vector3(verticies[vert + 9], verticies[vert + 10], verticies[vert + 11])
				});

			faces.push_back(face);
		}
	}

	Vector3 rotate = rotation;
	rotate = rotate / 180.0f * 3.14159;

	// Rotate
	float rotateX[16] = {
		1,		0,					0,						0,
		0,		cosf(rotate.x),		sinf(rotate.x),			0,
		0,		-sinf(rotate.x),	cosf(rotate.x),			0,
		0,		0,					0,						1
	};
	applyMatrix(rotateX);

	float rotateY[16] = {
		cosf(rotate.y),		0,		-sinf(rotate.y),	0,
		0,					1,		0,					0,
		sinf(rotate.y),		0,		cosf(rotate.y),		0,
		0,					0,		0,					1
	};
	applyMatrix(rotateY);

	float rotateZ[16] = {
		cosf(rotate.z),		sinf(rotate.z),		0,		0,
		-sinf(rotate.z),	cosf(rotate.z),		0,		0,
		0,					0,					1,		0,
		0,					0,					0,		1
	};
	applyMatrix(rotateZ);

	// Scale
	float scalar[16] = {
	scale.x,	0,				0,				0,
	0,			scale.y,		0,				0,
	0,			0,				scale.z,		0,
	0,			0,				0,				1
	};
	applyMatrix(scalar);

	// Move to position
	float translate[16] = {
	1,					0,					0,			0,
	0,					1,					0,			0,
	0,					0,					1,			0,
	position.x,			position.y,			position.z,	1
	};
	applyMatrix(translate);

	for (int face = 0; face < faces.size(); face++)
	{
		// Average position
		faces[face]->position = (faces[face]->verts[0] + faces[face]->verts[1] + faces[face]->verts[2]) / 3.0f;

		faces[face]->normal = (faces[face]->verts[1] - faces[face]->verts[0]).cross(faces[face]->verts[2] - faces[face]->verts[0]);
	}
}

void Mesh::update(float _deltaTime)
{

}

void Mesh::render(bool _excludeMesh)
{
	glPushMatrix();

		placeMesh();

		if (verticies.size() && !_excludeMesh)
		{
			// If there is a texture applied then bind it
			if (texture) 
			{ 
				glBindTexture(GL_TEXTURE_2D, *texture);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, NULL);
			}

			glVertexPointer(3, GL_FLOAT, 0, &verticies[0]);
			glNormalPointer(GL_FLOAT, 0, &normals[0]);
			glTexCoordPointer(3, GL_FLOAT, 0, &textureCOORDs[0]);

			glDrawArrays(polygon_Layout, 0, verticies.size() / 3);
		}

		// Render the children before pop matrix is called
		for (unsigned int child = 0; child < children.size(); child++)
		{
			children[child]->render();
		}

	glPopMatrix();
}

void Mesh::placeMesh()
{
	glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ()); // Move

	glRotatef(getRotation().getX(), 1, 0, 0);	glRotatef(getRotation().getY(), 0, 1, 0);	glRotatef(getRotation().getZ(), 0, 0, 1); // Rotate

	glScalef(getScale().getX(), getScale().getY(), getScale().getZ()); // Scale
}

void Mesh::addChild(Mesh* _child)
{
	_child->setParent(this);
	 children.push_back(_child);
}