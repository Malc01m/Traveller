#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include <array>

#include "sdlglSetup.h"

bool sdlglSetup::setupFullscreen() {
    if (!startVideo()) {
        SDL_Quit();
        return false;
    }
    setGLVer(3, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    if (!startFullscreenWindow()) {
        SDL_Quit();
        return false;
    }
    if (!startGLContext()) {
        SDL_Quit();
        return false;
    }
    setSwapInterval();
    return true;
}

bool sdlglSetup::startVideo() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "sdlglSetup: Failed to start SDL video, error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool sdlglSetup::startFullscreenWindow() {
    if (screenHeight < 0 || screenWidth < 0) {
        findScreenDimensions();
    }
    window = SDL_CreateWindow("Program", 0, 0, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        fprintf(stderr, "sdlglSetup: Failed to start the main window, error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool sdlglSetup::startGLContext() {
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == 0) {
        fprintf(stderr, "sdlglSetup: Failed to start the OpenGl context, error: %s\n", SDL_GetError());
        return false;
    }
    ctx = std::make_shared<SDL_GLContext>(context);
    return true;
}

void sdlglSetup::setGLVer(int major, int minor) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
}

bool sdlglSetup::setSwapInterval() {
    if (SDL_GL_SetSwapInterval(-1) != 0) {
        if (SDL_GL_SetSwapInterval(1) != 0) {
            fprintf(stderr, "sdlglSetup: Couldn't set the swap interval, screen tearing may occur.\n");
            SDL_ClearError();
            return false;
        }
    }
    return true;
}

int sdlglSetup::getScreenWidth() {
    if (screenWidth < 0) {
        findScreenDimensions();
    }
    return screenWidth;
}

int sdlglSetup::getScreenHeight() {
    if (screenHeight < 0) {
        findScreenDimensions();
    }
    return screenHeight;
}

double sdlglSetup::getScreenRatio() {
    if (screenRatio < 0) {
        findScreenRatio();
    }
    return screenRatio;
}

SDL_Window* sdlglSetup::getWindow() {
    return window;
}

std::shared_ptr<SDL_GLContext> sdlglSetup::getGLContext() {
    return ctx;
}

void sdlglSetup::findScreenDimensions() {
    SDL_DisplayMode dispmode;
    SDL_GetCurrentDisplayMode(0, &dispmode);
    screenWidth = dispmode.w;
    screenHeight = dispmode.h;
}

void sdlglSetup::findScreenRatio() {
    if (screenWidth < 0 || screenHeight < 0) {
        findScreenDimensions();
    }
    screenRatio = screenWidth / (double)screenHeight;
}