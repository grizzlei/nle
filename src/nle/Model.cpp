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

    MultiMeshInstance *Model::create_instance()
    {
        if(!m_multimesh)
        {
            // m_multimesh = new MultiMesh();
            prerr("no model loaded to create a MultiMeshInstance");
            return nullptr;
        }

        return m_multimesh->create_instance();
    }

    bool Model::load_obj(const std::string &path)
    {
        objl::Loader loader;

        if (!loader.LoadFile(path))
        {
            return false;
        }
        
        m_multimesh = new MultiMesh();

        for (const auto &mesh : loader.LoadedMeshes)
        {
            m_vertex_groups.push_back(std::vector<float>());

            for (const auto &v : mesh.Vertices)
            {
                auto &back = m_vertex_groups.back();
                back.push_back(v.Position.X);
                back.push_back(v.Position.Y);
                back.push_back(v.Position.Z);
                back.push_back(v.Normal.X);
                back.push_back(v.Normal.Y);
                back.push_back(v.Normal.Z);
                back.push_back(m_texture ? v.TextureCoordinate.X : 0.f);
                back.push_back(m_texture ? v.TextureCoordinate.Y : 0.f);
            }

            m_index_groups.push_back(std::vector<unsigned int>());

            for (const auto &i : mesh.Indices)
            {
                m_index_groups.back().push_back(i);
            }

            Shader *s = m_shader ? m_shader : nle::DEFAULT_SHADER;
            m_multimesh->meshes()->push_back(new Mesh(m_vertex_groups.back(), m_index_groups.back(), s, m_texture));
        }

        if ((m_vertex_groups.size() != m_index_groups.size()) || (m_vertex_groups.empty() || m_index_groups.empty()))
        {
            prerr(".obj file seems corrupt. vertex groups size does not match with index groups size.");
            m_vertex_groups.clear();
            m_index_groups.clear();
            delete m_multimesh;
            return false;
        }

        return true;
    }
} // namespace nle
