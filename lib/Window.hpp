#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include "Renderer.hpp"

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    void run();

private:
    SDL_Window* window_;
    std::unique_ptr<Renderer> renderer_;
    bool running_;
    int width_;
    int height_;

    void handleEvents();
    void update();
    void render();
};