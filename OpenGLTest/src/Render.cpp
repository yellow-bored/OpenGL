#include "Render.h"
#include<iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLErrorLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL ERROR]:(" << error << ") " << function << " " << file << ": " << line << "!!\n";
        return false;
    }
    return true;
}