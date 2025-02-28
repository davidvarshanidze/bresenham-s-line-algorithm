#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

void drawLine(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        SDL_RenderDrawPoint(renderer, x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

void drawTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2) {
    // Draw three lines to form a triangle
    drawLine(renderer, x0, y0, x1, y1);
    drawLine(renderer, x1, y1, x2, y2);
    drawLine(renderer, x2, y2, x0, y0);
}

void drawFace(SDL_Renderer* renderer, int centerX, int centerY, int size) {
    // Draw face as a large triangle (a rough approximation of a round face)
    drawTriangle(renderer,
                 centerX - size, centerY + size, // Bottom left corner
                 centerX + size, centerY + size, // Bottom right corner
                 centerX, centerY - size);       // Top center
}

void drawEyes(SDL_Renderer* renderer, int centerX, int centerY, int eyeSize) {
    // Left eye (triangle)
    drawTriangle(renderer,
                 centerX - 30, centerY - 30, // Left bottom corner
                 centerX - 10, centerY - 30, // Left top corner
                 centerX - 20, centerY - 50); // Left center

    // Right eye (triangle)
    drawTriangle(renderer,
                 centerX + 30, centerY - 30, // Right bottom corner
                 centerX + 10, centerY - 30, // Right top corner
                 centerX + 20, centerY - 50); // Right center
}

void drawMouth(SDL_Renderer* renderer, int centerX, int centerY) {
    // Draw mouth as a triangle (a smile)
    drawTriangle(renderer,
                 centerX - 40, centerY + 50, // Bottom left
                 centerX + 40, centerY + 50, // Bottom right
                 centerX, centerY + 80);     // Bottom center (point)
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Bresenham's Face with Triangles",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        drawFace(renderer, 400, 300, 100);
        drawEyes(renderer, 400, 300, 30);
        drawMouth(renderer, 400, 300);

        SDL_RenderPresent(renderer);
    }

     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);
     SDL_Quit();
     return 0;
}