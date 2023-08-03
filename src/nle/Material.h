#ifndef NLE_MATERIAL_H
#define NLE_MATERIAL_H

#include <GL/glew.h>

namespace nle
{
    class Material
    {
    private:
        float m_specular_intensity;
        float m_shininess;
    public:
        Material();
        Material(float specular_intensity, float shininess);
        ~Material();
        void use(float specular_intensity_location, float shininess_location);
    };
} // namespace nle


#endif