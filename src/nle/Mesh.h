#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>

#include "Shader.h"
#include "Object3D.h"
#include "Texture.h"

namespace nle
{
    class MeshInstance;
    class MultiMeshInstance;

    enum RenderMode
    {
        Fill = GL_FILL,
        Line = GL_LINE,
        Point = GL_POINT
    };

    class Mesh
    {
    private:
        bool m_isAABBMesh = false;
        unsigned int m_ebo,
            m_vbo,
            m_vao;

        unsigned int m_primitiveType = GL_TRIANGLES;

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;

        Shader *m_shader;
        Texture *m_texture;

        glm::vec3 m_aabbMin;
        glm::vec3 m_aabbMax;
        Mesh *m_aabbMesh;

        void load();

    public:
        Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, Shader *shader, Texture *texture = nullptr, bool isAABBMesh = false);
        virtual ~Mesh();
        std::vector<float> *vertices();
        std::vector<unsigned int> *indices();

        void setTexture(Texture *texture);
        Texture *texture();
        Shader *shader();
        MeshInstance *createInstance();

        friend class Renderer3D;
    };

    class MeshInstance : public Object3D
    {
    private:
        Mesh *m_mesh;

        uint8_t m_renderLayer;
        int m_renderMode;
        bool m_visible;

    public:
        MeshInstance(Mesh *mesh);
        Mesh *mesh();

        void setRenderMode(RenderMode renderMode = RenderMode::Fill);

        void setVisibile(bool visible);
        bool visible() const;

        void setRenderLayer(int layer);
        int renderLayer() const;

        friend class Renderer3D;
    };

    class MultiMesh
    {
    private:
        std::vector<Mesh *> m_meshes;

    public:
        MultiMesh(const std::vector<Mesh *> &meshes = {});
        ~MultiMesh();
        std::vector<Mesh *> *meshes();
        MultiMeshInstance *createInstance();
    };

    class MultiMeshInstance : public Object3D
    {
    public:
        MultiMeshInstance();
        ~MultiMeshInstance();
        friend class Mesh;
    };

} // namespace nle

#endif