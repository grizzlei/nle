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

        void set_root(Object3D *root);

    public:
        Object3D(const std::string &id = "");
        virtual ~Object3D();
        void set_position(glm::vec3 position);
        glm::vec3 position() const;
        void set_rotation(glm::vec3 rotation);
        glm::vec3 rotation() const;
        void set_scale(glm::vec3 scale);
        glm::vec3 velocity() const;
        void set_velocity(glm::vec3 velocity);
        glm::vec3 scale() const;
        std::vector<Object3D *> children() const;
        void add_child(Object3D *child);
        void set_id(const std::string);
        std::string id() const;
        void set_parent(Object3D *parent);
        Object3D *parent() const;
        Object3D *root() const;
    };
} // namespace nle

#endif