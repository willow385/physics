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
#include <stdlib.h>
#include <math.h>
#include "geometry.h"
#include "particle.h"

#define PARTICLE_CT 256
#define WINDOW_DIM 400

int main(int argc, char *argv[]) {
    SDL_Renderer *renderer;
    SDL_Window *main_window;

    SDL_Init(SDL_INIT_VIDEO);

    /* Now I'm going to create a window, 600x600 pixels, centred in the screen */
    main_window = SDL_CreateWindow(
        "Claire's physics simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_DIM,
        WINDOW_DIM,
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
    int prev_mouse_x, prev_mouse_y;
    Particle *mouse_particle = create_particle(0, 0, 0, 0);

    Particle **particles = malloc(PARTICLE_CT * sizeof(Particle *));
    int i;
    for (i = 0; i < PARTICLE_CT; i++) {
        particles[i] = create_particle(
            (WINDOW_DIM / 2) + 20 * sin(i),
            (WINDOW_DIM / 2) + 20 * cos(i),
            0,
            0
        );
    }

    /* create a place to store the state of our particles as they were in
       the previous frame */
    Particle **prev_frame_particles = malloc(PARTICLE_CT * sizeof(Particle *));
    for (i = 0; i < PARTICLE_CT; i++) {
        prev_frame_particles[i] = create_particle(0, 0, 0, 0);
    }

    while (window_open) {
        // record the old mouse position
        prev_mouse_x = mouse_x;
        prev_mouse_y = mouse_y;

        // get the new mouse position
        SDL_GetMouseState(
            &mouse_x,
            &mouse_y
        );

        // update the mouse particle
        mouse_particle->x_pos = (float) mouse_x;
        mouse_particle->y_pos = (float) mouse_y;
        mouse_particle->x_momentum = (float) mouse_x - prev_mouse_x;
        mouse_particle->y_momentum = (float) mouse_y - prev_mouse_y;

        // mouse is on our window? then hide the cursor
        if (
            (mouse_x > 0 && mouse_x < WINDOW_DIM)
        &&
            (mouse_y > 0 && mouse_y < WINDOW_DIM)
        ) {
            SDL_ShowCursor(SDL_DISABLE);
        } else {
            SDL_ShowCursor(SDL_ENABLE);
        }

        // first we copy the Particles' old properties
        for (i = 0; i < PARTICLE_CT; i++) {
            copy_particle(prev_frame_particles[i], *particles[i]);
        }
        // then we calculate the collisions
        int j, coinflip = -1;
        for (i = 0; i < PARTICLE_CT; i++) {
            for (j = 0; j < PARTICLE_CT; j++) {
                if (i != j) {
                    if (
                        is_distance(
                            particles[i]->x_pos,
                            particles[i]->y_pos,
                            prev_frame_particles[j]->x_pos,
                            prev_frame_particles[j]->y_pos,
                            1.5
                        )
                    ) {
                        collide(
                            particles[i],
                            *prev_frame_particles[j],
                            coinflip
                        );
                        coinflip *= -1;
                    }
                }
            }

            // collide with the mouse particle, too
            if (
                is_distance(
                    particles[i]->x_pos,
                    particles[i]->y_pos,
                    (float) mouse_x,
                    (float) mouse_y,
                    1.5
                )
            ) {
                collide(
                    particles[i],
                    *mouse_particle,
                    coinflip
                );
                coinflip *= -1;
            }

            // finally we can update them
            update_particle(particles[i], mouse_x, mouse_y);
        }

        // black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);


        // green foreground
        SDL_SetRenderDrawColor(renderer, 0, 255, 50, 255);


        // draw the Particles
        for (i = 0; i < PARTICLE_CT; i++) {
            SDL_RenderDrawPoint(
                renderer,
                particles[i]->x_pos,
                particles[i]->y_pos
            );
        }

        SDL_RenderPresent(renderer);

        // we want the mouse particle to be a different color than everything else
        SDL_SetRenderDrawColor(renderer, 255, 10, 0, 255);
        // and a little bigger
        SDL_RenderDrawPoint(renderer, mouse_x, mouse_y);
        SDL_RenderDrawPoint(renderer, mouse_x-1, mouse_y);
        SDL_RenderDrawPoint(renderer, mouse_x+1, mouse_y);
        SDL_RenderDrawPoint(renderer, mouse_x, mouse_y-1);
        SDL_RenderDrawPoint(renderer, mouse_x, mouse_y+1);

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
                        break;
                }
                break;
        }
    }

    for (i = 0; i < PARTICLE_CT; i++) {
        free_particle(particles[i]);
    }

    free_particle(mouse_particle);
    free(particles);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
