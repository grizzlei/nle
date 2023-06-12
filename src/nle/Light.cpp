#include "Light.h"

namespace nle
{
    Light::Light()
        : m_color(glm::vec3(1.f)), m_ambientIntensity(1.f), m_diffuseIntensity(1.f)
    {
        this->setRotation(glm::vec3(0.f, -1.f, 0.f));
    }

    Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
                 GLfloat diffuseIntensity)
    {
        m_color = glm::vec3(red, green, blue);
        m_ambientIntensity = ambientIntensity;
        m_diffuseIntensity = diffuseIntensity;
        this->setRotation(glm::vec3(0.f, -1.f, 0.f));
    }

    Light::~Light()
    {
    }

    void Light::use(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
                    GLfloat diffuseIntensityLocation, GLfloat diffuseDirectionLocation)
    {
        glUniform3f(ambientColorLocation, m_color.x, m_color.y, m_color.z);
        glUniform1f(ambientIntensityLocation, m_ambientIntensity);
        glUniform3f(diffuseDirectionLocation, glm::radians(this->rotation().x), glm::radians(this->rotation().y), glm::radians(this->rotation().z));
        glUniform1f(diffuseIntensityLocation, m_diffuseIntensity);
    }

    void Light::setAmbientIntensity(GLfloat intensity)
    {
        m_ambientIntensity = intensity;
    }

    void Light::setDiffuseIntensity(GLfloat intensity)
    {
        m_diffuseIntensity = intensity;
    }

    void Light::setSpecularIntensity(GLfloat intensity)
    {
        m_specularIntensity = intensity;
    }

    void Light::setEnabled(bool enabled)
    {
        m_enabled = enabled;
    }

    bool Light::enabled()
    {
        return m_enabled;
    }

    void Light::setColor(GLfloat red, GLfloat green, GLfloat blue)
    {
        m_color.r = red;
        m_color.g = green;
        m_color.b = blue;
    }

} // namespace nle
