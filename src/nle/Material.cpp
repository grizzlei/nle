#include "Material.h"

namespace nle
{
    Material::Material()
        : m_specular_intensity(0.0f),
        m_shininess(0.0f)
    {
    }

    Material::Material(float specular_intensity, float shininess)
    {
        m_specular_intensity = specular_intensity;
        m_shininess = shininess;
    }

    Material::~Material()
    {
    }

    void Material::use(float specular_intensity_location, float shininess_location)
    {
        glUniform1f(specular_intensity_location, m_specular_intensity);
        glUniform1f(shininess_location, m_shininess);
    }
} // namespace nle
