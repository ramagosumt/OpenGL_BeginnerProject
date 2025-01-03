//
// Created by Rama_2 on 12/31/2024.
//

#pragma once

#include "glm/glm.hpp"

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
    ~Camera();

    inline glm::vec3 GetPosition() { return m_Position; }
    inline glm::vec3 GetFront() { return m_Front; }
    inline glm::vec3 GetUp() { return m_Up; }
    inline glm::vec3 GetDirection() { return m_Direction; }
    [[nodiscard]] inline float GetPitch() const { return m_Pitch; }
    [[nodiscard]] inline float GetYaw() const { return m_Yaw; }
    [[nodiscard]] inline float GetFOV() const { return m_FOV; }

    inline void SetPosition(const glm::vec3 new_position) { m_Position = new_position; }
    inline void SetFront(const glm::vec3 new_front) { m_Front = new_front; }
    inline void SetDirection(const glm::vec3 new_direction) { m_Direction = new_direction; }
    inline void SetPitch(const float new_pitch) { m_Pitch = new_pitch; }
    inline void SetYaw(const float new_yaw) { m_Yaw = new_yaw; }
    inline void SetFOV(const float new_fov) { m_FOV = new_fov; }

private:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Target;
    glm::vec3 m_Direction;
    glm::vec3 m_Right;

    float m_Pitch = 0.f;
    float m_Yaw = -90.f;
    float m_Roll = 0.f;

    float m_FOV = 45.f;

};
