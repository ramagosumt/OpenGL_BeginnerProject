//
// Created by Rama_2 on 12/28/2024.
//

#include "SceneManager.h"
#include "imgui/imgui.h"

SceneManager::SceneManager(Scene*& current_scene) :
        m_CurrentScene(current_scene)
{
}

void SceneManager::OnImGuiRender() {
    for (const auto& scene : m_Scenes) {
        if (ImGui::Button(scene.first.c_str())) {
            m_CurrentScene = scene.second();
        }
    }
}