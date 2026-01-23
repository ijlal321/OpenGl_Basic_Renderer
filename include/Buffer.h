#pragma once
#include "glad.h"

class Buffer
{
public:

    enum VBOType {VERTEX_BUFFER, COLOR_BUFFER};

    enum ComponentType { XY = 2, XYZ = 3, RGB = 3, RGBA = 4};

    enum FillType { SINGLE = GL_STATIC_DRAW, MULTIPLE = GL_DYNAMIC_DRAW };

    enum DataType { INT = GL_INT, FLOAT = GL_FLOAT, UNSIGNED_INT = GL_UNSIGNED_INT };

    enum DrawType { POINTS = GL_POINTS, TRIANGLES = GL_TRIANGLES, LINES = GL_LINES, };

public:

    Buffer();

public:

    void CreateBuffer(GLuint totalVertices, bool hasEBO);


