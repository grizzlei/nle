#include "Model.h"

#include "OBJ_Loader.h"
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"

#include <algorithm>
#include <filesystem>

namespace nle
{
    Model::Model(const std::string &path, Shader *shader, Texture *texture)
        : m_shader(shader), m_texture(texture)
    {
        std::string fmt = path.substr(path.find_last_of("."));
        m_name = path.substr(path.find_last_of('/') + 1);

        std::transform(fmt.begin(), fmt.end(), fmt.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });

        if (fmt == ".obj")
        {
            load_obj(path);
        }
    }

    void Model::set_name(const std::string &name)
    {
        m_name = name;
    }

    const std::string &Model::name() const
    {
        return m_name;
    }

    MultiMeshInstance *Model::create_instance()
    {
        auto *ret = m_multimesh->create_instance();
        ret->m_source = m_name;
        return ret;
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
            std::vector<float> vertices;
            std::vector<unsigned int> indices;

            Shader *s = m_shader ? m_shader : nle::DEFAULT_SHADER;
            Texture *t = nullptr;

            if (!mesh.MeshMaterial.map_Kd.empty())
            {

                auto texpath = std::filesystem::path(mesh.MeshMaterial.map_Kd);

                if (texpath.is_absolute())
                {
                    if (std::filesystem::exists(texpath))
                    {
                        t = new Texture(texpath);
                    }
                }
                else if (texpath.is_relative())
                {
                    for (auto const &dir_entry : std::filesystem::recursive_directory_iterator(std::filesystem::path(path).parent_path()))
                    {
                        if (dir_entry.path().filename() == texpath.filename())
                        {
                            t = new Texture(dir_entry.path());
                        }
                    }
                }
            }

            for (const auto &v : mesh.Vertices)
            {
                vertices.push_back(v.Position.X);
                vertices.push_back(v.Position.Y);
                vertices.push_back(v.Position.Z);
                vertices.push_back(v.Normal.X);
                vertices.push_back(v.Normal.Y);
                vertices.push_back(v.Normal.Z);
                vertices.push_back(mesh.MeshMaterial.Kd.X);
                vertices.push_back(mesh.MeshMaterial.Kd.Y);
                vertices.push_back(mesh.MeshMaterial.Kd.Z);
                vertices.push_back(v.TextureCoordinate.X);
                vertices.push_back(v.TextureCoordinate.Y);
            }

            for (const auto &i : mesh.Indices)
            {
                indices.push_back(i);
            }

            m_multimesh->meshes().push_back(new Mesh(vertices, indices, s, t ? t : m_texture));
        }
        return true;
    }

    bool Model::load_gltf(const std::string &path)
    {
        // tinygltf::Model model;
        // tinygltf::TinyGLTF loader;
        // std::string err, warn;

        // bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path.c_str());
        // if(!warn.empty())
        // {
        //     prwar("%s",warn.c_str());
        // }
        // if(!err.empty())
        // {
        //     prerr("%s",err.c_str());
        //     return ret;
        // }

        // m_multimesh = new MultiMesh();
        // for(const auto& it : model.meshes)
        // {
        //     std::vector<float> vertices;
        //     std::vector<unsigned int> indices;

        //     for(const auto& it1 : it.primitives)
        //     {
        //         for(const auto& it2 : it1.targets)
        //     }

        //     Shader *s = m_shader ? m_shader : DEFAULT_SHADER;
        //     m_multimesh->meshes().push_back(new Mesh(vertices, indices, s, m_texture));
        // }

        // return ret;
        return path.empty();
    }

    MultiMesh *Model::multimesh() const
    {
        return m_multimesh;
    }
} // namespace nle
