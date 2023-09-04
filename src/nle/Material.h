#ifndef NLE_MATERIAL_H
#define NLE_MATERIAL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace nle
{
    class Material
    {
    private:
        bool m_accept_light = true;

        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
        float m_specular_intensity;
        float m_shininess;
    public:
        Material();
        Material(float specular_intensity, float shininess);
        ~Material();
        void use(float specular_intensity_location, float shininess_location);

        void set_ambient(glm::vec3 ambient); 
        glm::vec3 ambient() const;

        void set_diffuse(glm::vec3 diffuse); 
        glm::vec3 diffuse() const;

        void set_specular(glm::vec3 specular); 
        glm::vec3 specular() const;

        void set_specular_intensity(float specular_intensity); 
        float specular_intensity() const;

        void set_shininess(float shininess); 
        float shininess() const;

        void set_accept_light(bool accept);
        bool accept_light() const;

    };
} // namespace nle


#endif