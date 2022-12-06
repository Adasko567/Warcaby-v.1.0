#include "window.h"

#include <iostream>
#include <SDL.h>
#include <Windows.h>

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		std::cerr << "SDL failed to initialize\n";
	else {
		Window window("Chinczyk", 10, 10);
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			while (!window.isClosed()) {
				window.draw();
				window.pollEvents();
			}
		}
	}
	return 0;
}
