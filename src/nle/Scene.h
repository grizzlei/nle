#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Light.h"

#include <vector>

namespace nle
{
    class Scene : public Object3D
    {
    private:
        Camera *m_camera;
        Light *m_light;
        std::vector<Object3D*> m_render_objects;

    public:
        Scene();
        virtual ~Scene();
        Camera *camera();
        void set_camera(Camera *c);
        Light *light();
        void register_render_object(Object3D *object);
        std::vector<Object3D*> render_objects();

        friend class Renderer3D;
    };
} // namespace nle

#endif