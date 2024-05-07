#include "predictor.hpp"

void ft_fatal(std::string error) {
	std::cerr << "ERROR: " << error << std::endl;
	exit(1);
}

void debug(std::string message) {
	std::cerr << message << std::endl;
}

int main(int argc, char *argv[]) {
	if (argc != 3)
		ft_fatal("usage: ./predictor *csv file* *mileage*");
	
	std::ifstream thetaFile(argv[1]);
	std::string line;
	double theta0, theta1;

	if (thetaFile.is_open()) {
		while (getline(thetaFile, line)) {
			std::size_t commaPos = line.find(',');
			std::string T0String = line.substr(0, commaPos);
			std::string T1String = line.substr(commaPos + 1);
			try {
				theta0 = std::stod(T0String);
				theta1 = std::stod(T1String);
				debug("thetas found in file and set");
				std::cout << "Theta 0: " << theta0 << std::endl;
				std::cout << "Theta 1: " << theta1 << std::endl;
			}
			catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}
	}
	else
		ft_fatal("error opening the file");
	
	return (0);
}