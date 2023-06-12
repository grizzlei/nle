#ifndef SPATIAL_H
#define SPATIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils.h"

#include <vector>
#include <string>

namespace nle
{
    class Object3D
    {
    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
        glm::vec3 m_velocity;

        std::vector<Object3D *> m_children;
        std::string m_id;

        Object3D *m_parent;
        Object3D *m_root;

        void setRoot(Object3D *root);

    public:
        Object3D(const std::string &id = "");
        virtual ~Object3D();
        void setPosition(glm::vec3 position);
        glm::vec3 position() const;
        void setRotation(glm::vec3 rotation);
        glm::vec3 rotation() const;
        void setScale(glm::vec3 scale);
        glm::vec3 velocity() const;
        void setVelocity(glm::vec3 velocity);
        glm::vec3 scale() const;
        std::vector<Object3D *> children() const;
        void addChild(Object3D *child);
        void setId(const std::string);
        std::string id() const;
        void setParent(Object3D *parent);
        Object3D *parent() const;
        Object3D *root() const;
    };
} // namespace nle

#endif