//
// Created by Rama_2 on 12/28/2024.
//

#pragma once

#include "SceneManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <memory>
#include <GLFW/glfw3.h>

#define SCR_WIDTH 1920.f
#define SCR_HEIGHT 1080.f

class LearnOpenGL : public Scene {
public:
    LearnOpenGL();

    void OnUpdate(float delta_time) override;
    void OnRender() override;
    void OnImGuiRender() override;

    void set_window(GLFWwindow *window) { current_window =  window; }

private:
    unique_ptr<VertexBuffer> m_VBO;
    unique_ptr<IndexBuffer> m_IBO;
    unique_ptr<VertexArray> m_VAO;
    unique_ptr<VertexBufferLayout> m_VBL;
    unique_ptr<Shader> m_S;
    unique_ptr<Texture> m_T1;
    unique_ptr<Texture> m_T2;
    unique_ptr<Camera> m_C;

    glm::mat4 m_ProjectionMatrix;
    glm::vec3 m_ModelRotationAxisX;
    glm::vec3 m_ModelRotationAxisY;
    glm::vec3 m_ModelRotationAxisZ;

    glm::vec3 m_ModelTranslation;
    glm::vec3 m_ModelRotation;
    glm::vec3 m_ModelScale;
    glm::vec3 m_ViewTranslation;
    glm::vec3 m_ViewRotation;

    float m_ViewFOV = 45.f;

    void ConfigKeyboardInput(GLFWwindow *window);
    void ConfigMouseInput(GLFWwindow* window, double mouse_position_x, double mouse_position_y);
    void ConfigScrollInput(GLFWwindow* window, double scroll_offset_x, double scroll_offset_y);

    GLFWwindow* current_window;

    float m_DeltaTime = 0.0f;
    float m_LastFrame = 0.0f;
    float m_MouseX = SCR_WIDTH / 2, m_MouseY = SCR_HEIGHT / 2;

    bool m_FirstTouch = true;
};
