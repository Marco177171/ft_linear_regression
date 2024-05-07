#include "theta_finder.hpp"

void ft_fatal(std::string error) {
	std::cerr << "ERROR: " << error << std::endl;
	exit(1);
}

void debug(std::string message) {
	std::cout << message << std::endl;
}

std::vector<std::pair<double, double>> *parseCSVLine(const std::string& line, std::vector<std::pair<double, double>> *keyValuePairs) {
	std::size_t commaPos = line.find(',');
	if (commaPos != std::string::npos) {
		std::string keyStr = line.substr(0, commaPos);
		std::string valueStr = line.substr(commaPos + 1);
		try {
			double key = std::stod(line.substr(0, commaPos));
			double value = std::stod(line.substr(commaPos + 1));
			keyValuePairs->push_back({key, value});
		}
		catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}
	return keyValuePairs;
}

void ft_linear_regression(std::vector<std::pair <double, double>> *dataVector) {
	std::vector<std::pair <double, double>>::iterator it;
	std::ofstream outputFile("thetas.csv");

	double mean_x = 0.0; // average x value of data points (price)
	double mean_y = 0.0; // average Y value of data points (mileage)
	double theta_0 = 0.0; // predicted value of x with y = 0
	double theta_1 = 0.0; // slope of the line
	double numerator;
	double denominator;

	// find the average values for X and Y
	it = dataVector->begin();
	while (it++ != dataVector->end()) {
		mean_x += it->first;
		mean_y += it->second;
	}
	mean_x /= dataVector->size();
	mean_y /= dataVector->size();

	std::cout << "AVERAGE VALUES" << std::endl;
	std::cout << "mean X: " << mean_x << std::endl;
	std::cout << "mean y: " << mean_y << std::endl;

	// find theta 1 and 0
	it = dataVector->begin();
	while (it != dataVector->end()) {
		numerator += (it->first - mean_x) * (it->second - mean_y);
		denominator += (it->first - mean_x) * (it->first - mean_x);
		it++;
	}
	theta_1 = numerator / denominator; // slope of the line. Descendent if negative
	theta_0 = mean_y - theta_1 * mean_x; // value of Y where x = 0 (intercept)

	// Print the learned parameters
	std::cout << "LEARNED PARAMETERS:\n";
	std::cout << "theta_0 (intercept): " << theta_0 << std::endl;
	std::cout << "theta_1 (slope): " << theta_1 << std::endl;
	if (outputFile.is_open()) {
		outputFile << "theta,value" << std::endl;
		outputFile << "theta0," << theta_0 << std::endl; // write theta0 to the file
		outputFile << "theta1," << theta_1 << std::endl; // write theta1 to the file
		outputFile.close();
		std::cout << "Data was written to 'theta.csv'" << std::endl;
	}
	else {
		ft_fatal("Could not open theta output file");
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2)
		ft_fatal("wrong arguments");

	std::ifstream file(argv[1]);

	if (!file.is_open()) {
		std::cerr << "Error opening file." << std::endl;
		return 1;
	}

	std::string line;
	std::vector<std::pair<double, double>> keyValuePairs;
	while (std::getline(file, line))
		parseCSVLine(line, &keyValuePairs);
	file.close();
	debug("data vector was populated");

	ft_linear_regression(&keyValuePairs);

	return 0;
}
