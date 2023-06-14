#include "PhysicsEngine.h"

#define NLE_PHYSICS_PROCESS_SLEEP_TIME 16666

namespace nle
{

    PhysicsEngine::PhysicsEngine()
        : m_realm(new PhysicsRealm)
    {
        m_physicsTimestamp = get_time_sec();
        m_thrPhysics = std::thread(&PhysicsEngine::runner, this);
    }

    PhysicsEngine::~PhysicsEngine()
    {
        m_killed = true;
        
        if(m_thrPhysics.joinable())
            m_thrPhysics.join();

        delete m_realm;
    }

    void PhysicsEngine::attachPhysicsBody(Object3D *body)
    {
        m_realm->bodies.push_back(body);
        for(auto * c : body->children())
        {
            attachPhysicsBody(c);
        }
    }

    void PhysicsEngine::detachPhsicsBody(Object3D *body)
    {
        auto it = std::find(m_realm->bodies.begin(), m_realm->bodies.end(), body);
        if(it != m_realm->bodies.end())
        {
            m_realm->bodies.erase(it);
        }
    }

    void PhysicsEngine::bindPhysicsProcessCallback(std::function<void(Object3D * object, double delta)> callback)
    {
        m_onPhysicsProcess.bindCallback(callback);
    }

    void PhysicsEngine::bindPhysicsTickCallback(std::function<void(double)> callback)
    {
        m_onPhysicsTick.bindCallback(callback);
    }

    void PhysicsEngine::process(Object3D *body, double deltaTime)
    {
        glm::vec3 d = m_realm->gravity * m_realm->gravityVector * (float)deltaTime;
        body->setVelocity(body->velocity() + d);

        // @TODO: check for collisions and move if there's no obstacle

        body->setPosition(body->position() + body->velocity());

        m_onPhysicsProcess.emit(body, deltaTime);
    }

    void PhysicsEngine::processRecursively(Object3D *root, double deltaTime)
    {
        process(root, deltaTime);

        for(auto * c : root->children())
        {
            processRecursively(c, deltaTime);
        }
    }

    void PhysicsEngine::runner(void *_this)
    {
        PhysicsEngine *p = static_cast<PhysicsEngine*>(_this);
        if(p)
        {

            while(!p->m_killed)
            {
                double dtime = get_time_sec() - p->m_physicsTimestamp;
                for(auto * i : p->m_realm->bodies)
                {
                    p->processRecursively(i, dtime);
                }

                p->m_onPhysicsTick.emit(dtime);
                p->m_physicsTimestamp = get_time_sec();
                // 60 hertz constant physics processing.
                std::this_thread::sleep_for(std::chrono::microseconds(NLE_PHYSICS_PROCESS_SLEEP_TIME));
            }
        }
    }
} // namespace nle
