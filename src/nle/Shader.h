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
        GLuint m_vertexShader;
        GLuint m_fragmentShader;
        std::string m_sourceVertex;
        std::string m_sourceFragment;

        std::string loadFromFile(const std::string &path);
        void compileShaders(const std::string &vertex, const std::string &fragment);
        void attachShaders(GLuint program, const std::string &code, GLenum type);

    protected:
        GLuint m_shaderProgram;

    public:
        Shader();
        Shader(const std::string &vertexSource, const std::string &fragmentSource, bool fromFile = false);
        ~Shader();
        void use();
        void load(const std::string &vertexSource, const std::string &fragmentSource, bool fromFile = false);
        void clear();
        unsigned int program() const;
        unsigned int uniformLocation(const std::string& uniform) const;      

        friend class Renderer3D;
    };
} // namespace nle

#endif