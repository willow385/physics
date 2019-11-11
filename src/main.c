/*          main.c file of physics
    Copyright (C) 2019  Dante Falzone

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include "geometry.h"
#include "particle.h"

#define PARTICLE_CT 16

int main(int argc, char *argv[]) {
    SDL_Renderer *renderer;
    SDL_Window *main_window;

    SDL_Init(SDL_INIT_VIDEO);

    /* Now I'm going to create a window, 600x600 pixels, centred in the screen */
    main_window = SDL_CreateWindow(
        "Claire's physics simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        0
    );

    /* and a renderer so we can draw things on that window */
    renderer = SDL_CreateRenderer(
        main_window,
        0,
        0
    );

    /* Make sure that the user is properly bewildered if something goes wrong */
    if (main_window == NULL || renderer == NULL) {
        printf("Error! Something went horribly wrong!\n");
        printf("Error: %s\n", SDL_GetError());
        return 1;
    }


    int window_open = 1;
    SDL_Event event;

    int mouse_x, mouse_y;

    Particle *particle = create_particle(100, 100, 1.0, 0.1);

    while (window_open) {
        // find the mouse position
        SDL_GetMouseState(&mouse_x, &mouse_y);

        // mouse is on our window? then hide the cursor
        if (
            (mouse_x > 0 && mouse_x < 600)
        &&
            (mouse_y > 0 && mouse_y < 600)
        ) {
            SDL_ShowCursor(SDL_DISABLE);
        } else {
            SDL_ShowCursor(SDL_ENABLE);
        }

        // update our lonesome Particle
        update_particle(particle);

        // black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // green foreground
        SDL_SetRenderDrawColor(renderer, 0, 255, 50, 255);

        // check to see which points are the right distance from the mouse
        int x, y;
        for (x = mouse_x - 20; x < mouse_x + 20; x++) {
            for (y = mouse_y - 20; y < mouse_y + 20; y++) {
                if (is_distance(mouse_x, mouse_y, x, y, 16.0)) {
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }

        // draw the Particle
        SDL_RenderDrawPoint(renderer, particle->x_pos, particle->y_pos);

        SDL_RenderPresent(renderer);

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                window_open = 0;
                break;
            case SDL_KEYUP:
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        printf("You pressed 'A'!\n");
                        printf("Mouse was at (%d, %d)\n", mouse_x, mouse_y);
                        break;
                }
                break;
        }
    }

    free_particle(particle);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
