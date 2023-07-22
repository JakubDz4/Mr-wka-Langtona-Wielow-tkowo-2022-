module;
#include <SDL.h>
export module Module;
import <iostream>;

export int foo()
{
	const int WIDTH = 800, HEIGHT = 600;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("HI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, NULL);

	if (NULL == window)
	{
		std::cout << "blad" << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			if (SDL_QUIT == event.type)
			{
				break;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}