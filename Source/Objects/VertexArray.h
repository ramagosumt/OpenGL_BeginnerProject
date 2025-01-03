//
// Created by Rama_2 on 12/28/2024.
//

#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& VBO, const VertexBufferLayout& VBL) const;

    void Bind() const;
    static void Unbind();

private:
    unsigned int m_RendererID;

};