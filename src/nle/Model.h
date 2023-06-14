#ifndef NLE_MODEL_H
#define NLE_MODEL_H

#include "Nle.h"
#include "Mesh.h"
#include "Texture.h"

namespace nle
{
    class Model
    {
    private:
        std::vector<std::vector<float>> m_vertexGroups;
        std::vector<std::vector<unsigned int>> m_indexGroups;
        std::vector<Mesh> m_meshes;

        Shader *m_shader = nullptr;
        Texture *m_texture = nullptr;
        MultiMesh *m_multiMesh = nullptr;

    public:
        Model();
        Model(Shader *shader, Texture *texture = nullptr);
        Model(const std::string path);
        MultiMeshInstance *createInstance();
        bool loadOBJ(const std::string &path);
        // bool loadGLTF(const std::string& path) .. etc
    };
} // namespace nle

#endif