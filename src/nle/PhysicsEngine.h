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
        Signal<Object3D*, double> m_on_physics_process;
        Signal<double> m_on_physics_tick;
        PhysicsRealm *m_realm; // single realm now, multiple in the future
        Scene *m_scene;
        bool m_paused = false;
        bool m_killed = false;
        double m_physics_timeval;
        std::thread m_thr_physics;

        void process(Object3D *body, double delta_time);
        void process_recursively(Object3D *root, double delta_time);
        static void runner(void *_this);

    public:
        PhysicsEngine();
        ~PhysicsEngine();
        void attach_physics_body(Object3D *body);
        void detach_physics_body(Object3D *body);
        void bind_physics_process_callback(std::function<void(Object3D* object, double delta)> callback);
        void bind_physics_tick_callback(std::function<void(double)> callback);
        // void pause();
    };
} // namespace nle

#endif