#include <iostream>
#include <SDL2/SDL.h>

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        std::cout << "Failed to initialize SDL with error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("6502 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Failed to create the window" << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Event evt;
    bool isRunning = true;

    while (isRunning)
    {
        while (SDL_PollEvent(&evt) != 0)
        {
            switch (evt.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (evt.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
