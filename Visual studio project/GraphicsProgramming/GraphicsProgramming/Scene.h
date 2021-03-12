// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Includes, openGL includes are in the mesh base class
#include "DefaultCamera.h"
#include "TrackingCamera.h"
#include "proceduralCamera.h"

#include "Light.h"
#include "LoadedModel.h"
#include "Primitive.h"

class Scene{

public:
	Scene(Input *in);
	~Scene();

#pragma region Functions
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Main render function
	void render();

	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

private:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Will load a texture and retrun a pointer to it
	GLuint* loadTexture(char* _textureName);

	// Calculates FPS
	void calculateFPS();
	// A function to collate all text output in a single location
	void renderTextOutput();
	// Renders text to screen. Must be called last in render function (before swap buffers)
	void displayText(float x, float y, float r, float g, float b, char* string);

	// Renders the scene with shadows
	void renderScene();
	// Renders all the meshes
	void renderMeshes(Mesh* _excludeMesh = nullptr);
	// Renders all the mirrors in the scene
	void renderMirroredMeshes();
	// Renders shadow Volumes using depth pass (volumes aren't capped so depth fail won't work)
	void depthPass(int _light, ShadowVolume* _shadowVolume);
	// Renders all the mirrors in the scene
	void renderTranslucentMeshes();
#pragma endregion

#pragma region Variables
	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int window_Width, window_Height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	Camera* camera = nullptr;
	DefaultCamera* defaultCamera = nullptr;
	TrackingCamera* trackingCamera = nullptr;
	ProceduralCamera* proceduralCamera = nullptr;
	int cameraIndex = 0;

	Mesh* skyBox;

	std::vector<Light*> lights;
	Light* pointLight = nullptr;

	// A list that stores all loaded textures, makes sure each texture is loaded once
	std::vector<GLuint*> textures;
	enum Textures { Skybox, Wall, Ceiling, Floor, Divider, DisplayCase, Checker, Table };

	std::vector<Mesh*> meshes;
	std::vector<Mesh*> blendMeshes;
	Mesh* sun = nullptr;

	std::vector<Primitive::Plane*> reflectiveSurfaces;
#pragma endregion
};
#endif