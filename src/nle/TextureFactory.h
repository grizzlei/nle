#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H

#include <unordered_map>

#include "Texture.h"

namespace nle
{
    class TextureFactory
    {
    private:
        std::unordered_map<std::string, Texture *> m_textures;
    public:
        TextureFactory(/* args */);
        ~TextureFactory();
        bool load(const std::string& path, const std::string& id);
        Texture *get(const std::string& textureId);
        Texture *load_and_get(const std::string& path, const std::string& id);
    };
    
} // namespace nle


#endif