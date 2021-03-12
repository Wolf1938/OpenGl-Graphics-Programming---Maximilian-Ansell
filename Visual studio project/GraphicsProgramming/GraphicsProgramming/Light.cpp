#include "Light.h"

Light::Light(Input* _input, LightType _lightType, Colour _ambient, Colour _diffuse, bool _static, Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: Transform::Transform(_static, _position, _rotation, _scale)
{
	input = _input;
	light_Type = _lightType;

	setAmbient(_ambient);
	setDiffuse(_diffuse);
	setPosition(_position);
	light_Position[3] = light_Type == LightType::directional ? 0.0f : 1.0f;

	mesh = new Primitive::Cube(1, 1, nullptr, false, false, _position, Vector3(0, 0, 0), Vector3(0.1f, 0.1f, 0.1f));
}

Light::~Light()
{
	for (unsigned int volume = 0; volume < shadowVolumes.size(); volume++)
	{
		delete(shadowVolumes[volume]);
	}
}

void Light::buildShadowVolumes(std::vector<Mesh*>* _meshes)
{
	// Clear old volumes
	for (unsigned int volume = 0; volume < shadowVolumes.size(); volume++)
	{
		delete(shadowVolumes[volume]);
	}

	shadowVolumes.clear();

	// For each mesh
	for (unsigned int mesh = 0; mesh < _meshes->size(); mesh++)
	{
		// If the mesh casts shadow
		if ((*_meshes)[mesh]->castShadow())
		{
			// Calculate the shadow volume
			ShadowVolume* volume = new ShadowVolume();

			volume->buildShadowVolume(position, (*_meshes)[mesh]);
			shadowVolumes.push_back(volume);
		}
	}
}

void Light::renderShadowVolumes()
{
	for (unsigned int volume = 0; volume < shadowVolumes.size(); volume++)
	{
		shadowVolumes[volume]->render();
	}
}	

void Light::buildLight(int _lightIndex)
{
	int lightIndex = GL_LIGHT0 + _lightIndex;

	glLightfv(lightIndex, GL_AMBIENT, light_Ambient);
	glLightfv(lightIndex, GL_DIFFUSE, light_Diffuse);
	glLightfv(lightIndex, GL_SPECULAR, light_Specular);
	glLightfv(lightIndex, GL_POSITION, light_Position);

	if (light_Type == LightType::spot)
	{
		glLightfv(lightIndex, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(lightIndex, GL_SPOT_CUTOFF, spot_CutOff);
		glLightf(lightIndex, GL_SPOT_EXPONENT, spot_Exponent);
	}

	if (light_Type != LightType::directional)
	{
		glLightf(lightIndex, GL_CONSTANT_ATTENUATION, constant_Attenuation);
		glLightf(lightIndex, GL_LINEAR_ATTENUATION, linear_Attenuation);
		glLightf(lightIndex, GL_QUADRATIC_ATTENUATION, quadratic_Attenuation);
	}

	glEnable(GL_LIGHT0 + _lightIndex);
}

void Light::handleInput(float _deltaTime)
{
	#pragma region Movement
	// Forward
	if (input->isKeyDown('i'))
	{
		addPosition(forward() * 15 * _deltaTime);
	}
	// Backward
	else if (input->isKeyDown('k'))
	{
		addPosition(back() * 15 * _deltaTime);
	}

	// Left
	if (input->isKeyDown('j'))
	{
		addPosition(left() * 15 * _deltaTime);
	}
	// Right
	else if (input->isKeyDown('l'))
	{
		addPosition(right() * 15 * _deltaTime);
	}

	// Up
	if (input->isKeyDown('o'))
	{
		addPosition(up() * 15 * _deltaTime);
	}
	// Down
	else if (input->isKeyDown('u'))
	{
		addPosition(down() * 15 * _deltaTime);
	}
	#pragma endregion
}

void Light::setAmbient(Colour _colour)
{
	light_Ambient[0] = _colour.getRed();
	light_Ambient[1] = _colour.getGreen();
	light_Ambient[2] = _colour.getBlue();
	light_Ambient[3] = _colour.getAlpha();
}

void Light::setDiffuse(Colour _colour)
{
	light_Diffuse[0] = _colour.getRed();
	light_Diffuse[1] = _colour.getGreen();
	light_Diffuse[2] = _colour.getBlue();
	light_Diffuse[3] = _colour.getAlpha();
}

void Light::setSpecular(Colour _colour)
{
	light_Specular[0] = _colour.getRed();
	light_Specular[1] = _colour.getGreen();
	light_Specular[2] = _colour.getBlue();
	light_Specular[3] = _colour.getAlpha();
}

void Light::setPosition(Vector3 _position)
{
	Transform::setPosition(_position);
	light_Position[0] = getPosition().getX();
	light_Position[1] = getPosition().getY();
	light_Position[2] = getPosition().getZ();
}

void Light::addPosition(Vector3 _vector)
{
	Light::setPosition(getPosition() + _vector);

	// Limit X
	if (getPosition().getX() > 22.5f) {
		Light::setPosition(Vector3(22.5f, getPosition().getY(), getPosition().getZ()));
	}
	else if (getPosition().getX() < -22.5f) {
		Light::setPosition(Vector3(-22.5f, getPosition().getY(), getPosition().getZ()));
	}

	// Limit Y
	if (getPosition().getY() > 16) {
		Light::setPosition(Vector3(getPosition().getX(), 16, getPosition().getZ()));
	}
	else if (getPosition().getY() < 0.5f) {
		Light::setPosition(Vector3(getPosition().getX(), 0.5f, getPosition().getZ()));
	}

	// Limit Z
	if (getPosition().getZ() > 22.5f) {
		Light::setPosition(Vector3(getPosition().getX(), getPosition().getY(), 22.5f));
	}
	else if (getPosition().getZ() < -22.5f) {
		Light::setPosition(Vector3(getPosition().getX(), getPosition().getY(), -22.5f));
	}
}

void Light::setSpotDirection(Vector3 _direction)
{
	spot_Direction[0] = _direction.getX();
	spot_Direction[1] = _direction.getY();
	spot_Direction[2] = _direction.getZ();
}