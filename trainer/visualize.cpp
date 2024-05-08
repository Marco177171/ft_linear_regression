#include "theta_finder.hpp"

void visualize(std::vector<std::pair<double, double>> *dataVector, double theta0, double theta1) {
	double greatest_X = 0.0;
	double greatest_Y = 0.0;
	std::vector<std::pair<double, double>>::iterator it;


	it = dataVector->begin();
	while (++it != dataVector->end()) {
		if (it->first > greatest_X)
			greatest_X = it->first;
		if (it->second > greatest_Y)
			greatest_Y = it->second;
	}
	std::cout << "greatest X = " << greatest_X << " | greatest Y = " << greatest_Y << std::endl;

	it = dataVector->begin();
	while (++it != dataVector->end()) {
		it->first = it->first / greatest_X * 800;
		it->second = it->second / greatest_Y * 600;
	}
	std::cout << "window normalization executed" << std::endl;

	// normalize theta0 with window's height: when X = 0 Y must be...
	theta0 = theta0 / greatest_Y * 600;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Create a window
	SDL_Window *window = SDL_CreateWindow("Linear Regression Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	// Create a renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	// Clear the renderer
	SDL_SetRenderDrawColor(renderer, 12, 12, 12, 255);
	SDL_RenderClear(renderer);

	// Draw grid
	SDL_SetRenderDrawColor(renderer, 48, 48, 48, 255);
	int x_index = -1, y_index = -1;
	while (++x_index < 800) {
		while (++y_index < 600) {
			if ((x_index % static_cast<int>(greatest_X / 800) == 0) ||
				y_index % static_cast<int>(greatest_Y / 600) == 0)
				SDL_RenderDrawPoint(renderer, x_index, y_index);
		}
		y_index = 0;
	}

	// Draw regression line
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Yellow color for regression line
	for (int x = 0; x < 800; ++x) {
		int y = theta0 + theta1 * x;
		SDL_RenderDrawPoint(renderer, x, y);
	}

	// Draw data points
	it = dataVector->begin();
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color for data points
	while (++it != dataVector->end()) {
		std::cout << "drawing " << it->first << " | " << it->second << std::endl;
		int x = -2;
		while (++x < 3) {
			int y = -2;
			while (++y < 3) {
				SDL_RenderDrawPoint(renderer, static_cast<int>(it->first) + x, static_cast<int>(it->second) + y);
			}
		}
	}

	// Present the renderer
	SDL_RenderPresent(renderer);

	// Wait for user to close the window
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}