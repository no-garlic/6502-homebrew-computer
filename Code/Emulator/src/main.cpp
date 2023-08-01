#include <iostream>
#include <SDL2/SDL.h>

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        std::cout << "Failed to initialize SDL with error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    std::string hello = "hello world";
    std::cout << hello << std::endl;

    SDL_Quit();

    return EXIT_SUCCESS;
}
