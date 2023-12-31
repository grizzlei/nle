#include "Nle.h"
#include "Scene.h"

namespace nle
{

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

    TextureFactory *Nle::texture_factory()
    {
        return m_texture_factory;
    }

    Scene *Nle::current_scene()
    {
        return m_renderer->root_scene();
    }

    PhysicsEngine *Nle::physics_engine()
    {
        return m_physics_engine;
    }

    void Nle::run()
    {
        m_window->display();
    }

    void Nle::set_current_scene(Scene *s)
    {
        m_renderer->set_root_scene(s);
    }

    void Nle::initialize()
    {
        m_window = new nle::Window(1920, 720, "nice little engine");
        m_renderer = new Renderer3D(m_window);
        m_texture_factory = new TextureFactory();
        m_physics_engine = new PhysicsEngine();

        m_renderer->set_root_scene(new Scene());

        RenderLayerAttributes rla;
        rla.render_distance = 10000;
        m_renderer->set_render_layer_attributes(nle::RenderLayer::_0, rla);
        
        globals::init();
    }

    void Nle::cleanup()
    {
        delete m_physics_engine;
        delete m_texture_factory;
        delete m_renderer;
        globals::cleanup();
        delete m_window;
    }

} // namespace nle
