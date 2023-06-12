#include "Object3D.h"
#include <algorithm>

namespace nle
{
    Object3D::Object3D(const std::string &id)
        : m_position(0), m_rotation(0), m_scale(1.f), m_velocity(0.f), m_root(this)
    {
        m_id = id.empty() ? generate_random_alphanumeric_string() : id;
    }

    Object3D::~Object3D()
    {
        for (auto *i : m_children)
        {
            delete i;
        }
    }

    void Object3D::setPosition(glm::vec3 pos)
    {
        m_position = pos;
        for(auto * c : m_children)
        {
            c->setPosition(pos);
        }
    }

    glm::vec3 Object3D::position() const
    {
        return m_position;
    }

    void Object3D::setRotation(glm::vec3 rotation)
    {
        m_rotation = rotation;
        for(auto * c : m_children)
        {
            c->setRotation(rotation);
        }
    }

    glm::vec3 Object3D::rotation() const
    {
        return m_rotation;
    }

    void Object3D::setScale(glm::vec3 scale)
    {
        m_scale = scale;
        for(auto * c : m_children)
        {
            c->setScale(scale);
        }
    }

    glm::vec3 Object3D::velocity() const
    {
        return m_velocity;
    }

    void Object3D::setVelocity(glm::vec3 velocity)
    {
        m_velocity = velocity;
    }

    glm::vec3 Object3D::scale() const
    {
        return m_scale;
    }

    std::vector<Object3D *> Object3D::children() const
    {
        return m_children;
    }

    void Object3D::addChild(Object3D *child)
    {
        if(!child)
            prerr("child cannot be null");

        if (std::find(m_children.begin(), m_children.end(), child) == m_children.end())
        {
            m_children.push_back(child);
            child->setParent(this);
        }
        else
            prerr("child already added");
    }

    void Object3D::setId(const std::string id)
    {
        m_id = id;
    }

    std::string Object3D::id() const
    {
        return m_id;
    }

    void Object3D::setParent(Object3D *parent)
    {
        m_parent = parent;
        setRoot(parent->root());
    }

    Object3D *Object3D::parent() const
    {
        return m_parent;
    }

    void Object3D::setRoot(Object3D *root)
    {
        m_root = root;
        for(auto * c : m_children)
        {
            c->setRoot(root);
        }
    }

    Object3D *Object3D::root() const
    {
        return m_root;
    }
} // namespace nle
