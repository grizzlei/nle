#include "Model.h"
#include "OBJ_Loader.h"

namespace nle
{
    Model::Model()
    {
    }

    Model::Model(Shader *shader, Texture *texture)
        : m_shader(shader), m_texture(texture)
    {
    }

    Model::Model(const std::string path)
    {
        load_obj(path);
    }

    MeshInstance *Model::create_instance()
    {
        if(!m_mesh)
        {
            // m_multimesh = new MultiMesh();
            prerr("no model loaded to create a MultiMeshInstance");
            return nullptr;
        }

        return m_mesh->create_instance();
    }

    bool Model::load_obj(const std::string &path)
    {
        objl::Loader loader;

        if (!loader.LoadFile(path))
        {
            return false;
        }
        
        // m_multimesh = new MultiMesh();

        // m_vertex_groups.push_back(std::vector<float>());
        // m_index_groups.push_back(std::vector<unsigned int>());
        for (const auto &mesh : loader.LoadedMeshes)
        {

            for (const auto &v : mesh.Vertices)
            {
                // auto &back = m_vertex_groups.back();
                m_vertices.push_back(v.Position.X);
                m_vertices.push_back(v.Position.Y);
                m_vertices.push_back(v.Position.Z);
                m_vertices.push_back(v.Normal.X);
                m_vertices.push_back(v.Normal.Y);
                m_vertices.push_back(v.Normal.Z);
                m_vertices.push_back(m_texture ? v.TextureCoordinate.X : 0.f);
                m_vertices.push_back(m_texture ? v.TextureCoordinate.Y : 0.f);
            }


            for (const auto &i : mesh.Indices)
            {
                m_indices.push_back(i);
            }
        }

        Shader *s = m_shader ? m_shader : nle::DEFAULT_SHADER;
        // m_multimesh->meshes()->push_back(new Mesh(m_vertex_groups.back(), m_index_groups.back(), s, m_texture));
        m_mesh = new Mesh(m_vertices, m_indices, s, m_texture);

        // if ((m_vertex_groups.size() != m_index_groups.size()) || (m_vertex_groups.empty() || m_index_groups.empty()))
        // {
        //     prerr(".obj file seems corrupt. vertex groups size does not match with index groups size.");
        //     m_vertex_groups.clear();
        //     m_index_groups.clear();
        //     // delete m_multimesh;
        //     delete m_mesh;
        //     return false;
        // }

        return true;
    }
    Mesh *Model::mesh() const
    {
        return m_mesh;
    }
} // namespace nle
