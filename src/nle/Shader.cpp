#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace nle
{

    Shader::Shader()
    {
    }

    Shader::Shader(const std::string &vertex_source, const std::string &fragment_source, bool fromFile)
    {
        load(vertex_source, fragment_source, fromFile);
    }

    Shader::~Shader()
    {
        clear();
    }

    std::string Shader::load_from_file(const std::string &path)
    {
        std::ifstream ifs(path);
        std::stringstream iss;
        iss << ifs.rdbuf();
        return iss.str();
    }

    void Shader::attach_shaders(GLuint program, const std::string &code, GLenum type)
    {
        std::string shaderTypeStr;
        switch (type)
        {
        case GL_VERTEX_SHADER:
            shaderTypeStr = "vertex shader";
            break;
        case GL_FRAGMENT_SHADER:
            shaderTypeStr = "fragment shader";
            break;
        }

        GLuint shader = glCreateShader(type);
        const GLchar *code_[1];
        code_[0] = code.c_str();

        GLint codeLen[1];
        codeLen[0] = code.length();

        glShaderSource(shader, 1, code_, codeLen);
        glCompileShader(shader);

        GLint result = 0;
        GLchar errLog[1024] = {0};

        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            glGetShaderInfoLog(shader, sizeof(errLog), NULL, errLog);
            std::cerr << "error compiling " << shaderTypeStr << ": '" << errLog << "'" << std::endl;
            return;
        }

        glAttachShader(program, shader);
    }

    void Shader::compile_shaders(const std::string &vertex, const std::string &fragment)
    {
        m_program = glCreateProgram();

        if (!m_program)
        {
            std::cerr << "error creating program" << std::endl;
            return;
        }

        GLint result = 0;
        GLchar errLog[1024] = {0};

        attach_shaders(m_program, vertex, GL_VERTEX_SHADER);
        attach_shaders(m_program, fragment, GL_FRAGMENT_SHADER);

        glLinkProgram(m_program);
        glGetProgramiv(m_program, GL_LINK_STATUS, &result);

        if (!result)
        {
            glGetProgramInfoLog(m_program, sizeof(errLog), NULL, errLog);
            std::cerr << "error linking program: '" << errLog << "'" << std::endl;
            return;
        }

        glValidateProgram(m_program);
        glGetProgramiv(m_program, GL_VALIDATE_STATUS, &result);

        if (!result)
        {
            glGetProgramInfoLog(m_program, sizeof(errLog), NULL, errLog);
            std::cerr << "error validating program: '" << errLog << "'" << std::endl;
            return;
        }

        return;
    }

    void Shader::use()
    {
        glUseProgram(m_program);
    }
    
    void Shader::load(const std::string &vertex_source, const std::string &fragment_source, bool fromFile)
    {   
        if (fromFile)
        {
            compile_shaders(load_from_file(vertex_source), load_from_file(fragment_source));
        }
        else
        {
            compile_shaders(vertex_source, fragment_source);
        }

        prdbg("finished compiling %d", m_program);
    }

    void Shader::clear()
    {
        if(m_vertex_shader != 0)
        {
            glDeleteShader(m_vertex_shader);
        }
        if(m_fragment_shader != 0)
        {
            glDeleteShader(m_fragment_shader);
        }
    }

    unsigned int Shader::program() const
    {
        return m_program;
    }

    unsigned int Shader::uniform_location(const std::string &uniform) const
    {
        return glGetUniformLocation(m_program, uniform.c_str());
    }
} // namespace nle
