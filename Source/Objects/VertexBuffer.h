//
// Created by Rama_2 on 12/27/2024.
//

#pragma once

#include <GL/glew.h>

class VertexBuffer {

public:
    VertexBuffer(unsigned int size, const void* data, GLenum usage);
    ~VertexBuffer();

    void Bind() const;
    static void Unbind();

private:
    unsigned int m_RendererID;

};
