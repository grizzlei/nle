#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Window.h"
#include "Mesh.h"

#include <thread>
#include <unordered_map>

namespace nle
{
    struct RenderLayerAttributes
    {
        int render_distance = 100;
        bool visible = true;
    };

    class Renderer3D
    {
    private:
        Scene *m_root_scene;
        Window *m_parent_window;
        float m_max_render_distance;
        std::unordered_map<uint8_t, RenderLayerAttributes> m_render_layer_attributes;
        bool m_time_strict_mode;

        double m_render_timestamp;
        double m_input_timestamp;
        std::thread m_thr_input;

        void render_recursively(Object3D *root);
        void initialize();
        void process_keyboard_input();
        void process_mouse_input(GLfloat dx, GLfloat dy);

    public:
        enum RenderLayer
        {
            _0 = 0,
            _1,
            _2,
            _3,
            _4,
            _5,
            _6,
            _7
        };

        Renderer3D(Window *render_target);
        virtual ~Renderer3D();
        void render(Object3D *d);
        void set_root_scene(Scene *root);
        Scene *root_scene() const;
        void set_render_layer_attributes(RenderLayer layer, RenderLayerAttributes attributes);
        RenderLayerAttributes render_layer_attributes(RenderLayer layer = RenderLayer::_0);
    };
} // namespace nle

#endif