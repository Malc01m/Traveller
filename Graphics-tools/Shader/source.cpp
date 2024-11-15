namespace shadersrc {

    const char vertsrc[] = R"glsl(

                        #version 150 core

                        in vec2 position;

                        void main() {
                            gl_Position = vec4(position, 0.0, 1.0);
                        }

                        )glsl";

    const char fragsrc[] = R"glsl(

                        #version 150 core

                        uniform vec4 color;
                        out vec4 outColor;

                        void main() {
                            outColor = color;
                        }

                        )glsl";
                        
}