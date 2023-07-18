#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader {
    public: 

        //Constructors

        /**
         * @brief Constructs a shader with source s and type t
        */
        Shader(const char* s, int t);

        //Member functions

        /**
         * @brief Compiles the shader
        */
        void compile();

        //Getters

        /**
         * @returns The last compiled shader
        */
        GLuint getCompiledShader();

        /**
         * @returns the shader's source code
        */
        const char* getSource();

        /**
         * @returns the shader's type
        */
        int getType();

    private:

        //Shader's source code
        const char* source;
        //Shader's type
        int type;
        //Compiled shader
        GLuint compiledShader;

};

#endif