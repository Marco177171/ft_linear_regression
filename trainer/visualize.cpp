#include "theta_finder.hpp"

void visualize(std::vector<std::pair<double, double>> *dataVector, double theta0, double theta1) {
	double greatest_X = 0.0;
	double greatest_Y = 0.0;
	std::vector<std::pair<double, double>>::iterator it;

	it = dataVector->begin();
	while (it++ != dataVector->end()) {
		if (it->first > greatest_X)
			greatest_X = it->first;
		if (it->second > greatest_Y)
			greatest_Y = it->second;
	}

	std::cout << "greatest X = " << greatest_X << " | greatest Y = " << greatest_Y << std::endl;

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
	SDL_SetRenderDrawColor(renderer, 24, 24, 24, 255);
	int x_index = 0, y_index = 0;
	while (x_index++ < 800) {
		while (y_index++ < 600) {
			if (x_index % 100 == 0 || y_index % 100 == 0)
				SDL_RenderDrawPoint(renderer, x_index, y_index);
		}
		y_index = 0;
	}

	// Draw data points
	it = dataVector->begin();
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color for data points
	while (it++ != dataVector->end()) {
		SDL_RenderDrawPoint(renderer, static_cast<int>(it->first / 400), static_cast<int>(it->second / 30));
	}

	// Draw regression line
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color for regression line
	for (int x = 0; x < 800; ++x) {
		int y = theta0 + theta1 * x;
		SDL_RenderDrawPoint(renderer, x, y);
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