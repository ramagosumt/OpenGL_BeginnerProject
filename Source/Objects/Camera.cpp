//
// Created by Rama_2 on 12/31/2024.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up) :
    m_Position(position), m_Front(front), m_Up(up),
    m_Direction(0.f, 0.f, 0.f),
    m_Right(0.f, 0.f, 0.f),
    m_Target(0.f, 0.f, 0.f)
{
    m_Direction.x = static_cast<float>(cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));
    m_Direction.y = static_cast<float>(sin(glm::radians(m_Pitch)));
    m_Direction.z = static_cast<float>(sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));
}

Camera::~Camera() {

}
