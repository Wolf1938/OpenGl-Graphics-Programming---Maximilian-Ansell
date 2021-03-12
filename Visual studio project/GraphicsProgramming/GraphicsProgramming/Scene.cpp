#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input* _in)
{
	// Store pointer for input class
	input = _in;
	initialiseOpenGL();

	// Initialise state machine, all enables/deisables are in one place. func variables are set in initialiseOpenGL();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	// Initialise scene variables	
	#pragma region Cameras
	defaultCamera = new DefaultCamera(_in, false, Vector3(0, 2.5f, 9));
	trackingCamera = new TrackingCamera(sun, _in, false, Vector3(10, 3, 5));
	proceduralCamera = new ProceduralCamera(_in, false, Vector3(1, 1, 1));

	camera = defaultCamera;
	#pragma endregion

	#pragma region Lighting
	lights.push_back(new Light(input, Light::LightType::directional, Colour(0.4f, 0.4f, 0.4f), Colour(0.992f, 0.369f, 0.325f, 1), true, Vector3(0, 100, 50)));
	lights.push_back(new Light(input, Light::LightType::point, Colour(0.2f, 0.2f, 0.2f, 1), Colour(2, 2, 2, 1), true, Vector3(-15, 9, -1)));
	pointLight = new Light(input, Light::LightType::point, Colour(0, 0, 0, 1), Colour(1, 1, 1, 1), false, Vector3(10, 7, 0));
	lights.push_back(pointLight);
	#pragma endregion

	#pragma region Textures
	textures.push_back(loadTexture("gfx/skybox.png"));
	textures.push_back(loadTexture("gfx/Wall_Texture.png"));
	textures.push_back(loadTexture("gfx/Ceiling_Texture.png"));
	textures.push_back(loadTexture("gfx/Floor_Texture.png"));
	textures.push_back(loadTexture("gfx/Divider_Texture.png"));
	textures.push_back(loadTexture("gfx/Display_Case_Texture.png"));
	textures.push_back(loadTexture("gfx/checked.png"));
	textures.push_back(loadTexture("gfx/Table_Texture.png"));
	#pragma endregion

	skyBox = new Primitive::Cube(1, 1, textures[Textures::Skybox], false, true, camera->getPosition());

	#pragma region Room
	// Walls
	meshes.push_back(new LoadedModel("models/Wall_Long.obj", textures[Textures::Wall], false, true, Vector3(0, 7.5f, -23)));
	meshes.push_back(new LoadedModel("models/Wall_Long.obj", textures[Textures::Wall], false, true, Vector3(0, 7.5f, 23), Vector3(0, 180, 0)));
	meshes.push_back(new LoadedModel("models/Wall_Short.obj", textures[Textures::Wall], false, true, Vector3(35, 7.5f, 0), Vector3(0, -90, 0)));
	meshes.push_back(new LoadedModel("models/Wall_Short.obj", textures[Textures::Wall], false, true, Vector3(-35, 7.5f, 0), Vector3(0, 90, 0)));

	// Ceiling
	meshes.push_back(new LoadedModel("models/Ceiling.obj", textures[Textures::Ceiling], false, true, Vector3(0, 15.5f, 0)));

	// Floor
	meshes.push_back(new Primitive::Plane(1, 1, textures[Textures::Floor], false, true, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(72, 1, 48)));
	meshes.back()->setUVScale(3);

	// Divider
	meshes.push_back(new LoadedModel("models/Divider.obj", textures[Textures::Divider], true, true, Vector3(22, 7.5f, 0)));
	#pragma endregion

	#pragma region Display Cases 
	meshes.push_back(new LoadedModel("models/Display_Case.obj", textures[Textures::DisplayCase], true, true, Vector3(-23, 0, -16)));
	meshes.push_back(new Primitive::Plane(5, 5, textures[Textures::Checker], true, false, Vector3(-23, 7, -16), Vector3(25, 0, 0)));
	blendMeshes.push_back(new LoadedModel("models/Display_Case_Top.obj", nullptr, false, true, Vector3(-23, 7, -16)));

	meshes.push_back(new LoadedModel("models/Display_Case.obj", textures[Textures::DisplayCase], true, true, Vector3(-13, 0, -16)));
	meshes.push_back(new Primitive::Cube(5, 5, textures[Textures::Checker], true, true, Vector3(-13, 7, -16), Vector3(0, 20, 0)));
	blendMeshes.push_back(new LoadedModel("models/Display_Case_Top.obj", nullptr, false, true, Vector3(-13, 7, -16)));

	meshes.push_back(new LoadedModel("models/Display_Case.obj", textures[Textures::DisplayCase], true, true, Vector3(-3, 0, -16)));
	meshes.push_back(new Primitive::Disk(20, textures[Textures::Checker], true, true, Vector3(-3, 7, -16), Vector3(25, 0, 0)));
	blendMeshes.push_back(new LoadedModel("models/Display_Case_Top.obj", nullptr, false, true, Vector3(-3, 7, -16)));

	meshes.push_back(new LoadedModel("models/Display_Case.obj", textures[Textures::DisplayCase], true, true, Vector3(7, 0, -16)));
	meshes.push_back(new Primitive::Cylinder(5, 20, textures[Textures::Checker], true, true, Vector3(7, 7, -16), Vector3(0, 0, 0), Vector3(0.5f, 1, 0.5f)));
	blendMeshes.push_back(new LoadedModel("models/Display_Case_Top.obj", nullptr, false, true, Vector3(7, 7, -16)));

	meshes.push_back(new LoadedModel("models/Display_Case.obj", textures[Textures::DisplayCase], true, true, Vector3(7, 0, 16)));
	meshes.push_back(new Primitive::Sphere(10, textures[Textures::Checker], true, true, Vector3(7, 7, 16)));
	blendMeshes.push_back(new LoadedModel("models/Display_Case_Top.obj", nullptr, false, true, Vector3(7, 7, 16)));

	meshes.push_back(new LoadedModel("models/Display_Case.obj", textures[Textures::DisplayCase], true, true, Vector3(-3, 0, 16)));
	meshes.push_back(new Primitive::Cone(20, textures[Textures::Checker], true, true, Vector3(-3, 7, 16)));
	blendMeshes.push_back(new LoadedModel("models/Display_Case_Top.obj", nullptr, false, true, Vector3(-3, 7, 16)));

	meshes.push_back(new LoadedModel("models/Display_Case.obj", textures[Textures::DisplayCase], true, true, Vector3(-13, 0, 16)));
	meshes.push_back(new Primitive::Cone(4, textures[Textures::Checker], true, true, Vector3(-13, 7, 16)));
	blendMeshes.push_back(new LoadedModel("models/Display_Case_Top.obj", nullptr, false, true, Vector3(-13, 7, 16)));

	meshes.push_back(new LoadedModel("models/Display_Case.obj", textures[Textures::DisplayCase], true, true, Vector3(-23, 0, 16)));
	meshes.push_back(new Primitive::Torus(20, 20, textures[Textures::Checker], true, true, Vector3(-23, 7, 16), Vector3(30, 0, 0)));
	blendMeshes.push_back(new LoadedModel("models/Display_Case_Top.obj", nullptr, false, true, Vector3(-23, 7, 16)));
	#pragma endregion

	#pragma region Table 
	meshes.push_back(new LoadedModel("models/Table.obj", textures[Textures::Table], true, true, Vector3(-8, 0, 0)));
	blendMeshes.push_back(new LoadedModel("models/Table_Top.obj", nullptr, false, true, Vector3(-8, 3, 0)));

	sun = new Primitive::Sphere(10, textures[Textures::Checker], true, true, Vector3(-8, 4, 0));
	meshes.push_back(sun);

	sun->addChild(new Primitive::EmptyTransform());
	sun->getChild(0)->addChild(new Primitive::Sphere(10, textures[Textures::Checker], false, false, Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0.1f, 0.1f, 0.1f)));

	sun->addChild(new Primitive::EmptyTransform());
	sun->getChild(1)->addChild(new Primitive::Sphere(10, textures[Textures::Checker], false, false, Vector3(0, 0, 1.25f), Vector3(0, 0, 0), Vector3(0.25f, 0.25f, 0.25f)));

	sun->addChild(new Primitive::EmptyTransform());
	sun->getChild(2)->addChild(new Primitive::Sphere(10, textures[Textures::Checker], false, false, Vector3(0, 0, 1.75f), Vector3(0, 0, 0), Vector3(0.25f, 0.25f, 0.25f)));

	sun->addChild(new Primitive::EmptyTransform());
	sun->getChild(3)->addChild(new Primitive::Sphere(10, textures[Textures::Checker], false, false, Vector3(0, 0, 2.25f), Vector3(0, 0, 0), Vector3(0.2f, 0.2f, 0.2f)));

	sun->addChild(new Primitive::EmptyTransform());
	sun->getChild(4)->addChild(new Primitive::Sphere(10, textures[Textures::Checker], false, false, Vector3(0, 0, 2.75f), Vector3(0, 0, 0), Vector3(0.5f, 0.5f, 0.5f)));

	sun->addChild(new Primitive::EmptyTransform());
	sun->getChild(5)->addChild(new Primitive::Sphere(10, textures[Textures::Checker], false, false, Vector3(0, 0, 4.25f), Vector3(0, 0, 0), Vector3(0.5f, 0.5f, 0.5f)));

	sun->addChild(new Primitive::EmptyTransform());
	sun->getChild(6)->addChild(new Primitive::Sphere(10, textures[Textures::Checker], false, false, Vector3(0, 0, 5.0f), Vector3(0, 0, 0), Vector3(0.35f, 0.35f, 0.35f)));

	sun->addChild(new Primitive::EmptyTransform());
	sun->getChild(7)->addChild(new Primitive::Sphere(10, textures[Textures::Checker], false, false, Vector3(0, 0, 5.75f), Vector3(0, 0, 0), Vector3(0.35f, 0.35f, 0.35f)));

	trackingCamera->setTarget(sun->getChild(5)->getChild(0));

	// Apply a random rotation to each planet rotation
	for (unsigned int planet = 0; planet < 8; planet++)
	{
		sun->getChild(planet)->addRotation(Vector3(0, rand() % 360, 0));
	}
	#pragma endregion

	#pragma region Mirrors 
	reflectiveSurfaces.push_back(new Primitive::Plane(1, 1, nullptr, false, true, Vector3(-34.99f, 7.5f, 0), Vector3(0, 0, -90), Vector3(10, 1, 8)));
	reflectiveSurfaces.push_back(new Primitive::Plane(1, 1, nullptr, false, true, Vector3(-34.99f, 7.5f, 13), Vector3(0, 0, -90), Vector3(10, 1, 8)));
	reflectiveSurfaces.push_back(new Primitive::Plane(1, 1, nullptr, false, true, Vector3(-34.99f, 7.5f, -13), Vector3(0, 0, -90), Vector3(10, 1, 8)));
	#pragma endregion

	#pragma region Shadows 
	for (unsigned int light = 1; light < lights.size(); light++)
	{
		lights[light]->buildShadowVolumes(&meshes);
	}
	#pragma endregion
}
Scene::~Scene()
{
	for (unsigned int mesh = 0; mesh < meshes.size(); mesh++)	{
		delete(meshes[mesh]);
	}

	for (unsigned int texture = 0; texture < textures.size(); texture++) {
		delete(textures[texture]);
	}

	for (unsigned int light = 0; light < lights.size(); light++) {
		delete(lights[light]);
	}

	delete(defaultCamera);
	delete(trackingCamera);
	delete(proceduralCamera);
	delete(skyBox);
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);				// Grey Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer

	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glCullFace(GL_BACK);

	// Vertex array settings
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Scene::handleInput(float _deltaTime)
{
	if (input->isKeyDown(32))
	{
		input->setKeyUp(32);

		cameraIndex = cameraIndex < 2 ? cameraIndex + 1 : 0;

		switch (cameraIndex)
		{
		case 0:
			camera = defaultCamera;
			break;
		case 1:
			camera = trackingCamera;
			break;
		case 2:
			camera = proceduralCamera;
			break;
		}
	}

	// Handle user input
	camera->handleInput(_deltaTime);
	pointLight->handleInput(_deltaTime);	
}

