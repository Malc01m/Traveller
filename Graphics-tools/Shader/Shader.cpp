#include <stdio.h>

#include "Shader.h"

Shader::Shader(const char* s, int t) {
    source = s;
    type = t;
};

void Shader::compile() {

    //Compile...
    compiledShader = glCreateShader(type); 
    const char* c = source;
    glShaderSource(compiledShader, 1, &c, NULL);
    glCompileShader(compiledShader);

    //Report errors...
    GLint status;
    glGetShaderiv(compiledShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        fprintf(stderr, "Failed to compile shader of type %i\n", type);
    }

}

GLuint Shader::getCompiledShader() {
    return compiledShader;
}

const char* Shader::getSource() {
    return source;
}

int Shader::getType() {
    return type;
}
