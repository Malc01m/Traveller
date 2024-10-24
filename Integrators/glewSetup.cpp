#include <GL/glew.h>
#include <cstdio>

#include "Shader.h"

class glewSetup {
    public:
        bool startGlew() {
            GLenum glewstatus = glewInit();
            if (glewstatus != GLEW_OK) {
                fprintf(stderr, "Failed to start GLEW, error: %s\n", glewGetErrorString(glewstatus));
                return false;
            }
            return true;
        }

        void setupGL(GLint shaderProgram) {
            color = glGetUniformLocation(shaderProgram, "color");
            pos = glGetAttribLocation(shaderProgram, "position");

            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glEnableVertexAttribArray(pos);
            glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable( GL_BLEND );
        }

        GLint getColor() {
            return color;
        }

    private:
        GLuint vbo = 0;
        GLuint vao = 0;
        GLint color = 0;
        GLint pos = 0;
};