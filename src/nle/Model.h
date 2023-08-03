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
        // std::vector<std::vector<float>> m_vertex_groups;
        // std::vector<std::vector<unsigned int>> m_index_groups;
        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;
        // std::vector<Mesh> m_meshes;

        Shader *m_shader = nullptr;
        Texture *m_texture = nullptr;
        // MultiMesh *m_multimesh = nullptr;
        Mesh *m_mesh = nullptr;

    public:
        Model();
        Model(Shader *shader, Texture *texture = nullptr);
        Model(const std::string path);
        MeshInstance *create_instance();
        bool load_obj(const std::string &path);
        Mesh *mesh() const;
        // bool loadGLTF(const std::string& path) .. etc
    };
} // namespace nle

#endif