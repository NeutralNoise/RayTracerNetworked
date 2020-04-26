// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "SDL2/SDL.h"

int main(int argc, char ** argv)
{
    std::cout << "Hello World!\n";

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL2 Error\n";
	}
	else {
		std::cout << "SDL2 OK\n";
	}

	SDL_version sdlVersion;
	SDL_GetVersion(&sdlVersion);
	std::cout << std::to_string(sdlVersion.major) << "." << std::to_string(sdlVersion.minor) << "." << std::to_string(sdlVersion.patch) << "\n";

	std::cin.get();
	return 0;
}

