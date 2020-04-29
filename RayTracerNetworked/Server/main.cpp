// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "Renderer.h"

int main(int argc, char ** argv)
{
    std::cout << "Hello World!\n";

	int x = 0;
	int y = 0;
	Renderer render;
	render.InitRenderer(800, 800);
	bool running = true;
	while (running) {
		SDL_Event ievent;
		while (SDL_PollEvent(&ievent) != 0) {
			switch (ievent.type) {
			case::SDL_QUIT:
				running = false;
			}
		}
		if (y >= 799) {
			std::cout << "Completed Image!\n";
			std::cin.get();
			exit(0);
		}
		else {
			render.LockTexture();
			for (int i = x; i <= x + 50; i++) {
				for (int t = y; t <= y + 50; t++) {
					render.SetPixel(i, t, 128, 0, 128);
				}
			}
			render.UnlockTexture();
		}

		if (x < 799) {
			x += 50;
			//Just to make sure we don't go where we shouldn't
			if (x >= 799) {
				x = 0;
				if (y < 799) {
					y += 50;
				}
			}
		}
		else {
			x = 0;
			if (y < 799) {
				y += 50;
			}
		}
		render.Draw();

	}
	render.Clean();

	//std::cin.get();
	return 0;
}

