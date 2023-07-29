#include "Scene.h"

namespace nle
{
    Scene::Scene()
        : m_camera(new Camera(glm::vec3(0.f, 0.f, 0.f))), m_light(new Light(1.f, 1.f, 1.f, 1.f, 1.f))
    {
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

    Light *Scene::light()
    {
        return m_light;
    }
} // namespace nle
