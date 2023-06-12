#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace nle
{

    Shader::Shader()
    {
    }

    Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource, bool fromFile)
    {
        load(vertexSource, fragmentSource, fromFile);
    }

    Shader::~Shader()
    {
        clear();
    }

    std::string Shader::loadFromFile(const std::string &path)
    {
        std::ifstream ifs(path);
        std::stringstream iss;
        iss << ifs.rdbuf();
        return iss.str();
    }

    void Shader::attachShaders(GLuint program, const std::string &code, GLenum type)
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

    void Shader::compileShaders(const std::string &vertex, const std::string &fragment)
    {
        m_shaderProgram = glCreateProgram();

        if (!m_shaderProgram)
        {
            std::cerr << "error creating program" << std::endl;
            return;
        }

        GLint result = 0;
        GLchar errLog[1024] = {0};

        attachShaders(m_shaderProgram, vertex, GL_VERTEX_SHADER);
        attachShaders(m_shaderProgram, fragment, GL_FRAGMENT_SHADER);

        glLinkProgram(m_shaderProgram);
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);

        if (!result)
        {
            glGetProgramInfoLog(m_shaderProgram, sizeof(errLog), NULL, errLog);
            std::cerr << "error linking program: '" << errLog << "'" << std::endl;
            return;
        }

        glValidateProgram(m_shaderProgram);
        glGetProgramiv(m_shaderProgram, GL_VALIDATE_STATUS, &result);

        if (!result)
        {
            glGetProgramInfoLog(m_shaderProgram, sizeof(errLog), NULL, errLog);
            std::cerr << "error validating program: '" << errLog << "'" << std::endl;
            return;
        }

        return;
    }

    void Shader::use()
    {
        glUseProgram(m_shaderProgram);
    }
    
    void Shader::load(const std::string &vertexSource, const std::string &fragmentSource, bool fromFile)
    {   
        if (fromFile)
        {
            compileShaders(loadFromFile(vertexSource), loadFromFile(fragmentSource));
        }
        else
        {
            compileShaders(vertexSource, fragmentSource);
        }

        prdbg("finished compiling %d", m_shaderProgram);
    }

    void Shader::clear()
    {
        if(m_vertexShader != 0)
        {
            glDeleteShader(m_vertexShader);
        }
        if(m_fragmentShader != 0)
        {
            glDeleteShader(m_fragmentShader);
        }
    }

    unsigned int Shader::program() const
    {
        return m_shaderProgram;
    }

    unsigned int Shader::uniformLocation(const std::string &uniform) const
    {
        return glGetUniformLocation(m_shaderProgram, uniform.c_str());
    }
} // namespace nle
