#include "Camera.h"
#include "Scene.h"

#include <GLFW/glfw3.h>

namespace nle
{
    Camera::Camera()
    {
        Scene *s= dynamic_cast<Scene*>(root());
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

    bool Camera::free_roam() const
    {
        return m_free_roam;
    }

    void Camera::set_free_roam(bool free_roam)
    {
        m_free_roam = free_roam;
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

    void Camera::on_mouse_motion(int dx, int dy)
    {
        if(!m_free_roam)
        {
            return;
        }
        
        dx *= m_turn_speed;
        dy *= m_turn_speed;

        glm::vec3 camrot = rotation();

        float pitch = camrot.x + dy;
        float yaw = camrot.y + dx;

        if (pitch > 89.f)
        {
            pitch = 89.f;
        }
        if (pitch < -89.f)
        {
            pitch = -89.f;
        }

        set_rotation({pitch, yaw, 0.f});
        update();
    }

    void Camera::on_key_pressed(int key)
    {
        if(!m_free_roam)
        {
            return;
        }
        
        glm::vec3 dposf = m_front * m_speed;
        glm::vec3 dposr = m_right * m_speed;
        glm::vec3 dposu = m_up * m_speed;

        if (key == GLFW_KEY_W)
        {
            set_position(position() + dposf);
        }
        if (key == GLFW_KEY_S)
        {
            set_position(position() - dposf);
        }
        if (key == GLFW_KEY_D)
        {
            set_position(position() + dposr);
        }
        if (key == GLFW_KEY_A)
        {
            set_position(position() - dposr);
        }
        if (key == GLFW_KEY_E)
        {
            set_position(position() + dposu);
        }
        if (key == GLFW_KEY_Q)
        {
            set_position(position() - dposu);
        }
    }
} // namespace nle
