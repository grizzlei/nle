#ifndef CAMERA_H
#define CAMERA_H

#include "Object3D.h"

namespace nle
{
    class Camera : public Object3D
    {
    private:
        float m_speed;
        float m_turn_speed;

        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_up_world;

        void update();
        glm::mat4 get_view_matrix();

    public:
        Camera();
        Camera(glm::vec3 position);
        virtual ~Camera();
        void set_speed(float speed);
        float speed() const;
        void set_turn_speed(float turnSpeed);
        float turn_speed() const;

        friend class Renderer3D;
    };
} // namespace nle

#endif