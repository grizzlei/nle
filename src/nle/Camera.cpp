#include "Camera.h"

namespace nle
{
    Camera::Camera()
    {
    }

    Camera::Camera(glm::vec3 position)
    {
        set_position(position);
        set_rotation(glm::vec3(0.f));
        m_up = glm::vec3(0.f, 1.f, 0.f);
        m_front = glm::vec3(0.f, 0.f, -1.f);
        m_right = glm::vec3(1.f, 0.f, 0.f);
        m_up_world = glm::vec3(0.f, 1.f, 0.f);
        m_speed = 1.f;
        m_turn_speed = 1.f;
    }

    Camera::~Camera()
    {
    }

    void Camera::set_speed(float speed)
    {
        m_speed = speed;
    }

    float Camera::speed() const
    {
        return m_speed;
    }

    void Camera::set_turn_speed(float turnSpeed)
    {
        m_turn_speed = turnSpeed;
    }

    float Camera::turn_speed() const
    {
        return m_turn_speed;
    }

    void Camera::update()
    {
        m_front.x = cos(glm::radians(rotation().y)) * cos(glm::radians(rotation().x));
        m_front.y = sin(glm::radians(rotation().x));
        m_front.z = sin(glm::radians(rotation().y)) * cos(glm::radians(rotation().x));
        m_front = glm::normalize(m_front);

        m_right = glm::normalize(glm::cross(m_front, m_up_world));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }

    glm::mat4 Camera::get_view_matrix()
    {
        return glm::lookAt(position(), position() + m_front, m_up);
    }
} // namespace nle
