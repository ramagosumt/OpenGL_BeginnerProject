//
// Created by Rama_2 on 12/28/2024.
//

#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

Shader::Shader(const string& vertex_path, const string& fragment_path) :
        m_VertexPath(vertex_path), m_FragmentPath(fragment_path), m_RendererID()
{
    ShaderProgramSource source = ParseShader(vertex_path, fragment_path);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(m_RendererID);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1f(const string &name, float value) {
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const string &name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1iv(const string& name, unsigned int count, int* value) {
    GLCall(glUniform1iv(GetUniformLocation(name), count, value));
}

void Shader::SetUniform2f(const string &name, float v0, float v1) {
    GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniform3f(const string &name, float v0, float v1, float v2) {
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const string &name, const glm::mat4 &matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

ShaderProgramSource Shader::ParseShader(const string& vertex_path, const string& fragment_path) {
    auto skipBOM = [](ifstream& file) {
        char bom[3];
        file.read(bom, 3);
        if (!(bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF')) {
            file.seekg(0); // Reset to the beginning if no BOM
        }
    };

    ifstream vertex_file(vertex_path);
    ifstream fragment_file(fragment_path);

    if (!vertex_file.is_open() || !fragment_file.is_open()) {
        cerr << "Error: Unable to open shader file(s)." << endl;
        return {"", ""};
    }

    skipBOM(vertex_file);
    skipBOM(fragment_file);

    stringstream vertexStream, fragmentStream;

    vertexStream << vertex_file.rdbuf();
    fragmentStream << fragment_file.rdbuf();

    return { vertexStream.str(), fragmentStream.str() };
}

unsigned int Shader::CompileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
        cerr << message << endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const string& vertexShader, const string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int Shader::GetUniformLocation(const string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) {
        cerr << "[Warning] Uniform " << name << " does not exist!" << endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}
