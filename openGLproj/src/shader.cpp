#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "renderer.h"

shader::shader(const std::string& filepath)
	: m_filePath(filepath), m_rendererID(0)
{
    shaderProgramSource source = parseShader(filepath);
    m_rendererID = createShader(source.vertexSource, source.fragmentSource);
}

shader::~shader()
{
    GLCall(glDeleteProgram(m_rendererID));
}

void shader::bind() const
{
    GLCall(glUseProgram(m_rendererID));
}

void shader::unbind() const
{
    GLCall(glUseProgram(0));
}

shaderProgramSource shader::parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class shaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::stringstream ss[2];

    std::string line;
    shaderType type = shaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = shaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = shaderType::FRAGMENT;
        }
        else {
            ss[int(type)] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int shader::compileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int shader::getUniformLocation(const std::string& name)
{
    if (m_uniformLocCache.find(name) != m_uniformLocCache.end())
        return m_uniformLocCache[name];

    GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
    if (location == -1)
        std::cout << "warning: uniform '" << name << "' doesn't exist" << std::endl;

    m_uniformLocCache[name] = location;

    return location;
}

void shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void shader::setUniform1f(const std::string& name, float v0)
{
    GLCall(glUniform1f(getUniformLocation(name), v0));
}

void shader::setUniform1i(const std::string& name, int i0)
{
    GLCall(glUniform1i(getUniformLocation(name), i0));

}

void shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}