void Scene::update(float _deltaTime)
{
	// update scene related variables.
	camera->update(_deltaTime);
	skyBox->setPosition(camera->getPosition());

	for (unsigned int planet = 0; planet < 8; planet++)
	{
		sun->getChild(planet)->addRotation(Vector3(0, (40 - 4 * (planet + 1)) * _deltaTime, 0));
	}

	for (unsigned int mesh = 0; mesh < meshes.size(); mesh++)
	{
		meshes[mesh]->update(_deltaTime);		
	}

	for (unsigned int light = 1; light < lights.size(); light++)
	{
		// If a light is not static
		if (!lights[light]->isStatic())
		{			
			// If the light has moved
			if (lights[light]->hasMoved())
			{
				// Re calculate shadows for that light
				lights[light]->buildShadowVolumes(&meshes);
			}

			lights[light]->update(_deltaTime);
		}
	}

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render()
{
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	camera->lookAt();

	// Render geometry/scene here -------------------------------------
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	skyBox->render();
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	for (unsigned int light = 1; light < lights.size(); light++) {
		lights[light]->render();
	}

	// Build lighting
	for (unsigned int light = 0; light < lights.size(); light++) {
		lights[light]->buildLight(light);
	}

	// Reflective surfaes
	renderMirroredMeshes();

	//renderMeshes();
	renderScene();

	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

//	Multiple Light Shadow Volumes
//
//	OpenGL (unkown) 'Multiple Light Sources'
//	https://www.opengl.org/archives/resources/code/samples/advanced/advanced97/notes/node103.html#SECTION000114210000000000000
//	[Accessed 18 December 2020].

void Scene::renderScene()
{
	// Render all meshes to depth buffer then disabel depth write.
	renderMeshes();

	// Disable write to colour buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);

	// For each light
	for (unsigned int light = 0; light < lights.size(); light++)
	{
		// Get all the volumes that the light casts
		std::vector<ShadowVolume*>* volumes = lights[light]->getShadowVolumes();

		// For each of those volumes depth pass
		for (unsigned int volume = 0; volume < volumes->size(); volume++)
		{
			depthPass(light, (*volumes)[volume]);
		}

		// If Shadow volumes are set to render
		if (camera->showShadowVolumes())
		{
			// Render them
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glDisable(GL_STENCIL_TEST);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			lights[light]->renderShadowVolumes();

			glPolygonMode(GL_FRONT_AND_BACK, camera->polygonMode());
			glEnable(GL_STENCIL_TEST);
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		}
	}

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glDisable(GL_STENCIL_TEST);

	renderTranslucentMeshes();
}

void Scene::renderMirroredMeshes()
{
	glDisable(GL_LIGHTING);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	for (unsigned int mirror = 0; mirror < reflectiveSurfaces.size(); mirror++) {
		reflectiveSurfaces[mirror]->render();
	}

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glPushMatrix();
		glTranslatef(reflectiveSurfaces[0]->getPosition().getX() * 2, 0, 0);
		glScalef(-1, 1, 1);
		renderMeshes();
		renderTranslucentMeshes();
	glPopMatrix();

	glClear(GL_STENCIL_BUFFER_BIT);
	glDisable(GL_STENCIL_TEST);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glColor4f(0.8f, 0.8f, 1.0f, 0.6f);

	for (unsigned int mirror = 0; mirror < reflectiveSurfaces.size(); mirror++) {
		reflectiveSurfaces[mirror]->render();
	}
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

void Scene::renderMeshes(Mesh* _excludeMesh)
{
	for (unsigned int mesh = 0; mesh < meshes.size(); mesh++)
	{
		meshes[mesh]->render(meshes[mesh] == _excludeMesh);		
	}
}

void Scene::depthPass(int _light, ShadowVolume* _shadowVolume)
{
	glClear(GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 0, 0);

	// Render shadow volumes ++
	glCullFace(GL_BACK);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

	_shadowVolume->render();

	// Render shadow volumes --
	glCullFace(GL_FRONT);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);

	_shadowVolume->render();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glStencilFunc(GL_EQUAL, 1, 1);

	// Use stencil buffer to render each mesh in shadow
	glDisable(GL_LIGHT0 + _light);
	renderMeshes(_shadowVolume->getMesh());

	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
}

void Scene::renderTranslucentMeshes()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glColor4f(0.9f, 0.9f, 1.0f, 0.3f);
	for (unsigned int mesh = 0; mesh < blendMeshes.size(); mesh++)
	{
		blendMeshes[mesh]->render();
	}
}

GLuint* Scene::loadTexture(char* _textureName)
{
	GLuint* texture = new GLuint();

	*texture = SOIL_load_OGL_texture
	(
		_textureName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	return  texture;
}

void Scene::resize(int w, int h) 
{
	window_Width = w;
	window_Height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	defaultCamera->setCentre(window_Width / 2, window_Height / 2);
	trackingCamera->setCentre(window_Width / 2, window_Height / 2);
	proceduralCamera->setCentre(window_Width / 2, window_Height / 2);

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 150.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / ((double)time - timebase));
		timebase = time;
		frame = 0;
	}
}

void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)window_Width / (float)window_Height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}