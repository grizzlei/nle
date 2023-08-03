#pragma once

#include "Mesh.h"
#include "RenderObject3D.h"

namespace nle
{
    class MultiMeshInstance;
    
    class MultiMesh
    {
    private:
        Mesh *m_mesh;
        std::vector<MeshInstance*> m_mesh_instances;
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_rotations;
        std::vector<glm::vec3> m_scales;
    public:
        MultiMesh(Mesh * m);
        ~MultiMesh();
        Mesh *mesh() const;
        const std::vector<MeshInstance*>& instances() const;
        const std::vector<glm::vec3>& positions() const;
        const std::vector<glm::vec3>& rotations() const;
        const std::vector<glm::vec3>& scales() const;
        MeshInstance *create_mesh_instance(glm::vec3 position = glm::vec3(1.f), glm::vec3 rotation = glm::vec3(1.f), glm::vec3 scale = glm::vec3(1.f));
        MultiMeshInstance *create_instance();
    };

    class MultiMeshInstance : public RenderObject3D
    {
    private:
        MultiMesh *m_multimesh;
        uint8_t m_render_layer;
        int m_render_mode;
        bool m_visible;
    public:
        MultiMeshInstance(MultiMesh *mm);
        ~MultiMeshInstance();
        MultiMesh *multimesh() const;

        // void set_render_mode(RenderMode render_mode = RenderMode::Fill);

        // void set_visible(bool visible);
        // bool visible() const;

        // void set_render_layer(int layer);
        // int render_layer() const;
    };
} // namespace nle
