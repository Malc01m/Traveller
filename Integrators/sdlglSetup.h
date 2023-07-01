#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include <memory>

class sdlglSetup {
    public:

        /**
         * @brief Completely starts a fullscreen window, enabling SDL video and starting an OpenGL context
         * 
         * @return true on success
         */
        bool setupFullscreen();

        /**
         * @brief Starts the SDL video module
         * 
         * @return true on success
         */
        bool startVideo();

        /**
         * @brief Starts a fullscreen window (but nothing else needed to use it)
         * 
         * @return true on success
         */
        bool startFullscreenWindow();

        /**
         * @brief Starts an openGL context
         * 
         * @return true on success
         */
        bool startGLContext();

        /**
         * @brief Sets the version of OpenGL to use
         * 
         * @param major the major version number
         * @param minor the minor version number
         */
        void setGLVer(int major, int minor);

        /**
         * @brief Sets the swap interval to the monitor's refresh rate, preventing screen tearing 
         * 
         * @return true on success
         */
        bool setSwapInterval();

        /**
         * @brief Gets he width of the screen
         * 
         * @return width in pixels
         */
        int getScreenWidth();

        /**
         * @brief Gets he height of the screen
         * 
         * @return height in pixels
         */
        int getScreenHeight();

        /**
         * @brief Gets the screen ratio in width / height
         * 
         * @return the screen ratio in width / height
         */
        double getScreenRatio();

        /**
         * @brief Returns the SDL_Window object managed by this setup object
         * 
         * @return SDL_Window* the window
         */
        SDL_Window* getWindow();

        /**
         * @brief Returns the SDL_GLContext object managed by this setup object
         * 
         * @return SDL_GLContext* the opengl context
         */
        std::shared_ptr<SDL_GLContext> getGLContext();

    private:

        int screenWidth = -1;
        int screenHeight = -1;
        double screenRatio = -1;
        SDL_Window* window;
        std::shared_ptr<SDL_GLContext> ctx;

        void findScreenDimensions();
        void findScreenRatio();

};