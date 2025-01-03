//
// Created by Rama_2 on 12/28/2024.
//

#include "LearnOpenGL.h"
#include "imgui/imgui.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

LearnOpenGL::LearnOpenGL() :
        m_ProjectionMatrix(glm::perspective(glm::radians(45.f), SCR_WIDTH / SCR_HEIGHT, 0.1f, 3000.f)),
        m_ModelRotationAxisX(1.f, 0.f, 0.f),
        m_ModelRotationAxisY(0.f, 1.f, 0.f),
        m_ModelRotationAxisZ(0.f, 0.f, 1.f),
        m_ModelTranslation(0.f, 0.f, 0.f),
        m_ModelRotation(0.f, 0.f, 0.f),
        m_ModelScale(1.f, 1.f, 1.f),
        m_ViewTranslation(0.f, 0.f, 1250.f),
        m_ViewRotation(270.f, 0.f, 0.f),
        current_window(nullptr)
{
    float Vertices[] = {
        -50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 0.f,
         50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  1.f, 0.f,
         50.f,  50.f, -50.f,  1.f, 0.f, 0.f,  1.f, 1.f,
         50.f,  50.f, -50.f,  1.f, 0.f, 0.f,  1.f, 1.f,
        -50.f,  50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f,
        -50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 0.f,

        -50.f, -50.f,  50.f,  1.f, 0.f, 0.f,  0.f, 0.f,
         50.f, -50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,
         50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 1.f,
         50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 1.f,
        -50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  0.f, 1.f,
        -50.f, -50.f,  50.f,  1.f, 0.f, 0.f,  0.f, 0.f,

        -50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,
        -50.f,  50.f, -50.f,  1.f, 0.f, 0.f,  1.f, 1.f,
        -50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f,
        -50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f,
        -50.f, -50.f,  50.f,  1.f, 0.f, 0.f,  0.f, 0.f,
        -50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,

         50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,
         50.f,  50.f, -50.f,  1.f, 0.f, 0.f,  1.f, 1.f,
         50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f,
         50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f,
         50.f, -50.f,  50.f,  1.f, 0.f, 0.f,  0.f, 0.f,
         50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,

        -50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f,
         50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  1.f, 1.f,
         50.f, -50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,
         50.f, -50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,
        -50.f, -50.f,  50.f,  1.f, 0.f, 0.f,  0.f, 0.f,
        -50.f, -50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f,

        -50.f,  50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f,
         50.f,  50.f, -50.f,  1.f, 0.f, 0.f,  1.f, 1.f,
         50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,
         50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  1.f, 0.f,
        -50.f,  50.f,  50.f,  1.f, 0.f, 0.f,  0.f, 0.f,
        -50.f,  50.f, -50.f,  1.f, 0.f, 0.f,  0.f, 1.f
    };

    unsigned int Indices[] = {
        0, 1, 2, 2, 3, 0,           // Front
        4, 5, 6, 6, 7, 4,           // Back
        8, 9, 10, 10, 11, 8,        // Top
        12, 13, 14, 14, 15, 12,     // Bottom
        16, 17, 18, 18, 19, 16,     // Left
        20, 21, 22, 22, 23, 20      // Right
    };

    /* Buffers */
    m_VAO = make_unique<VertexArray>();
    m_VBO = make_unique<VertexBuffer>(sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    m_IBO = make_unique<IndexBuffer>(sizeof(Indices) / sizeof(Indices[0]), Indices, GL_STATIC_DRAW);

    /* Layouts */
    m_VBL = make_unique<VertexBufferLayout>();
    m_VBL->Push<float>(3);
    m_VBL->Push<float>(3);
    m_VBL->Push<float>(2);

    /* Arrays */
    m_VAO->AddBuffer(*m_VBO, *m_VBL);

    /* Shaders */
    m_S = make_unique<Shader>("B:/OpenGL Projects/LearnOpenGL/Resource/Shaders/vertex.shader",
                              "B:/OpenGL Projects/LearnOpenGL/Resource/Shaders/fragment.shader");

    /* Textures */
    m_T1 = make_unique<Texture>(TexMode::JPG,
                                "B:/OpenGL Projects/LearnOpenGL/Resource/Textures/mc_dirt.jpg",
                                0);
    m_T2 = make_unique<Texture>(TexMode::JPG,
                                "B:/OpenGL Projects/LearnOpenGL/Resource/Textures/mc_dirt.jpg",
                                1);

    m_S->SetUniform1i("texture1", 0);
    m_S->SetUniform1i("texture2", 1);

    /* Camera */
    m_C = make_unique<Camera>(m_ViewTranslation,
                              glm::vec3(0.f, 0.f, -1.f),
                              glm::vec3(0.f, 1.f, 0.f));
}

void LearnOpenGL::OnUpdate(float delta_time) {
}

void LearnOpenGL::OnRender() {
    auto currentFrame = static_cast<float>(glfwGetTime());
    m_DeltaTime = currentFrame - m_LastFrame;
    m_LastFrame = currentFrame;

    glm::mat4 model_matrix = translate(glm::mat4(1.f), m_ModelTranslation);
    model_matrix = rotate(model_matrix, glm::radians(-m_ModelRotation.x), m_ModelRotationAxisX);
    model_matrix = rotate(model_matrix, glm::radians(-m_ModelRotation.y), m_ModelRotationAxisY);
    model_matrix = rotate(model_matrix, glm::radians(-m_ModelRotation.z), m_ModelRotationAxisZ);
    model_matrix = scale(model_matrix, m_ModelScale);

    glm::mat4 view_matrix = glm::lookAt(m_C->GetPosition(),m_C->GetPosition() + m_C->GetFront(), m_C->GetUp());

    glm::mat4 model_view_projection_matrix = m_ProjectionMatrix * view_matrix * model_matrix;

    m_S->Bind();
    m_S->SetUniformMat4f("transform", model_view_projection_matrix);

    Renderer::DrawVertices(GL_TRIANGLES,
                           reinterpret_cast<VertexArray *&>(m_VAO),
                           reinterpret_cast<VertexBuffer *&>(m_VBO),
                           reinterpret_cast<Shader *&>(m_S),
                           36, true);

    if (current_window) {
        if (glfwGetKey(current_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (glfwGetInputMode(current_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
                m_FirstTouch = true;
            }

            ConfigKeyboardInput(current_window);

            glfwSetWindowUserPointer(current_window, this);

            glfwSetCursorPosCallback(current_window, [](GLFWwindow *window, double mouse_position_x, double mouse_position_y) {
                auto app = static_cast<LearnOpenGL *>(glfwGetWindowUserPointer(window));
                if (app) {
                    app->ConfigMouseInput(window, mouse_position_x, mouse_position_y);
                }

                ImGuiIO& io = ImGui::GetIO();
                if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
                    io.AddMousePosEvent(static_cast<float>(mouse_position_x),
                                        static_cast<float>(mouse_position_y));
                }

            });

            glfwSetScrollCallback(current_window, [](GLFWwindow *window, double scroll_offset_x, double scroll_offset_y) {
                auto app = static_cast<LearnOpenGL *>(glfwGetWindowUserPointer(window));
                if (app) {
                    app->ConfigScrollInput(window, scroll_offset_x, scroll_offset_y);
                }

                ImGuiIO& io = ImGui::GetIO();
                if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
                    io.AddMouseWheelEvent(static_cast<float>(scroll_offset_x),
                                          static_cast<float>(scroll_offset_y));
                }
            });

            ImGuiIO& io = ImGui::GetIO();

            if (glfwGetInputMode(current_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
                io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
                for (int button = 0; button < 3; ++button) {
                    io.AddMouseButtonEvent(button, false);
                }
            } else {
                io.AddMousePosEvent(static_cast<float>(m_MouseX), static_cast<float>(m_MouseY));

                for (int button = 0; button < 3; ++button) {
                    if (glfwGetMouseButton(current_window, button) == GLFW_PRESS) {
                        io.AddMouseButtonEvent(button, true);
                    } else {
                        io.AddMouseButtonEvent(button, false);
                    }
                }
            }

            glfwSetInputMode(current_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetWindowUserPointer(current_window, nullptr);
            glfwSetInputMode(current_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void LearnOpenGL::OnImGuiRender() {
    float label_width = 100.f;
    float slider_start_x = ImGui::GetCursorPosX() + label_width;

    ImGui::Separator();
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.26f, 0.59f, 0.98f, 1.f));
    ImGui::Text("Model");
    ImGui::PopStyleColor();
    ImGui::Separator();

    ImGui::Text("Translation");
    ImGui::SameLine();
    ImGui::SetCursorPosX(slider_start_x);
    ImGui::SliderFloat3("##ModelTranslation", &m_ModelTranslation.x, -1000.f, 1000.f);

    ImGui::Text("Rotation");
    ImGui::SameLine();
    ImGui::SetCursorPosX(slider_start_x);
    ImGui::SliderFloat3("##ModelRotation", &m_ModelRotation.x, 0.f, 360.f);

    ImGui::Text("Scale");
    ImGui::SameLine();
    ImGui::SetCursorPosX(slider_start_x);
    ImGui::SliderFloat3("##ModelScale", &m_ModelScale.x, 0.f, 10.f);

    ImGui::Text("");

    ImGui::Separator();
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.26f, 0.59f, 0.98f, 1.f));
    ImGui::Text("View");
    ImGui::PopStyleColor();
    ImGui::Separator();

    ImGui::Text("Translation");
    ImGui::SameLine();
    ImGui::SetCursorPosX(slider_start_x);
    ImGui::SliderFloat3("##ViewTranslation", &m_ViewTranslation.x, -1000.f, 1000.f);
    m_C->SetPosition(m_ViewTranslation);

    ImGui::Text("Rotation");
    ImGui::SameLine();
    ImGui::SetCursorPosX(slider_start_x);
    ImGui::SliderFloat3("##ViewRotation", &m_ViewRotation.x, 0.f, 360.f);

    m_C->SetPitch(m_ViewRotation.y);
    m_C->SetYaw(m_ViewRotation.x);

    if (m_C->GetPitch() < 0.f) m_C->SetPitch(m_C->GetPitch() + 360.f);
    else if (m_C->GetPitch() > 360.f) m_C->SetPitch(m_C->GetPitch() - 360.f);
    if (m_C->GetPitch() > 89.f && m_C->GetPitch() < 180.f) m_C->SetPitch(89.f);
    else if (m_C->GetPitch() > 180.f && m_C->GetPitch() < 271.f) m_C->SetPitch(271.f);

    m_C->SetDirection(glm::vec3(
            static_cast<float>(cos(glm::radians(m_C->GetYaw())) * cos(glm::radians(m_C->GetPitch()))),
            static_cast<float>(sin(glm::radians(m_C->GetPitch()))),
            static_cast<float>(sin(glm::radians(m_C->GetYaw())) * cos(glm::radians(m_C->GetPitch())))
    ));

    m_C->SetFront(glm::normalize(m_C->GetDirection()));

    if (m_C->GetYaw() < 0.f) m_C->SetYaw(m_C->GetYaw() + 360.f);
    else if (m_C->GetYaw() > 360.f) m_C->SetYaw(m_C->GetYaw() - 360.f);

    if (m_C->GetPitch() < 0.f) m_C->SetPitch(m_C->GetPitch() + 360.f);
    else if (m_C->GetPitch() > 360.f) m_C->SetPitch(m_C->GetPitch() - 360.f);
    if (m_C->GetPitch() > 89.f && m_C->GetPitch() < 180.f) m_C->SetPitch(89.f);
    else if (m_C->GetPitch() > 180.f && m_C->GetPitch() < 271.f) m_C->SetPitch(271.f);

    ImGui::Text("FOV");
    ImGui::SameLine();
    ImGui::SetCursorPosX(slider_start_x);
    ImGui::SliderFloat("##ViewFOV", &m_ViewFOV, 1.f, 45.f);
    m_C->SetFOV(m_ViewFOV);
    m_ProjectionMatrix = glm::perspective(glm::radians(m_C->GetFOV()), SCR_WIDTH / SCR_HEIGHT, 0.1f, 3000.f);
}

void LearnOpenGL::ConfigKeyboardInput(GLFWwindow *window) {
    float cameraSpeed = 1250.f * m_DeltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        m_C->SetPosition(m_C->GetPosition() + cameraSpeed * m_C->GetFront());
        m_ViewTranslation = m_C->GetPosition();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        m_C->SetPosition(m_C->GetPosition() - cameraSpeed * m_C->GetFront());
        m_ViewTranslation = m_C->GetPosition();
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_C->SetPosition(m_C->GetPosition() - glm::normalize(glm::cross(m_C->GetFront(), m_C->GetUp())) * cameraSpeed);
        m_ViewTranslation = m_C->GetPosition();
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_C->SetPosition(m_C->GetPosition() + glm::normalize(glm::cross(m_C->GetFront(), m_C->GetUp())) * cameraSpeed);
        m_ViewTranslation = m_C->GetPosition();
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        m_C->SetPosition(m_C->GetPosition() + cameraSpeed * m_C->GetUp());
        m_ViewTranslation = m_C->GetPosition();
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        m_C->SetPosition(m_C->GetPosition() - cameraSpeed * m_C->GetUp());
        m_ViewTranslation = m_C->GetPosition();
    }
}

void LearnOpenGL::ConfigMouseInput(GLFWwindow* window, double mouse_position_x, double mouse_position_y) {
    if (m_FirstTouch)
    {
        m_MouseX = static_cast<float>(mouse_position_x);
        m_MouseY = static_cast<float>(mouse_position_y);
        m_FirstTouch = false;
    }

    float mouse_offset_x = static_cast<float>(mouse_position_x) - m_MouseX;
    float mouse_offset_y = m_MouseY - static_cast<float>(mouse_position_y);
    m_MouseX = static_cast<float>(mouse_position_x);
    m_MouseY = static_cast<float>(mouse_position_y);

    const float sensitivity = 0.2f;
    mouse_offset_x *= sensitivity;
    mouse_offset_y *= sensitivity;

    m_C->SetPitch(m_C->GetPitch() + mouse_offset_y);
    m_C->SetYaw(m_C->GetYaw() + mouse_offset_x);

    if (m_C->GetPitch() < 0.f) m_C->SetPitch(m_C->GetPitch() + 360.f);
    else if (m_C->GetPitch() > 360.f) m_C->SetPitch(m_C->GetPitch() - 360.f);
    if (m_C->GetPitch() > 89.f && m_C->GetPitch() < 180.f) m_C->SetPitch(89.f);
    else if (m_C->GetPitch() > 180.f && m_C->GetPitch() < 271.f) m_C->SetPitch(271.f);

    m_C->SetDirection(glm::vec3(
                      static_cast<float>(cos(glm::radians(m_C->GetYaw())) * cos(glm::radians(m_C->GetPitch()))),
                      static_cast<float>(sin(glm::radians(m_C->GetPitch()))),
                      static_cast<float>(sin(glm::radians(m_C->GetYaw())) * cos(glm::radians(m_C->GetPitch())))
    ));

    m_C->SetFront(glm::normalize(m_C->GetDirection()));

    if (m_C->GetYaw() < 0.f) m_C->SetYaw(m_C->GetYaw() + 360.f);
    else if (m_C->GetYaw() > 360.f) m_C->SetYaw(m_C->GetYaw() - 360.f);

    if (m_C->GetPitch() < 0.f) m_C->SetPitch(m_C->GetPitch() + 360.f);
    else if (m_C->GetPitch() > 360.f) m_C->SetPitch(m_C->GetPitch() - 360.f);
    if (m_C->GetPitch() > 89.f && m_C->GetPitch() < 180.f) m_C->SetPitch(89.f);
    else if (m_C->GetPitch() > 180.f && m_C->GetPitch() < 271.f) m_C->SetPitch(271.f);

    m_ViewRotation = glm::vec3(m_C->GetYaw(), m_C->GetPitch(), 0.f);
}

void LearnOpenGL::ConfigScrollInput(GLFWwindow* window, double scroll_offset_x, double scroll_offset_y)
{
    const vector<float> FOV_values = {1.0f, 15.0f, 30.0f, 45.0f};
    float current_FOV = m_C->GetFOV();

    auto closest_it = std::min_element(FOV_values.begin(), FOV_values.end(),
                                       [current_FOV](float a, float b) {
                                           return std::abs(a - current_FOV) < std::abs(b - current_FOV);
                                       });

    auto it = closest_it;
    if (scroll_offset_y > 0 && it != FOV_values.begin()) {
        --it;
    } else if (scroll_offset_y < 0 && it + 1 != FOV_values.end()) {
        ++it;
    }

    m_C->SetFOV(*it);
    m_ViewFOV = *it;
    m_ProjectionMatrix = glm::perspective(glm::radians(*it), SCR_WIDTH / SCR_HEIGHT, 0.1f, 3000.f);
}
