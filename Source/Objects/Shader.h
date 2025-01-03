//
// Created by Rama_2 on 12/28/2024.
//

#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

using namespace std;

struct ShaderProgramSource {
    string VertexSource;
    string FragmentSource;
};

class Shader {
public:
    Shader(const string& vertex_path, const string& fragment_path);
    ~Shader();

    void Bind() const;
    static void Unbind();

    void SetUniform1f(const string& name, float value);
    void SetUniform1i(const string& name, int value);
    void SetUniform1iv(const string& name, unsigned int count, int* value);
    void SetUniform2f(const string& name, float v0, float v1);
    void SetUniform3f(const string& name, float v0, float v1, float v2);
    void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const string& name, const glm::mat4& matrix);

private:
    unsigned int m_RendererID;
    string m_VertexPath;
    string m_FragmentPath;
    unordered_map<string, int> m_UniformLocationCache;

    static ShaderProgramSource ParseShader(const string& vertex_path, const string& fragment_path);
    static unsigned int CompileShader(unsigned int type, const string& source);
    static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);

    int GetUniformLocation(const string& name);

};
