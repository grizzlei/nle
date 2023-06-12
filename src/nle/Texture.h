#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include "Utils.h"

namespace nle
{
    class Texture
    {
    private:
        GLuint m_textureId;
        GLint m_width;
        GLint m_height;
        GLint m_bitDepth;
        std::string m_filePath;

    public:
        Texture(const std::string &filePath);
        ~Texture();
        void loadFromFile(const std::string &filePath);
        void use();
        void unuse();
        void clear();
        unsigned int id();
    };
} // namespace nle

#endif