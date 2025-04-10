#pragma once
#include"GL/glew.h"

#define ASSERT(x) if(!(x)) __debugbreak();

#define GLErrorCall(x) GLClearError();\
    x;\
    ASSERT(GLErrorLogCall(#x,__FILE__,__LINE__))

void GLClearError();
bool GLErrorLogCall(const char* function, const char* file, int line);
