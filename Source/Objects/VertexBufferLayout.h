//
// Created by Rama_2 on 12/28/2024.
//

#pragma once

#include "Renderer.h"

#include <vector>
#include <GL/glew.h>

using namespace std;

struct VertexBufferElement {
    unsigned int count;
    unsigned int type;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;

            default:
                ASSERT(false);
                return 0;
        }
    }
};

class VertexBufferLayout {
public:
    VertexBufferLayout() : m_Stride(0) {}

    template<typename T>
    void Push(unsigned int count) {
        static_assert(false, "Unsupported type for Push.");
    }

    [[nodiscard]] inline const vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    [[nodiscard]] inline unsigned int GetStride() const { return m_Stride; }

private:
    vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count) {
    m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
    m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

