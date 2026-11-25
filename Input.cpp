#include "Input.h"
void Input::transfer(std::string& input) {
	std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {return std::tolower(c);});
	input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) {
		return std::isspace(c);
		}), input.end());
}
std::string Input::CheckInput() {

	std::string input;
	if (!std::getline(std::cin, input)) {
		throw std::runtime_error("unexpected behavior");
	}
	return input;
}
uint64_t Input::ValidInput(long long int Num, const std::string& name) {
	long long int value = 0;
	std::string input;
	std::cout << " Please tell address or number of " << name << std::endl;
	input = CheckInput();
	transfer(input);
	if (input == "exit") {
		return -1;
	}
	else {
		auto result = std::from_chars(input.data(), input.data() + input.size(), value);
		bool verif = false;

		while (verif == false) {
			if (result.ec != std::errc{} || result.ptr != input.data() + input.size()) {
				std::cout << " Please enter a positive valid integer number of " << name << " and type exit to exit the function" << std::endl;
				input = CheckInput();
			}
			else if (value <= 0) {


				std::cout << " Please enter positive value for number of " << name << std::endl;
				input = CheckInput();


			}
			else if (value <= Num) {
				verif = true;
				break;
			}

			else {
				std::cout << "Please enter a count of more than 0 till " << Num << std::endl;
				input = CheckInput();
			}
			std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {return std::tolower(c);});
			input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) {
				return std::isspace(c);
				}), input.end());
			if (input == "exit") {
				return -1;
			}
			else {
				result = std::from_chars(input.data(), input.data() + input.size(), value);
			}

		}

		return value;
	}
}

