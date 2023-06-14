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
        loadOBJ(path);
    }

    MultiMeshInstance *Model::createInstance()
    {
        if(!m_multiMesh)
        {
            // m_multiMesh = new MultiMesh();
            prerr("no model loaded to create a MultiMeshInstance");
            return nullptr;
        }

        return m_multiMesh->createInstance();
    }

    bool Model::loadOBJ(const std::string &path)
    {
        objl::Loader loader;

        if (!loader.LoadFile(path))
        {
            return false;
        }
        
        m_multiMesh = new MultiMesh();

        for (const auto &mesh : loader.LoadedMeshes)
        {
            m_vertexGroups.push_back(std::vector<float>());

            for (const auto &v : mesh.Vertices)
            {
                auto &back = m_vertexGroups.back();
                back.push_back(v.Position.X);
                back.push_back(v.Position.Y);
                back.push_back(v.Position.Z);
                back.push_back(v.Normal.X);
                back.push_back(v.Normal.Y);
                back.push_back(v.Normal.Z);
                back.push_back(m_texture ? v.TextureCoordinate.X : 0.f);
                back.push_back(m_texture ? v.TextureCoordinate.Y : 0.f);
            }

            m_indexGroups.push_back(std::vector<unsigned int>());

            for (const auto &i : mesh.Indices)
            {
                m_indexGroups.back().push_back(i);
            }

            Shader *s = m_shader ? m_shader : nle::DEFAULT_SHADER;
            m_multiMesh->meshes()->push_back(new Mesh(m_vertexGroups.back(), m_indexGroups.back(), s, m_texture));
        }

        if ((m_vertexGroups.size() != m_indexGroups.size()) || (m_vertexGroups.empty() || m_indexGroups.empty()))
        {
            prerr(".obj file seems corrupt. vertex groups size does not match with index groups size.");
            m_vertexGroups.clear();
            m_indexGroups.clear();
            delete m_multiMesh;
            return false;
        }

        return true;
    }
} // namespace nle
