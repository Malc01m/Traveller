#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <vector>
#include <GL/glew.h>
#include "Shader.h"

class ShaderProgram {

    public:

        //Constructors

        /**
         * @brief Constructs a shader program object
        */
        ShaderProgram();

        //Member functions

        /**
         * @brief Adds a shader to the shaders vector
        */
        void add(Shader s);

        /**
         * @brief Compiles the shaders in the shaders vector as a shader program
        */
        GLuint compile();

        //Getters

        /**
         * @brief Returns the last compiled shader program
        */
        GLuint getCompiledShaderProgram();

    private:

        //The last compiled shader program
        GLuint compiledShaderProgram;
        //Objects of shaders to be included in the program
        std::vector<Shader> shaders;

};

#endif