#include "Renderer.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Renderer::Renderer(SDL_Window* window) : 
    renderer_(nullptr),
    textures_()
{
    renderer_ = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!renderer_) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return;
    }

    // Initialize SDL_image for PNG loading
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! Error: " << IMG_GetError() << std::endl;
    }

    // Set blend mode for alpha transparency
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    
    // Load all game assets
    loadAssets();
}

Renderer::~Renderer() {
    textures_.clear(); // Destroy all textures first
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }
    IMG_Quit();
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer_, 135, 206, 235, 255); // Sky blue
    SDL_RenderClear(renderer_);
}

void Renderer::present() {
    SDL_RenderPresent(renderer_);
}

void Renderer::render(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* destRect) {
    SDL_RenderCopy(renderer_, texture, srcRect, destRect);
}

void Renderer::render(SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopy(renderer_, texture, nullptr, &destRect);
}

SDL_Texture* Renderer::loadTexture(const std::string& filePath) {
    // Check if file exists first
    if (!fs::exists(filePath)) {
        std::cerr << "Texture file not found: " << filePath << std::endl;
        return nullptr;
    }

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
    
    if (!loadedSurface) {
        std::cerr << "Unable to load image " << filePath << "! Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    
    if (!newTexture) {
        std::cerr << "Unable to create texture from " << filePath << "! Error: " << SDL_GetError() << std::endl;
    }

    return newTexture;
}

SDL_Texture* Renderer::getTexture(const std::string& name) {
    auto it = textures_.find(name);
    if (it != textures_.end()) {
        return it->second.get();
    }
    return nullptr;
}

void Renderer::loadAssets() {
    // Define base assets path (works for both build and development environments)
    fs::path assetsPath;
    
    // First try the path relative to executable (for installed builds)
    if (fs::exists("assets")) {
        assetsPath = "assets";
    } 
    // Then try the path from source directory (for development)
    else if (fs::exists("../assets")) {
        assetsPath = "../assets";
    } else {
        std::cerr << "Could not find assets directory!" << std::endl;
        return;
    }

    // Load background
    fs::path bgPath = assetsPath / "maps" / "background.jpg";
    SDL_Texture* bgTex = loadTexture(bgPath.string());
    if (bgTex) {
        textures_.emplace("background", std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(bgTex, SDL_DestroyTexture));
    }

    // Load bird
    fs::path birdPath = assetsPath / "characters" / "flappy.png";
    SDL_Texture* birdTex = loadTexture(birdPath.string());
    if (birdTex) {
        textures_.emplace("bird", std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(birdTex, SDL_DestroyTexture));
    }

    // Load pipe
    fs::path pipePath = assetsPath / "characters" / "pipe.png";
    SDL_Texture* pipeTex = loadTexture(pipePath.string());
    if (pipeTex) {
        textures_.emplace("pipe", std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(pipeTex, SDL_DestroyTexture));
    }

    // Load cloud
    fs::path cloudPath = assetsPath / "characters" / "cloud.png";
    SDL_Texture* cloudTex = loadTexture(cloudPath.string());
    if (cloudTex) {
        textures_.emplace("cloud", std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(cloudTex, SDL_DestroyTexture));
    }
}

// Game-specific rendering functions
void Renderer::renderBackground() {
    SDL_Texture* bg = getTexture("background");
    if (bg) {
        render(bg, 0, 0, 800, 600); // Assuming 800x600 resolution
    }
}

void Renderer::renderBird(int x, int y, int width, int height) {
    SDL_Texture* bird = getTexture("bird");
    if (bird) {
        render(bird, x, y, width, height);
    }
}

void Renderer::renderPipe(int x, int y, int width, int height, bool top) {
    SDL_Texture* pipe = getTexture("pipe");
    if (pipe) {
        SDL_Rect srcRect = {0, 0, width, height};
        SDL_Rect destRect = {x, y, width, height};
        
        // Flip the pipe if it's a top pipe
        if (top) {
            SDL_RenderCopyEx(renderer_, pipe, &srcRect, &destRect, 0, nullptr, SDL_FLIP_VERTICAL);
        } else {
            SDL_RenderCopy(renderer_, pipe, &srcRect, &destRect);
        }
    }
}

void Renderer::renderCloud(int x, int y, int width, int height) {
    SDL_Texture* cloud = getTexture("cloud");
    if (cloud) {
        render(cloud, x, y, width, height);
    }
}