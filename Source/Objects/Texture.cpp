//
// Created by Rama_2 on 12/29/2024.
//

#include "Texture.h"

#include <iostream>

using namespace std;

Texture::Texture(const TexMode mode, const string &path, const unsigned int slot, GLenum desired_param) :
        m_RendererID(), m_TexMode(mode), m_FilePath(path), m_Data(nullptr), m_Width(0), m_Height(0), m_NumChannels(0)
{
    stbi_set_flip_vertically_on_load(true);
    m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NumChannels, 4);

    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    if (desired_param == GL_NEAREST) {
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
    }
    else if (desired_param == GL_LINEAR) {
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    }

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, desired_param));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    switch (m_TexMode) {
    case TexMode::JPG:
    case TexMode::PNG:
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                            m_Width, m_Height, 0, GL_RGBA,
                            GL_UNSIGNED_BYTE, m_Data));

        break;
    default:
        cerr << "Texture mode is not supported." << endl;
        return;
    }

    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    if (m_Data) {
        stbi_image_free(m_Data);
    }
    else {
        cerr << "Failed to load texture." << endl;
        cerr << "Texture path: \"" << path << "\"" << endl;
    }
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(const unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}