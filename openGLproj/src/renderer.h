#pragma once

#include <GL/glew.h>

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();

#ifdef _DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLPoll(x) x
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class renderer
{
public:
    void draw(const vertexArray& va, const indexBuffer& ib, const shader& shader) const;
    void clear() const;
};