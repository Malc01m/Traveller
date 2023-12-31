#include <stdio.h>

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    shaders = std::vector<Shader>();
};

void ShaderProgram::add(Shader s) {
    ShaderProgram::shaders.push_back(s);
};

GLuint ShaderProgram::compile() {
    compiledShaderProgram = glCreateProgram();
    //For each shader in the shaders vector...
    for (unsigned int i = 0; i < shaders.size(); i++) {
        //Compile...
        shaders.at(i).compile();
        //And attach...
        glAttachShader(compiledShaderProgram, shaders.at(i).getCompiledShader());
    }
    //And finally, link the program.
    glLinkProgram(compiledShaderProgram);
    glUseProgram(compiledShaderProgram);
    return compiledShaderProgram;
};

GLuint ShaderProgram::getCompiledShaderProgram() {
    return compiledShaderProgram;
}