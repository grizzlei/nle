#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include "Utils.h"

namespace nle
{
    class Texture
    {
    private:
        GLuint m_texture_id;
        GLint m_width;
        GLint m_height;
        GLint m_bitDepth;
        std::string m_file_path;

    public:
        Texture(const std::string &file_path);
        ~Texture();
        void load_from_file(const std::string &file_path);
        void use();
        void unuse();
        void clear();
        unsigned int id();
    };
} // namespace nle

#endif