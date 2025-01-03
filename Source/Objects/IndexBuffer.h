//
// Created by Rama_2 on 12/27/2024.
//

#pragma once

#include <GL/glew.h>

class IndexBuffer {

public:
    IndexBuffer(unsigned int count, const unsigned int* data, GLenum usage);
    ~IndexBuffer();

    void Bind() const;
    static void Unbind();

    [[nodiscard]] inline unsigned int GetCount() const { return m_Count; }

private:
    unsigned int m_RendererID;
    unsigned int m_Count;

};

