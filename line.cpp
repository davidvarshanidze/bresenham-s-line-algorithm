#include <SDL2/SDL.h>
#include <iostream>

const int width = 800;
const int height = 600;

// function to draw a line using Bresenham's line algorithm
void drawLine(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        SDL_RenderDrawPoint(renderer, x0, y0); // Plot pixel in framebuffer

        if (x0 == x1 && y0 == y1) break; // Stop when reaching the end point
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

int main()
{
    if ((SDL_Init(SDL_INIT_VIDEO)) < 0) {
        std::cerr << "Failed to initialize SDL" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Bresenham's Line Algorithm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        std::cerr << "Failed to create SDL_Window" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    } 

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Failed to create SDL_Renderer" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        drawLine(renderer, 100, 100, 700, 500); // Example line

        SDL_RenderPresent(renderer);
    }

     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);
     SDL_Quit();
     return 0;
}