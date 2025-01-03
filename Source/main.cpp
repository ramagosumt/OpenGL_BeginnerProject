#include "SceneManager.h"
#include "LearnOpenGL.h"
#include "LearnOpenGL_LargerMap.h"
#include "LearnOpenGL_SimpleHouse.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace std;

/* Function Declarations */
void ResizeWindow(GLFWwindow* window, int width, int height);
void OnEscapeButtonPressed(GLFWwindow *window);

/* Main Function */
int main() {
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Training", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glewInit();

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, ResizeWindow);

    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init((char *) glGetString(330));

        Scene* current_scene = nullptr;
        auto* current_manager = new SceneManager(current_scene);
        current_scene = current_manager;

        current_manager->AddScene<LearnOpenGL>("Basic - Dirt Block");
        current_manager->AddScene<LearnOpenGL_LargerMap>("Basic - Dirt House");
        current_manager->AddScene<LearnOpenGL_SimpleHouse>("Batch Rendering - Simple House");

        /* Rendering Loop */
        while (!glfwWindowShouldClose(window)) {
            OnEscapeButtonPressed(window);

            Renderer::Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (current_scene != nullptr) {
                current_scene->OnUpdate(0.0f);
                if (auto gl_cast = dynamic_cast<LearnOpenGL*>(current_scene)) gl_cast->set_window(window);
                else if (auto gllm_cast = dynamic_cast<LearnOpenGL_LargerMap*>(current_scene)) gllm_cast->set_window(window);
                else if (auto glsh_cast = dynamic_cast<LearnOpenGL_SimpleHouse*>(current_scene)) glsh_cast->set_window(window);
                current_scene->OnRender();

                ImGui::Begin("RAMA's World of Graphics");
                if (current_scene != current_manager && ImGui::Button("<-")) {
                    delete current_scene;
                    current_scene = current_manager;
                }

                current_scene->OnImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        delete current_scene;
        if (current_scene != current_manager) {
            delete current_manager;
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}

/* Helper Functions */
void ResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OnEscapeButtonPressed(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}