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

	double mean_x = 0.0;
	double mean_y = 0.0;

	it = dataVector->begin();
	while (it++ != dataVector->end()) {
		mean_x += it->first;
		mean_y += it->second;
	}
	mean_x /= dataVector->size();
	mean_y /= dataVector->size();

	double numerator;
	double denominator;

	it = dataVector->begin();
	while (it++ != dataVector->end()) {
		numerator += (it->first - mean_x) * (it->second - mean_y);
		denominator += (it->first - mean_x) * (it->first - mean_x);
	}
	double theta_1 = numerator / denominator;
	double theta_0 = mean_y - theta_1 * mean_x;

	// Print the learned parameters
	std::cout << "Learned parameters:\n";
	std::cout << "theta_0 (intercept): " << theta_0 << std::endl;
	std::cout << "theta_1 (slope): " << theta_1 << std::endl;

	
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
	std::vector<std::pair<double, double>>::iterator it = keyValuePairs.begin();
	while (it++ != keyValuePairs.end())
		std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
	file.close();

	ft_linear_regression(&keyValuePairs);

	return 0;
}
