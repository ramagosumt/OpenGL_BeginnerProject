//
// Created by Rama_2 on 12/27/2024.
//

#include "Renderer.h"

#include <iostream>
#include <GL/glew.h>

using namespace std;

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        cerr << "[OpenGL] Error(" << error << ")." << endl;
        cerr << "Function: " << function << endl;
        cerr << "File: " << file << ":" << line << endl;
        return false;
    }

    return true;
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::DrawIndices(const GLenum mode, VertexArray*& VAO, IndexBuffer*& IBO, Shader*& S, bool depth, GLenum raster_mode) {
    VAO->Bind();
    IBO->Bind();
    S->Bind();

    if (depth) {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glPolygonMode(GL_FRONT_AND_BACK, raster_mode);
    glDrawElements(mode, static_cast<GLsizei>(IBO->GetCount()), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawVertices(GLenum mode, VertexArray*& VAO, VertexBuffer*& VBO, Shader*& S, const unsigned int count, bool depth)
{
    VAO->Bind();
    VBO->Bind();
    S->Bind();

    if (depth) {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glDrawArrays(mode, 0, static_cast<GLsizei>(count));
}
