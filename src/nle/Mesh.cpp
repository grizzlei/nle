#include "Mesh.h"
#include <stdexcept>
#include <limits>

namespace nle
{
    Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, Shader *shader, Texture *texture, bool isAABBMesh)
        : m_vertices(vertices), m_indices(indices), m_shader(shader), m_texture(texture), m_isAABBMesh(isAABBMesh)
    {
        if (!m_isAABBMesh)
        {
            // compute aabb here.
            unsigned int blockSize = 8U; // 3 vertices, 3 normals, 2 texture coords
            unsigned int range = vertices.size() / blockSize;

            m_aabbMax = glm::vec3(std::numeric_limits<float>::min());
            m_aabbMin = glm::vec3(std::numeric_limits<float>::max());

            for (unsigned int i = 0; i < range; i++)
            {
                float &vx = m_vertices[blockSize * i];
                float &vy = m_vertices[blockSize * i + 1];
                float &vz = m_vertices[blockSize * i + 2];

                if (vx < m_aabbMin.x)
                {
                    m_aabbMin.x = vx;
                }
                else if (vx > m_aabbMax.x)
                {
                    m_aabbMax.x = vx;
                }
                if (vy < m_aabbMin.y)
                {
                    m_aabbMin.y = vy;
                }
                else if (vy > m_aabbMax.y)
                {
                    m_aabbMax.y = vy;
                }
                if (vz < m_aabbMin.z)
                {
                    m_aabbMin.z = vz;
                }
                else if (vz > m_aabbMax.z)
                {
                    m_aabbMax.z = vz;
                }
            }

            // 0 - 1 - 5 - 4 - 0 - 3 - 7 - 4 - 5 - 6 - 7 - 3 - 2 - 6 - 5 - 1 - 2 
            // -----------------   ---------   ---------  ----------   ---------
            //     front		      lef        btm         bck        right
            m_aabbMesh = new Mesh(
                {
                    m_aabbMin.x, m_aabbMax.y, m_aabbMax.z, 0.f, 0.f, 0.f, 0.f, 0.f, // top left front,
                    m_aabbMax.x, m_aabbMax.y, m_aabbMax.z, 0.f, 0.f, 0.f, 0.f, 0.f, // top right front
                    m_aabbMax.x, m_aabbMax.y, m_aabbMin.z, 0.f, 0.f, 0.f, 0.f, 0.f, // top right back
                    m_aabbMin.x, m_aabbMax.y, m_aabbMin.z, 0.f, 0.f, 0.f, 0.f, 0.f, // top left back
                    m_aabbMin.x, m_aabbMin.y, m_aabbMax.z, 0.f, 0.f, 0.f, 0.f, 0.f, // bottom left front
                    m_aabbMax.x, m_aabbMin.y, m_aabbMax.z, 0.f, 0.f, 0.f, 0.f, 0.f, // bottom right front
                    m_aabbMax.x, m_aabbMin.y, m_aabbMin.z, 0.f, 0.f, 0.f, 0.f, 0.f, // bottom right back
                    m_aabbMin.x, m_aabbMin.y, m_aabbMin.z, 0.f, 0.f, 0.f, 0.f, 0.f  // bottom left back
                },
                {
                    0, 1, 5, 4, 0, 3, 7, 4, 5, 6, 7, 3, 2, 6, 5, 1, 2
                },
                m_shader,
                nullptr,
                true);

            m_aabbMesh->m_primitiveType = GL_LINE_STRIP;
            prdbg("aabb created.");
        }

        load();
    }

    Mesh::~Mesh()
    {
        if (m_ebo != 0)
        {
            glDeleteBuffers(1, &m_ebo);
        }
        if (m_vbo != 0)
        {
            glDeleteBuffers(1, &m_vbo);
        }
        if (m_vao != 0)
        {
            glDeleteBuffers(1, &m_vao);
        }
    }

    void Mesh::load()
    {
        // vertex array object
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // vertex buffer object
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);

        // element buffer offset (index buffer object)
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), m_indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]) * 8, (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]) * 8, (void *)(sizeof(m_vertices[0]) * 3));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]) * 8, (void *)(sizeof(m_vertices[0]) * 6));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    std::vector<float> *Mesh::vertices()
    {
        return &m_vertices;
    }

    std::vector<unsigned int> *Mesh::indices()
    {
        return &m_indices;
    }

    void Mesh::setTexture(Texture *texture)
    {
        m_texture = texture;
    }

    Texture *Mesh::texture()
    {
        return m_texture;
    }

    Shader *Mesh::shader()
    {
        return m_shader;
    }

    MeshInstance *Mesh::createInstance()
    {
        MeshInstance *mi = new MeshInstance(this);
        if (!m_isAABBMesh)
        {
            mi->addChild(this->m_aabbMesh->createInstance());
        }
        return mi;
    }

    MeshInstance::MeshInstance(Mesh *mesh)
        : m_mesh(mesh), m_visible(true), m_renderLayer(0)
    {
    }

    Mesh *MeshInstance::mesh()
    {
        return m_mesh;
    }

    void MeshInstance::setRenderMode(RenderMode renderMode)
    {
        m_renderMode = renderMode;
        for (auto *c : this->children())
        {
            if (MeshInstance *m = dynamic_cast<MeshInstance *>(c))
            {
                m->setRenderMode(renderMode);
            }
        }
    }

    void MeshInstance::setVisibile(bool visible)
    {
        m_visible = visible;
    }

    bool MeshInstance::visible() const
    {
        return m_visible;
    }

    void MeshInstance::setRenderLayer(int layer)
    {
        m_renderLayer = layer;
    }

    int MeshInstance::renderLayer() const
    {
        return m_renderLayer;
    }

    MultiMesh::MultiMesh(const std::vector<Mesh *> &meshes)
        : m_meshes(meshes)
    {
    }

    MultiMesh::~MultiMesh()
    {
        for(auto * i : m_meshes)
        {
            delete i;
        }
    }

    std::vector<Mesh *> *MultiMesh::meshes()
    {
        return &m_meshes;
    }

    MultiMeshInstance *MultiMesh::createInstance()
    {
        MultiMeshInstance *mm = new MultiMeshInstance();

        for (auto *i : m_meshes)
        {
            mm->addChild(i->createInstance());
        }

        return mm;
    }

    MultiMeshInstance::MultiMeshInstance()
    {
    }

    MultiMeshInstance::~MultiMeshInstance()
    {
    }

} // namespace nle
