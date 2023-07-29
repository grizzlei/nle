#ifndef NLE_TERRAIN_H
#define NLE_TERRAIN_H

#include "Mesh.h"

namespace nle
{
    class Terrain
    {
    private:
        unsigned int m_width;
        unsigned int m_height;

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;

    public:
        Terrain(unsigned int width = 1, unsigned int height = 1);
        ~Terrain();
        Mesh * create();
    };
} // namespace nle

#endif