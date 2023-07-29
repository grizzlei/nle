#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Light.h"

namespace nle
{
    class Scene : public Object3D
    {
    private:
        Camera *m_camera;
        Light *m_light;

    public:
        Scene();
        virtual ~Scene();
        Camera *camera();
        Light *light();
    };
} // namespace nle

#endif