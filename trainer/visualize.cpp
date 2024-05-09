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

	// normalize points' coordinates with window's measures
	it = dataVector->begin();
	while (it != dataVector->end()) {
		it->first = it->first / greatest_X * 800;
		it->second = 450 - it->second / greatest_Y * 400; // Invert Y-coordinate
		++it;
	}
	std::cout << "window normalization executed" << std::endl;

	// normalize theta0 with window's height: when X = 0 Y must be...
	theta0 /= greatest_Y * 450;
	// mirror theta1 (slope) on x axis
	theta1 *= -10;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Create a window
	SDL_Window *window = SDL_CreateWindow("Linear Regression Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 450, SDL_WINDOW_SHOWN);
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
		while (++y_index < 450) {
			if (((x_index * -1) % static_cast<int>(greatest_X / 800) == 0) ||
				((y_index * -1) % static_cast<int>(greatest_Y / 450) == 0)) {
				SDL_RenderDrawPoint(renderer, x_index, y_index);
			}
		}
		y_index = -1;
	}

	// Draw regression line
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Purple color for regression line
	for (int x = 0; x < 800; ++x) {
		int y = static_cast<int>(theta0 + theta1 * x);
		SDL_RenderDrawPoint(renderer, x, y); // Invert Y-coordinate
	}
	// Draw data points
	it = dataVector->begin();
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color for data points
	while (++it != dataVector->end()) {
		std::cout << "drawing " << it->first << " | " << it->second << std::endl;
			SDL_RenderDrawPoint(renderer, it->first, it->second);
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