//
// Created by Rama_2 on 12/29/2024.
//

#pragma once

#include "Renderer.h"
#include "stb_image/stb_image.h"

enum class TexMode : int {
    PNG,
    JPG
};

using namespace std;

class Texture {
public:
    explicit Texture(TexMode mode, const string& path, unsigned int slot = 0, GLenum desired_param = GL_NEAREST);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    [[nodiscard]] inline int GetWidth() const { return m_Width; }
    [[nodiscard]] inline int GetHeight() const { return m_Height; }
    [[nodiscard]] inline int GetNumChannelsP() const { return m_NumChannels; }
    [[nodiscard]] inline string GetFilePath() const { return m_FilePath; }

private:
    unsigned int m_RendererID;
    TexMode m_TexMode;
    string m_FilePath;
    unsigned char* m_Data;
    int m_Width, m_Height, m_NumChannels;

};
