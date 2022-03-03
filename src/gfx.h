#include <iostream>
#include <SDL2/SDL.h>
#include "vm.h"

class GFXWindow {
	public:
		GFXWindow() {
			SDL_Init(SDL_INIT_EVERYTHING);

			window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
			surface = SDL_GetWindowSurface(window);
		}

		~GFXWindow() {
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

		bool update(VirtualMachine* vm) {
			SDL_Event event;    // Event variable

			if (vm->draw_flag) {
				SDL_FillRect(surface, NULL, 0x000000);

				for (int y = 0; y < 32; y++) {
					for (int x = 0; x < 64; x ++) {
						if (vm->gfx[y][x]) {
							SDL_Rect rect = {x * 10, y * 10, 10, 10};
							SDL_FillRect(surface, &rect, 0xFFFFFF);
						}
					}
				}

				// SDL_Rect rect = {frame_counter, 0, 100, 100}; // x, y, width, height
				// SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0xFF, 0x00, 0x00));

            	SDL_UpdateWindowSurface(window);
			}

			SDL_PollEvent(&event);  // Catching the poll event.

			frame_counter ++;

			return event.type != SDL_QUIT;
			// }
		}

	private:
		SDL_Window* window;
		SDL_Surface* surface;

		int width = 640;
		int height = 320;

		int frame_counter = 0;
};