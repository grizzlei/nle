#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace nle
{
    Texture::Texture(const std::string &filePath)
    {
        clear();
        loadFromFile((m_filePath = filePath));
    }

    Texture::~Texture()
    {
        clear();
    }

    void Texture::loadFromFile(const std::string &filePath)
    {
        if(m_textureId != 0)
            return;
        
        stbi_set_flip_vertically_on_load(true);

        unsigned char *data = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bitDepth, 0);
        if (!data)
        {
            prerr("Texture::loadFromFile(): nothing here %s", m_filePath.c_str());
            return;
        }

        int internalFormat = GL_RGB;
        if(filePath.find(".png") != std::string::npos)
        {
            internalFormat = GL_RGBA;
        }

        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }

    void Texture::use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }

    void Texture::unuse()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::clear()
    {
        if (m_textureId != 0)
            glDeleteTextures(1, &m_textureId);
        m_textureId = 0;
        m_height = 0;
        m_width = 0;
        m_bitDepth = 0;
        m_filePath.clear();
    }
    
    unsigned int Texture::id()
    {
        return m_textureId;
    }
} // namespace nle
