#include "Window.hpp"
#include <memory>

Window::Window(const std::string& title, int width, int height) :
    window_(nullptr),
    renderer_(nullptr),
    running_(false),
    width_(width),
    height_(height)
{
    window_ = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width_,
                              height_,
                              SDL_WINDOW_SHOWN);
    if (!window_) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }
}

Window::~Window() {
    if (window_) {
        SDL_DestroyWindow(window_);
    }
    SDL_Quit();
}

void Window::run() {
    if (!window_) return;

    running_ = true;
    renderer_ = std::make_unique<Renderer>(window_);

    while (running_) {
        handleEvents();
        update();
        render();
    }
}

void Window::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running_ = false;
        }
    }
}

void Window::update() {
    // Game update logic here
}

void Window::render() {
    if (!renderer_) return;

    renderer_->clear();
    
    // Render game objects here
    renderer_->renderBackground();
    // renderer_->renderBird(...);
    // renderer_->renderPipe(...);
    // renderer_->renderCloud(...);
    
    renderer_->present();
}