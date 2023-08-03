#pragma once

#include <GL/gl.h>

#include "Object3D.h"

namespace nle
{
enum RenderMode
{
    Fill = GL_FILL,
    Line = GL_LINE,
    Point = GL_POINT
};

class RenderObject3D : public Object3D
{
private:
    uint8_t m_render_layer;
    RenderMode m_render_mode;
    bool m_visible;
public:
    RenderObject3D() = default;

    void set_render_mode(RenderMode render_mode = RenderMode::Fill);
    RenderMode render_mode();

    void set_visible(bool visible);
    bool visible() const;

    void set_render_layer(int layer);
    int render_layer() const;
};

} // namespace nle
