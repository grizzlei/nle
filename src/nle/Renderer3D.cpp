#include "Renderer3D.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define NLE_INPUT_PROCESS_SLEEP_TIME            16666
#define NLE_RENDER_MAX_ELAPSED_TIME_SECONDS     0.016666

namespace nle
{
    Renderer3D::Renderer3D(Window *renderTarget)
        : m_parentWindow(renderTarget), m_maxRenderDistance(10000.f), m_timeStrictMode(false)
    {
        for (auto &it : m_renderLayerAttributes)
        {
            it.second.renderDistance = m_maxRenderDistance;
        }

        initialize();
        m_parentWindow->setDrawCallback(
            [this]()
            {
                glViewport(0, 0, this->m_parentWindow->m_width, this->m_parentWindow->m_height);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                this->renderRecursively(this->m_rootScene);
                m_renderTimestamp = get_time_sec();
            });

        m_inputTimestamp = get_time_sec();
        m_thrInput = std::thread(
            [this]()
            {
                while (!this->m_parentWindow->m_closed)
                {
                    this->processKeyboardInput();
                    this->processMouseInput(this->m_parentWindow->m_mouseDelta.x, this->m_parentWindow->m_mouseDelta.y);
                    this->m_parentWindow->m_mouseDelta = glm::vec2(0.f);

                    // 60 fps constant input processing.
                    std::this_thread::sleep_for(std::chrono::microseconds(NLE_INPUT_PROCESS_SLEEP_TIME));
                }
            });
    }

    Renderer3D::~Renderer3D()
    {
        if (m_thrInput.joinable())
            m_thrInput.join();
    }

    void Renderer3D::renderRecursively(Object3D *root)
    {
        if (!root)
        {
            prerr("root spatial is null");
            return;
        }

        if(m_timeStrictMode)
        {
            double now = get_time_sec();

            if((now - m_renderTimestamp) > NLE_RENDER_MAX_ELAPSED_TIME_SECONDS)
            {
                m_renderTimestamp = now;
                return;
            }
        }

        if (MeshInstance *m = dynamic_cast<MeshInstance *>(root))
        {
            if (m->visible())
            {
                render(m);
            }
        }

        for (auto *c : root->children())
        {
            renderRecursively(c);
        }
    }

