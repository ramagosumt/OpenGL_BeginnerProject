//
// Created by Rama_2 on 12/28/2024.
//

#pragma once

#include <vector>
#include <string>
#include <functional>

using namespace std;

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnImGuiRender() {}

};

class SceneManager : public Scene {
public:
    SceneManager(Scene*& current_scene);

    void OnImGuiRender() override;

    template<typename T>
    void AddScene(const string& scene_name) {
        m_Scenes.push_back(make_pair(scene_name, []() { return new T(); }));
    }

private:
    vector<pair<string, function<Scene*()>>> m_Scenes;
    Scene*& m_CurrentScene;

};
