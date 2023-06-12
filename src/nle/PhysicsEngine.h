#ifndef NLE_PHYSICS_ENGINE_H
#define NLE_PHYSICS_ENGINE_H

#include "Scene.h"
#include "Signal.hpp"

#include <list>
#include <thread>

namespace nle
{
    struct PhysicsRealm
    {
        float gravity = 9.81f;
        glm::vec3 gravityVector = {0.f, -1.f, 0.f};
        std::list<Object3D *> bodies;
    };

    class PhysicsEngine
    {
    private:
        Signal<Scene *> m_onPhysicsProcess;
        PhysicsRealm *m_realm; // single realm now, multiple in the future
        Scene *m_scene;
        bool m_paused = false;
        bool m_killed = false;
        double m_physicsTimestamp;
        std::thread m_thrPhysics;

        void process(Object3D *body, double deltaTime);
        void processRecursively(Object3D *root, double deltaTime);
        static void runner(void *_this);

    public:
        PhysicsEngine();
        ~PhysicsEngine();
        void attachPhysicsBody(Object3D *body);
        void detachPhsicsBody(Object3D *body);
        void pause();
    };
} // namespace nle

#endif