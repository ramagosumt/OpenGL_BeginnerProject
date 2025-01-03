//
// Created by Rama_2 on 12/27/2024.
//

#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    static void Clear();
    static void DrawIndices(GLenum mode, VertexArray*& VAO, IndexBuffer*& IBO, Shader*& S, bool depth = false, GLenum raster_mode = GL_FILL);
    static void DrawVertices(GLenum mode, VertexArray*& VAO, VertexBuffer*& VBO, Shader*& S, unsigned int count, bool depth = false);

};