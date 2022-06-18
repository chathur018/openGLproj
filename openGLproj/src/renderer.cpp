#include "renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[openGL error] (" << error << "):" << function << file << ": " << line << std::endl;
        return false;
    }

    return true;
}

void renderer::draw(const vertexArray& va, const indexBuffer& ib, const shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void renderer::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}