#include "./lib/Window.hpp"
#include <iostream>

int Window(int argc, char* args[]) {
    SDL_Window* window = NULL; 
    SDL_Surface* screenSurface = NULL;

    if ( SDL_Init( SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL COULDN'T INITIALIZE" <<std::endl;
    } else {
        window = SDL_CreateWindow("Flappy-Bird",SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if (window = NULL) {std::cout << "Window couldn't be created!"<<std::endl;}
        else {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );
            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }
        //destroy the window
        SDL_DestroyWindow( window );

        
        SDL_Quit();
    
        return 0;
}