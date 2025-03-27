#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include <unordered_map>

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    // Render operations
    void clear();
    void present();
    void render(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* destRect);
    void render(SDL_Texture* texture, int x, int y, int width, int height);

    // Asset management
    SDL_Texture* loadTexture(const std::string& filePath);
    SDL_Texture* getTexture(const std::string& name);
    void loadAssets();

    // Game-specific rendering
    void renderBackground();
    void renderBird(int x, int y, int width, int height);
    void renderPipe(int x, int y, int width, int height, bool top);
    void renderCloud(int x, int y, int width, int height);

    // Utility functions
    SDL_Renderer* getSDLRenderer() const { return renderer_; }

private:
    SDL_Renderer* renderer_;
    std::unordered_map<std::string, std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> textures_;
};