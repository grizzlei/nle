#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

#include "Utils.h"

namespace nle
{
    class Shader
    {
    private:
        GLuint m_vbo;
        GLuint m_vao;
        GLuint m_vertex_shader;
        GLuint m_fragment_shader;
        std::string m_vertex_source;
        std::string m_fragment_source;

        std::string load_from_file(const std::string &path);
        void compile_shaders(const std::string &vertex, const std::string &fragment);
        void attach_shaders(GLuint program, const std::string &code, GLenum type);

    protected:
        GLuint m_program;

    public:
        Shader();
        Shader(const std::string &vertex_source, const std::string &fragment_source, bool fromFile = false);
        ~Shader();
        void use();
        void load(const std::string &vertex_source, const std::string &fragment_source, bool fromFile = false);
        void clear();
        unsigned int program() const;
        unsigned int uniform_location(const std::string& uniform) const;      

        friend class Renderer3D;
    };
} // namespace nle

#endif