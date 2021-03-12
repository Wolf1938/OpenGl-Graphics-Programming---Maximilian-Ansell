// Light Class contains functionality of directional, spot, and point lights 
// Stores a pointer to each shadow volume this light casts

#pragma once
#include "Colour.h"
#include "ShadowVolume.h"
#include "primitive.h"
#include "Input.h"

class Light :
    public Transform
{
public:
    enum class LightType { directional, spot, point };

#pragma region Functions
    Light(Input* _input, LightType _lightType, Colour _ambient, Colour _diffuse, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    ~Light();

    void handleInput(float _deltaTime);
    void render() { mesh->setPosition(getPosition()); mesh->render(); }

    // Iterates through each mesh and if that mesh casts shadows calculate each shadow volume
    void buildShadowVolumes(std::vector<Mesh*>* _meshes);
    // Renders all the shadow volumes this light casts
    void renderShadowVolumes();
    // Called each render cylce, build the light using OpenGL
    void buildLight(int _lightIndex);  

#pragma region Getters + Setters
    std::vector<ShadowVolume*>* getShadowVolumes() { return &shadowVolumes; }

    GLfloat* getAmbient() { return light_Ambient; }
    void setAmbient(Colour _colour);

    GLfloat* getDiffuse() { return light_Diffuse; }
    void setDiffuse(Colour _colour);

    GLfloat* getSpecular() { return light_Specular; }
    void setSpecular(Colour _colour);

    // This function is used in place of Transfrom::getPosition to return a GLFloat* instead of Vector3*
    GLfloat* getLightPosition() { return light_Position; }
    // Intercepts the Transform setPosition and Updates the Light_Position GLFloat array
    void setPosition(Vector3 _Position);
    // Intercepts the Transform addPosition and sets the position of both Light_Position GLFloat array and Transform::position
    void addPosition(Vector3 _vector);

    float getConstantAttenuation() { return constant_Attenuation; }
    void setConstantAttenuation(float _constantAttenuation) { constant_Attenuation = _constantAttenuation; }

    float getLinearAttenuation() { return linear_Attenuation; }
    void setLinearAttenuation(float _linearAttenuation) { linear_Attenuation = _linearAttenuation; }

    float getquadraticAttenuation() { return quadratic_Attenuation; }
    void setquadraticAttenuation(float _quadraticAttenuation) { quadratic_Attenuation = _quadraticAttenuation; }    

    GLfloat* getSpotDirection() { return spot_Direction; }
    void setSpotDirection(Vector3 _direction);

    float getSpotCutOff() { return spot_CutOff; }
    void setSpotCutOff(float _cutOff) { spot_CutOff = _cutOff; }

    float getSpotExponent() { return spot_Exponent; }
    void setSpotExponent(float _exponent) { spot_Exponent = _exponent; }
#pragma endregion
#pragma endregion

#pragma region Variables
private:
    Input* input = nullptr;
    LightType light_Type;

    std::vector<ShadowVolume*> shadowVolumes;

    Mesh* mesh;

    // Global light variables
    GLfloat light_Ambient[4];
    GLfloat light_Diffuse[4];
    GLfloat light_Specular[4];
    GLfloat light_Position[4];

    // Attenuation variables
    float constant_Attenuation = 0.1f;
    float linear_Attenuation = 0.125f;
    float quadratic_Attenuation = 0.0f;

    // Spot light variables
    GLfloat spot_Direction[3];
    float spot_CutOff = 25.0f;
    float spot_Exponent = 50.0f;
#pragma endregion
};