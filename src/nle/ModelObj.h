#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "Nle.h"
#include "Mesh.h"
#include "Texture.h"

namespace nle
{
    class ModelOBJ
    {
    private:
        std::vector<std::vector<float>> m_vertexGroups;
        std::vector<std::vector<unsigned int>> m_indexGroups;
        std::vector<Mesh> m_meshes;

        Shader *m_shader = nullptr;
        Texture *m_texture = nullptr;
        MultiMesh *m_multiMesh = nullptr;

    public:
        ModelOBJ();
        ModelOBJ(Shader *shader, Texture *texture = nullptr);
        ModelOBJ(const std::string path);
        MultiMeshInstance *createInstance();
        bool load(const std::string &path);
    };
} // namespace nle

#endif