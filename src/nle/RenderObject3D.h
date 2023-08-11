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

enum class RenderLayer
{
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7
};

class RenderObject3D : public Object3D
{
protected:
    RenderLayer m_render_layer;
    RenderMode m_render_mode;
    bool m_visible;
public:
    RenderObject3D() = default;

    void set_render_mode(RenderMode render_mode = RenderMode::Fill);
    RenderMode render_mode();

    void set_visible(bool visible);
    bool visible() const;

    void set_render_layer(RenderLayer layer);
    RenderLayer render_layer() const;
};

} // namespace nle
