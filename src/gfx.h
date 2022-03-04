#include <iostream>
#include <SDL2/SDL.h>
#include "vm.h"

const int MS_BETWEEN_FRAMES = 17;
unsigned int unix_time = 0;

class GFXWindow {
	public:
		GFXWindow(std::string filename) {
			SDL_Init(SDL_INIT_EVERYTHING);

			// get name of file from filename
			std::string name = filename.substr(0, filename.find_last_of("."));
			// remove path from name
			name = name.substr(name.find_last_of("/") + 1);

			window = SDL_CreateWindow(("CHIP-8 :: "+name).c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
			surface = SDL_GetWindowSurface(window);
		}

		~GFXWindow() {
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

		bool update(VirtualMachine* vm) {
			if (vm->display_timer > 0) {
				vm->display_timer--;
				return true;
			}

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

			if (unix_time != 0) {
				// get time between frames
				unsigned int time_between_frames = SDL_GetTicks() - unix_time;
				unsigned int time_to_sleep = MS_BETWEEN_FRAMES - time_between_frames;

				if (time_between_frames > MS_BETWEEN_FRAMES) {
					warning("Frame took too long: " + std::to_string(time_between_frames) + std::string("/17 ms"));
				} else {
					SDL_Delay(time_to_sleep);
				}
			}

			unix_time = SDL_GetTicks();

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