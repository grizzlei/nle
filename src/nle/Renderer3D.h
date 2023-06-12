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
        int renderDistance = 100;
        bool visible = true;
    };

    class Renderer3D
    {
    private:
        Scene *m_rootScene;
        Window *m_parentWindow;
        float m_maxRenderDistance;
        std::unordered_map<uint8_t, RenderLayerAttributes> m_renderLayerAttributes;
        bool m_timeStrictMode;

        double m_renderTimestamp;
        double m_inputTimestamp;
        std::thread m_thrInput;

        void renderRecursively(Object3D *root);
        void initialize();
        void processKeyboardInput();
        void processMouseInput(GLfloat dx, GLfloat dy);

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

        Renderer3D(Window *renderTarget);
        virtual ~Renderer3D();
        void render(Object3D *d);
        void setRootScene(Scene *root);
        Scene *rootScene() const;
        void setRenderLayerAttributes(RenderLayer layer, RenderLayerAttributes attributes);
        RenderLayerAttributes renderLayerAttributes(RenderLayer layer = RenderLayer::_0);
    };
} // namespace nle

#endif