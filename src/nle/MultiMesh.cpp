#include "MultiMesh.h"

namespace nle
{

MultiMesh::MultiMesh(Mesh *m)
    : m_mesh(m)
{
}

MultiMesh::~MultiMesh()
{

}

Mesh *MultiMesh::mesh() const
{
    return m_mesh;
}

const std::vector<MeshInstance*>& MultiMesh::instances() const
{
    return m_mesh_instances;
}

const std::vector<glm::vec3>& MultiMesh::positions() const
{
    return m_positions;
}

const std::vector<glm::vec3>& MultiMesh::rotations() const
{
    return m_rotations;
}

const std::vector<glm::vec3>& MultiMesh::scales() const
{
    return m_scales;
}

MeshInstance *MultiMesh::create_mesh_instance(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    auto *mi = m_mesh->create_instance();
    mi->set_position(position);
    mi->set_rotation(rotation);
    mi->set_scale(scale);

    m_positions.push_back(position);
    m_rotations.push_back(rotation);
    m_scales.push_back(scale);
    m_mesh_instances.push_back(mi);
    return mi;
}

MultiMeshInstance *MultiMesh::create_instance()
{
    return new MultiMeshInstance(this);
}

MultiMeshInstance::MultiMeshInstance(MultiMesh *mm)
    : m_multimesh(mm)
{
}

MultiMeshInstance::~MultiMeshInstance()
{
}

MultiMesh *MultiMeshInstance::multimesh() const
{
    return m_multimesh;
}

// void MultiMeshInstance::set_render_mode(RenderMode render_mode)
// {
//     m_render_mode = render_mode;
//     for (auto *c : this->children())
//     {
//         if (MeshInstance *m = dynamic_cast<MeshInstance *>(c))
//         {
//             m->set_render_mode(render_mode);
//         }
//     }
// }

// void MultiMeshInstance::set_visible(bool visible)
// {
//     m_visible = visible;
// }

// bool MultiMeshInstance::visible() const
// {
//     return m_visible;
// }

// void MultiMeshInstance::set_render_layer(int layer)
// {
//     m_render_layer = layer;
// }

// int MultiMeshInstance::render_layer() const
// {
//     return m_render_layer;
// }

} // namespace nle
