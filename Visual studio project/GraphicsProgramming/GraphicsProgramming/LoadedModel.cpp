// Loaded Model Class


// Below ifdef required to remove warnings for unsafe version of fopen and fscanf.
// Secure version won't work cross-platform, forcing this small hack.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "LoadedModel.h"

LoadedModel::LoadedModel(char* _modelName, GLuint* _texture, bool _castShadows, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Mesh::Mesh(_texture, _castShadows, _static, _position, _rotation, _scale)
{
	if (!loadModel(_modelName))
	{
		MessageBox(NULL, "Model failed to load", "Error", MB_OK);
	}
}

LoadedModel::~LoadedModel()
{

}

bool LoadedModel::loadModel(char* _modelName)
{
	std::vector<Vector3> Verts;
	std::vector<Vector3> Norms;
	std::vector<Vector3> TexCs;
	std::vector<unsigned int> faces;

	FILE* file = fopen(_modelName, "r");
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				Verts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				TexCs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				Norms.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
					&face[0], &face[1], &face[2],
					&face[3], &face[4], &face[5],
					&face[6], &face[7], &face[8]);

				if (matches != 9)
				{
					// Parser error, or not triangles
					return false;
				}

				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}
			}
		}
	}

#pragma region unroll_data
	for (unsigned int vert = 0; vert < faces.size(); vert += 3)
	{
		verticies.push_back(Verts[faces[vert] - 1].getX());
		verticies.push_back(Verts[faces[vert] - 1].getY());
		verticies.push_back(Verts[faces[vert] - 1].getZ());

		textureCOORDs.push_back(TexCs[faces[vert + 1] - 1].getX());
		textureCOORDs.push_back(TexCs[faces[vert + 1] - 1].getY());
		textureCOORDs.push_back(0);

		normals.push_back(Norms[faces[vert + 2] - 1].getX());
		normals.push_back(Norms[faces[vert + 2] - 1].getY());
		normals.push_back(Norms[faces[vert + 2] - 1].getZ());
	}
#pragma endregion unroll_data

	polygon_Layout = GL_TRIANGLES;

	// Once data has been sorted, clear read data (which has been copied and are not longer needed).
	Verts.clear();
	Norms.clear();
	TexCs.clear();
	faces.clear();

	return true;
}