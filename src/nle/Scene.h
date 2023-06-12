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

        bool m_showGrid;

    public:
        Scene();
        virtual ~Scene();
        Camera *camera();
        Light *light();
        void setGridVisibility(bool visible);
        bool gridVisibility();
    };
} // namespace nle

#endif