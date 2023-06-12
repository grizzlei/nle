#include "Nle.h"
#include "Scene.h"

namespace nle
{
    Shader *DEFAULT_SHADER;

    Nle::Nle()
    {
        initialize();
    }

    Nle::~Nle()
    {
        cleanup();
    }

    Window *Nle::window()
    {
        return m_window;
    }

    Renderer3D *Nle::renderer()
    {
        return m_renderer;
    }

    TextureFactory *Nle::textureFactory()
    {
        return m_textureFactory;
    }

    Scene *Nle::currentScene()
    {
        return m_renderer->rootScene();
    }

    PhysicsEngine *Nle::physicsEngine()
    {
        return m_physicsEngine;
    }

    void Nle::run()
    {
        m_window->display();
    }

    void Nle::initialize()
    {
        m_window = new nle::Window(1280, 720, "nice little engine");
        m_renderer = new Renderer3D(m_window);
        m_textureFactory = new TextureFactory();
        m_physicsEngine = new PhysicsEngine();

        m_renderer->setRootScene(new Scene());

        RenderLayerAttributes rla;
        rla.renderDistance = 10000;
        m_renderer->setRenderLayerAttributes(nle::Renderer3D::RenderLayer::_0, rla);

        // initialize defaults
        DEFAULT_SHADER = new Shader("shader/default_vert.glsl", "shader/default_frag.glsl", true);
    }

    void Nle::cleanup()
    {
        delete DEFAULT_SHADER;
        delete m_physicsEngine;
        delete m_textureFactory;
        delete m_renderer;
        delete m_window;
    }

} // namespace nle
