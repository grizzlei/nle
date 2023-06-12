#include "Camera.h"

namespace nle
{
    Camera::Camera()
    {
    }

    Camera::Camera(glm::vec3 position)
    {
        setPosition(position);
        setRotation(glm::vec3(0.f));
        m_up = glm::vec3(0.f, 1.f, 0.f);
        m_front = glm::vec3(0.f, 0.f, -1.f);
        m_right = glm::vec3(1.f, 0.f, 0.f);
        m_upWorld = glm::vec3(0.f, 1.f, 0.f);
        m_speed = 1.f;
        m_turnSpeed = 1.f;
    }

    Camera::~Camera()
    {
    }

    void Camera::setSpeed(float speed)
    {
        m_speed = speed;
    }

    float Camera::speed() const
    {
        return m_speed;
    }

    void Camera::setTurnSpeed(float turnSpeed)
    {
        m_turnSpeed = turnSpeed;
    }

    float Camera::turnSpeed() const
    {
        return m_turnSpeed;
    }

    void Camera::update()
    {
        m_front.x = cos(glm::radians(rotation().y)) * cos(glm::radians(rotation().x));
        m_front.y = sin(glm::radians(rotation().x));
        m_front.z = sin(glm::radians(rotation().y)) * cos(glm::radians(rotation().x));
        m_front = glm::normalize(m_front);

        m_right = glm::normalize(glm::cross(m_front, m_upWorld));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(position(), position() + m_front, m_up);
    }
} // namespace nle
