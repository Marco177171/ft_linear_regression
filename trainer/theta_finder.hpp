#ifndef THETA_FINDER_HPP
# define THETA_FINDER_HPP

# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include <iostream>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>

void visualize(std::vector<std::pair<double, double>> *dataVector, double theta0, double theta1);

#endif