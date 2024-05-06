#include "trainer.hpp"

void ft_fatal(std::string error) {
	std::cerr << "ERROR: " << error << std::endl;
	exit(1);
}

void debug(std::string message) {
	std::cout << message << std::endl;
}

std::vector<std::pair<int, int>> *parseCSVLine(const std::string& line, std::vector<std::pair<int, int>> *keyValuePairs) {
	std::size_t commaPos = line.find(',');
	if (commaPos != std::string::npos) {
		std::string keyStr = line.substr(0, commaPos);
		std::string valueStr = line.substr(commaPos + 1);
		try {
			int key = std::stoi(line.substr(0, commaPos));
			int value = std::stoi(line.substr(commaPos + 1));
			keyValuePairs->push_back({key, value});
		}
		catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}

	return keyValuePairs;
}

void linearRegression(std::vector<std::pair<int, int>> *dataVector) {
	double mean_X = 0.0; // mileage in this case
	double mean_Y = 0.0; // price

	// double theta_1 = 0.0; // numerator
	// double theta_2 = 0.0; // denominator

	std::vector<std::pair<int, int>>::iterator it;

	debug("in linear");

	it = dataVector->begin();
	while (it++ != dataVector->end()) {
		std::cout << "while: key: " << it->first  << " | value: " << it->second << std::endl;
		mean_X = mean_X + it->first;
		mean_Y = mean_Y + it->second;
	}
	mean_X /= dataVector->size();
	mean_Y /= dataVector->size();

	std::cout << "mean x : " << mean_X << " | mean y : " << mean_Y << std::endl;
	it = dataVector->begin();
	while (it++ != dataVector->end()) {
		
	}
}

int main(int argc, char *argv[]) {

	std::vector<std::pair<int, int>> dataVector;

	if (argc != 2)
		ft_fatal("wrong arguments");

	std::ifstream file(argv[1]);
	if (!file.is_open()) {
		std::cerr << "Error opening file." << std::endl;
		return 1;
	}

	std::string line;
	std::vector<std::pair<int, int>> keyValuePairs;
	while (std::getline(file, line))
		parseCSVLine(line, &keyValuePairs);
	std::vector<std::pair<int, int>>::iterator it = keyValuePairs.begin();
	while (it++ != keyValuePairs.end())
		std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
	file.close();

	linearRegression(&keyValuePairs);

	return 0;
}