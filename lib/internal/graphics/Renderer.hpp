// Renderer.hpp
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void clearScreen();
    void render();
    void present();

private:
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
};

#endif // RENDERER_HPP