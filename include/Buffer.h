#pragma once
#include <glad/glad.h>
#include <string>

class Buffer
{
public:

    enum class VBOType {VERTEX_BUFFER, COLOR_BUFFER, TEXTURE_BUFFER};

    enum class ComponentType { XY = 2, XYZ = 3, RGB = 3, RGBA = 4, UV = 2};

    enum class FillType { Once = GL_STATIC_DRAW, OnGoing = GL_DYNAMIC_DRAW };

    enum class DataType { INT = GL_INT, FLOAT = GL_FLOAT, UNSIGNED_INT = GL_UNSIGNED_INT };

    enum class DrawType { POINTS = GL_POINTS, TRIANGLES = GL_TRIANGLES, LINES = GL_LINES, };

public:

    Buffer();

public:

    void CreateBuffer(GLuint totalVertices, bool hasEBO = false);
	void FillEBO(const GLuint* data,
		GLsizeiptr bufferSize, 
        FillType fill = FillType::Once);
    void FillVBO(VBOType vboType,
                GLfloat* data,
                GLsizeiptr bufferSize,
                FillType fillType);

    void LinkEBO();
    void LinkVBO(const std :: string& attribute,
                    VBOType vboType,
                    ComponentType componentType,
                    DataType dataType);

    void Render(DrawType drawType);

    void DestroyBuffer();

private:

    bool m_hasEBO;
    
    GLuint m_VAO;
    GLuint m_EBO;
    GLuint m_vertexVBO;
    GLuint m_colorVBO;
    GLuint m_textureVBO;
    GLuint m_totalVertices;

};

