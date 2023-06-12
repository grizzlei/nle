#ifndef CAMERA_H
#define CAMERA_H

#include "Object3D.h"

namespace nle
{
    class Camera : public Object3D
    {
    private:
        float m_speed;
        float m_turnSpeed;

        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_upWorld;

        void update();
        glm::mat4 getViewMatrix();

    public:
        Camera();
        Camera(glm::vec3 position);
        virtual ~Camera();
        void setSpeed(float speed);
        float speed() const;
        void setTurnSpeed(float turnSpeed);
        float turnSpeed() const;

        friend class Renderer3D;
    };
} // namespace nle

#endif