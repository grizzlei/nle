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
        bool m_is_AABB_mesh = false;
        unsigned int m_ebo,
            m_vbo,
            m_vao;

        unsigned int m_primitive_type = GL_TRIANGLES;

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;

        Shader *m_shader;
        Texture *m_texture;

        glm::vec3 m_aabb_min;
        glm::vec3 m_aabb_max;
        Mesh *m_aabb_Mesh;

        void load();

    public:
        Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, Shader *shader, Texture *texture = nullptr, bool is_AABB_mesh = false);
        virtual ~Mesh();
        std::vector<float> *vertices();
        std::vector<unsigned int> *indices();

        void set_texture(Texture *texture);
        Texture *texture();
        Shader *shader();
        MeshInstance *create_instance();

        friend class Renderer3D;
    };

    class MeshInstance : public Object3D
    {
    private:
        Mesh *m_mesh;

        uint8_t m_render_layer;
        int m_render_mode;
        bool m_visible;

    public:
        MeshInstance(Mesh *mesh);
        Mesh *mesh();

        void set_render_mode(RenderMode render_mode = RenderMode::Fill);

        void set_visible(bool visible);
        bool visible() const;

        void set_render_layer(int layer);
        int render_layer() const;

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
        MultiMeshInstance *create_instance();
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