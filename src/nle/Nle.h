#ifndef NLE_H
#define NLE_H

#include "Shader.h"
#include "Renderer3D.h"
#include "PhysicsEngine.h"
#include "TextureFactory.h"

namespace nle
{
    extern Shader *DEFAULT_SHADER;
    
    class Nle
    {
    private:
        Window *m_window;
        Renderer3D *m_renderer;
        TextureFactory *m_textureFactory;
        PhysicsEngine *m_physicsEngine;

        void initialize();
        void cleanup();
    public:
        Nle(/* args */);
        ~Nle();
        Window *window();
        Renderer3D *renderer();
        TextureFactory *textureFactory();
        Scene *currentScene();
        PhysicsEngine *physicsEngine();
        void run();
    };

} // namespace nle

#endif