    void Renderer3D::initialize()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthFunc(GL_LEQUAL);
        glClearColor(1.f, 1.f, 1.f, 1.f);
    }

    void Renderer3D::processKeyboardInput()
    {
        constexpr double limit = 1.f / 60.f;
        double now = get_time_sec();

        if ((now - m_inputTimestamp) < limit)
        {
            return;
        }

        Camera *c = m_rootScene->camera();
        glm::vec3 dposf = c->m_front * c->m_speed;
        glm::vec3 dposr = c->m_right * c->m_speed;
        glm::vec3 dposu = c->m_up * c->m_speed;

        if (m_parentWindow->m_keys[GLFW_KEY_W])
        {
            c->setPosition((c->position() += dposf));
        }
        if (m_parentWindow->m_keys[GLFW_KEY_S])
        {
            c->setPosition((c->position() -= dposf));
        }
        if (m_parentWindow->m_keys[GLFW_KEY_D])
        {
            c->setPosition((c->position() += dposr));
        }
        if (m_parentWindow->m_keys[GLFW_KEY_A])
        {
            c->setPosition((c->position() -= dposr));
        }
        if (m_parentWindow->m_keys[GLFW_KEY_E])
        {
            c->setPosition((c->position() += dposu));
        }
        if (m_parentWindow->m_keys[GLFW_KEY_Q])
        {
            c->setPosition((c->position() -= dposu));
        }

        m_inputTimestamp = get_time_sec();
    }

    void Renderer3D::processMouseInput(GLfloat dx, GLfloat dy)
    {
        if (m_rootScene)
        {
            Camera *c = m_rootScene->camera();
            if (c)
            {
                dx *= c->turnSpeed();
                dy *= c->turnSpeed();

                glm::vec3 camrot = c->rotation();

                GLfloat pitch = camrot.x + dy;
                GLfloat yaw = camrot.y + dx;

                if (pitch > 89.f)
                {
                    pitch = 89.f;
                }
                if (pitch < -89.f)
                {
                    pitch = -89.f;
                }

                c->setRotation({pitch, yaw, 0.f});
                c->update();
            }
        }
    }

    void Renderer3D::render(Object3D *d)
    {
        if (!d)
        {
            return;
        }

        MeshInstance *mi = dynamic_cast<MeshInstance *>(d);

        if (!mi)
        {
            return;
        }

        if (!m_renderLayerAttributes[mi->m_renderLayer].visible)
        {
            return;
        }

        if (glm::distance(static_cast<Scene *>(d->root())->camera()->position(), d->position()) >
            m_renderLayerAttributes[mi->m_renderLayer].renderDistance)
        {
            return;
        }

        Scene *s = static_cast<Scene *>(d->root());
        if (!s)
        {
            return;
        }

        glPolygonMode(GL_FRONT_AND_BACK, mi->m_renderMode);

        mi->mesh()->shader()->use();

        GLuint uniformModel = mi->mesh()->shader()->uniformLocation("model");
        GLuint uniformProjection = mi->mesh()->shader()->uniformLocation("projection");
        GLuint uniformView = mi->mesh()->shader()->uniformLocation("view");
        GLuint uniformAmbientIntensity = mi->mesh()->shader()->uniformLocation("directionalLight.ambientIntensity");
        GLuint uniformAmbientColor = mi->mesh()->shader()->uniformLocation("directionalLight.color");
        GLuint uniformDiffuseDirection = mi->mesh()->shader()->uniformLocation("directionalLight.direction");
        GLuint uniformDiffuseIntensity = mi->mesh()->shader()->uniformLocation("directionalLight.diffuseIntensity");
        GLuint uniformLightingEnabled = mi->mesh()->shader()->uniformLocation("lightingEnabled");
        GLuint uniformTextureEnabled = mi->mesh()->shader()->uniformLocation("textureEnabled");

        if (mi->mesh()->texture())
        {
            mi->mesh()->texture()->use();
            glUniform1i(uniformTextureEnabled, 1);
        }
        else
        {
            glUniform1i(uniformTextureEnabled, 0);
        }

        if (s->light()->enabled())
        {
            glUniform1i(uniformLightingEnabled, 1);
            s->light()->use(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDiffuseDirection);
        }
        else
        {
            glUniform1i(uniformLightingEnabled, 0);
        }

        glm::mat4 model = glm::mat4(1.f);
        glm::mat4 projection = glm::perspective(45.f, (GLfloat)m_parentWindow->m_width / (GLfloat)m_parentWindow->m_height, 0.1f, m_maxRenderDistance);

        model = glm::translate(model, d->position());
        model = glm::rotate(model, glm::radians(d->rotation().x), glm::vec3(1.f, 0.f, 0.f));
        model = glm::rotate(model, glm::radians(d->rotation().y), glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, glm::radians(d->rotation().z), glm::vec3(0.f, 0.f, 1.f));
        model = glm::scale(model, d->scale());

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(s->camera()->getViewMatrix()));

        glBindVertexArray(mi->mesh()->m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mi->mesh()->m_ebo);
        glDrawElements(mi->mesh()->m_primitiveType, mi->mesh()->indices()->size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glUseProgram(0);

        if (mi->mesh()->texture())
            mi->mesh()->texture()->unuse();
    }

    void Renderer3D::setRootScene(Scene *root)
    {
        m_rootScene = root;
    }

    Scene *Renderer3D::rootScene() const
    {
        return m_rootScene;
    }

    void Renderer3D::setRenderLayerAttributes(RenderLayer layer, RenderLayerAttributes attributes)
    {
        m_renderLayerAttributes[layer] = attributes;
    }

    RenderLayerAttributes Renderer3D::renderLayerAttributes(RenderLayer layer)
    {
        return m_renderLayerAttributes[layer];
    }

} // namespace nle
