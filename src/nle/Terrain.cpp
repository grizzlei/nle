#include "Terrain.h"

namespace nle
{
    Terrain::Terrain(unsigned int width, unsigned int height)
    {
        m_width = width;
        m_height = height;
    }

    Terrain::~Terrain()
    {
    }

    Mesh *Terrain::createTerrainMesh()
    {
        for(unsigned int i = 0; i < m_height; i++)
        {
            for(unsigned int j = 0; j < m_width; j++)
            {
                
            }
        }

        // Mesh * ret = new Mesh();

        // ret->getVertices() = m_vertices;
        // ret->getIndices() = m_indices;

        return nullptr;
    }
} // namespace nle