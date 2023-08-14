#include "Scene.h"

namespace nle
{
    Scene::Scene()
        : m_camera(new Camera(glm::vec3(0.f, 0.f, 0.f))), m_light(new Light(1.f, 1.f, 1.f, 1.f, 1.f))
    {
        // this->sig_child_added().bind_callback([this](const Object3D*& msg){
        //     this->register_render_object(c);
        // });
    }

    Scene::~Scene()
    {
        delete m_light;
        delete m_camera;
    }

    Camera *Scene::camera()
    {
        return m_camera;
    }

    void Scene::set_camera(Camera *c)
    {
        m_camera = c;
    }

    Light *Scene::light()
    {
        return m_light;
    }

    void Scene::register_render_object(Object3D *object)
    {
        m_render_objects.push_back(object);
        for(auto * c : object->children())
        {
            m_render_objects.push_back(c);
        }
    }
    std::vector<Object3D *> Scene::render_objects()
    {
        return m_render_objects;
    }
    void Scene::add_child(Object3D *child)
    {
        Object3D::add_child(child);
        register_render_object(child);
    }
} // namespace nle
