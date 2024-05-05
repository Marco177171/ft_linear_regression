#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

void ft_fatal(std::string error) {
	std::cerr << "ERROR: " << error << std::endl;
	exit(1);
}

void debug(std::string message) {
	std::cout << message << std::endl;
}

std::vector<std::pair<int, int>> parseCSVLine(const std::string& line) {
	std::vector<std::pair<int, int>> keyValuePairs;
	std::istringstream ss(line);
	std::string csvLine;

	while (std::getline(ss, csvLine)) {
		std::size_t commaPos = csvLine.find(',');
		if (commaPos != std::string::npos) {
			int key = std::stoi(csvLine.substr(0, commaPos));
			int value = std::stoi(csvLine.substr(commaPos + 1));
			keyValuePairs.push_back({key, value});
		}
	}

	return keyValuePairs;
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
	while (std::getline(file, line)) {
		std::vector<std::pair<int, int>> keyValuePairs = parseCSVLine(line);
		// Process key-value pairs
		for (const auto& pair : keyValuePairs) {
			std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
		}
	}

	file.close();

	return 0;
}
