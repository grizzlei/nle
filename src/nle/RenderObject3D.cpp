#include "RenderObject3D.h"

namespace nle
{

void RenderObject3D::set_render_mode(RenderMode render_mode)
{
    m_render_mode = render_mode;
    for (auto *c : this->children())
    {
        if (RenderObject3D *r = dynamic_cast<RenderObject3D *>(c))
        {
            r->set_render_mode(render_mode);
        }
    }
}

RenderMode RenderObject3D::render_mode()
{
    return m_render_mode;
}

void RenderObject3D::set_visible(bool visible)
{
    m_visible = visible;
}

bool RenderObject3D::visible() const
{
    return m_visible;
}

void RenderObject3D::set_render_layer(int layer)
{
    m_render_layer = layer;
}

int RenderObject3D::render_layer() const
{
    return m_render_layer;
}

} // namespace nle

    // void MeshInstance::set_render_mode(RenderMode render_mode)
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

    // void MeshInstance::set_visible(bool visible)
    // {
    //     m_visible = visible;
    // }

    // bool MeshInstance::visible() const
    // {
    //     return m_visible;
    // }

    // void MeshInstance::set_render_layer(int layer)
    // {
    //     m_render_layer = layer;
    // }

    // int MeshInstance::render_layer() const
    // {
    //     return m_render_layer;
    // }