// Primitive Class
// Contains a sub class for each primitive type

#pragma once
#define PI 3.14159f

#include "Mesh.h"

class Primitive :
    public Mesh
{
public:
    Primitive();
    ~Primitive();

    class EmptyTransform : public Mesh {};

    class Plane : 
        public Mesh
    {    
    public:
        Plane(int _hSubdivisions = 1, int _vSubdivisions = 1, GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    };

    class Cube :
        public Mesh
    {
    public:
        Cube(int _hSubdivisions = 1, int _vSubdivisions = 1, GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    };

    class Sphere :
        public Mesh
    {
    public:
        Sphere(int _segments = 20, GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    };    
    
    class Disk :
        public Mesh
    {
    public:
        Disk(int _segments, GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    };    
    
    class Cylinder :
        public Mesh
    {
    public:
        Cylinder(int _hSubdivisions = 1, int _vSubdivisions = 1, GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    };

    class Cone :
        public Mesh
    {
    public:
        Cone(int _vSubdivisions = 1, GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    };

    class Torus :
        public Mesh
    {
    public:
        Torus(int _hSubdivisions = 1, int _vSubdivisions = 1, GLuint* _texture = nullptr, bool _castShadows = false, bool _static = true, Vector3 _position = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1));
    };
};