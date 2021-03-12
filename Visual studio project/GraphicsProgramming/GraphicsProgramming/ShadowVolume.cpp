#include "ShadowVolume.h"

ShadowVolume::ShadowVolume(GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	polygon_Layout = GL_QUADS;
}

//	Edge detection shadow volume pseudo code
//
//	John Tsiombikas (unkown) 'Volume Shadows Tutorial'
//	nuclear.mutantstargoat.com/articles/volume_shadows_tutorial_nuclear.pdf
//	[Accessed 08 December 2020].

void ShadowVolume::buildShadowVolume(Vector3 _lightPosition, Mesh* _mesh, float _extrusion)
{
	mesh = _mesh;

	// Clear previous shadow volume
	verticies.clear();
	normals.clear();
	textureCOORDs.clear();

	std::vector<Mesh::Edge*> outline;

	std::vector<Mesh::Face*> faces = *_mesh->getFaces();

	// For each face
	for (unsigned int face = 0; face < faces.size(); face++)
	{
		Vector3 lightDirection = faces[face]->position - _lightPosition;
		lightDirection.normalise();

		// If the face is pointing away from the light scource
		if (lightDirection.dot(faces[face]->normal) > 0.0f)
		{
			// For each edge
			for (unsigned int vert = 0; vert < faces[face]->verts.size(); vert++)
			{
				Vector3 vert1 = faces[face]->verts[vert];
				Vector3 vert2 = vert < faces[face]->verts.size() - 1 ? faces[face]->verts[vert + 1] : faces[face]->verts[0];

				Mesh::Edge* newEdge = new Mesh::Edge(vert1, vert2);

				// If the edge is already in the outline edge list then it can't be a contour edge since it is
				// referenced by two triangles that are facing away from the light
				if (!containsEdge(&outline, newEdge))
				{
					outline.push_back(newEdge);
				}
			}
		}
	}	

	for (unsigned int edge = 0; edge < outline.size(); edge++)
	{
		Vector3 vert3 = outline[edge]->vert2 + (outline[edge]->vert2 - _lightPosition) * _extrusion;
		Vector3 vert4 = outline[edge]->vert1 + (outline[edge]->vert1 - _lightPosition) * _extrusion;

		verticies.insert(verticies.end(), {
			outline[edge]->vert1.getX(), outline[edge]->vert1.getY(), outline[edge]->vert1.getZ(),
			outline[edge]->vert2.getX(), outline[edge]->vert2.getY(), outline[edge]->vert2.getZ(),
			vert3.getX(), vert3.getY(), vert3.getZ(),
			vert4.getX(), vert4.getY(), vert4.getZ()
			});

		normals.insert(normals.end(), {
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
			});

		textureCOORDs.insert(textureCOORDs.end(), {
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
			});
	}

	for (unsigned int edge = 0; edge < outline.size(); edge++)
	{
		delete outline[edge];
	}
}

bool ShadowVolume::containsEdge(std::vector<Mesh::Edge*>* _edges, Mesh::Edge* _edge)
{
	for (unsigned int edge = 0; edge < _edges->size(); edge++)
	{
		if (*(*_edges)[edge] == *_edge)
		{
			delete(_edge);
			delete((*_edges)[edge]);

			_edges->erase(_edges->begin() + edge);
			return true;
		}
	}
	
	return false;
}