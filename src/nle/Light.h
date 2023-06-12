#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Object3D.h"

namespace nle
{
    class Light : public Object3D
    {
    private:
        glm::vec3 m_color;
        GLfloat m_ambientIntensity;
        GLfloat m_diffuseIntensity;
        GLfloat m_specularIntensity;
        
        bool m_enabled = false;

    public:
        Light();
        Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
              GLfloat diffuseIntensity);
        ~Light();
        void use(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
                 GLfloat diffuseIntensityLocation, GLfloat diffuseDirectionLocation);
        void setColor(GLfloat red, GLfloat green, GLfloat blue);
        void setAmbientIntensity(GLfloat intensity);
        void setDiffuseIntensity(GLfloat intensity);
        void setSpecularIntensity(GLfloat intensity);
        void setEnabled(bool enabled);
        bool enabled();
    };
} // namespace nle

#endif