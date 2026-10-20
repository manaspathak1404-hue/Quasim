#include "Checksystem.h"

std::string Checksystem::CheckInput() {

	std::string input;
	if (!std::getline(std::cin, input)) {
		throw std::runtime_error("unexpected behaviour");
	}
	return input;
}
int Checksystem::GetValidQubit() {

	int qubit = 0;
	std::string input;
	std::cout << " Please tell the number of Qubits you want to process: ";
	input = CheckInput();
	auto result = std::from_chars(input.data(), input.data() + input.size(), qubit);
	auto maxValue = std::numeric_limits<unsigned long long>::max() / sizeof(std::complex<double>);
	bool verif = false;

	while (verif == false) {
		if (result.ec != std::errc{} || result.ptr != input.data() + input.size()) {
			std::cout << " Please enter a positive valid integer number of qubits ";
			input = CheckInput();
		}
		else if (qubit <= 0) {


			std::cout << " Please enter positive value for number of qubits ";
			input = CheckInput();


		}
		else if (qubit > 0 && qubit < std::numeric_limits<unsigned long long>::digits && (1ULL << qubit) <= maxValue && result.ptr == input.data() + input.size()) {
			verif = true;
			break;
		}

		else {
			std::cout << "Please enter a count of more than 0 and less than 64 within range of int ";
			input = CheckInput();
		}
		result = std::from_chars(input.data(), input.data() + input.size(), qubit);
	}

	return qubit;
}
int Checksystem::check() {

	int qubit = GetValidQubit();
	double size = ((1ULL << qubit) * sizeof(std::complex<double>)) / Gb;

	bool verification = false;
	while (verification != true) {
		MEMORYSTATUSEX memory;
		memory.dwLength = sizeof(MEMORYSTATUSEX);
		if (!GlobalMemoryStatusEx(&memory)) {
			std::cout << "Reading failed, Exiting";
			throw std::runtime_error("Memory reader failure");

		}
		double storage = memory.ullAvailPhys;
		if (storage / Gb - size >= 1) {
			verification = true;
			std::cout << "thank you for telling Initializing system" << std::endl;
		}
		else {
			std::cout << "Memory limit exceeded ";
			qubit = GetValidQubit();

			size = ((1ULL << qubit) * sizeof(std::complex<double>)) / Gb;
		}
	}
	std::cout << "The size is " << ((1ULL << qubit) * sizeof(std::complex<double>)) << "bytes";
	return qubit;
}

void Checksystem::getsystem() {
	std::cout << "Welcome to Quasim version 1.00" << std::endl;
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	DWORD buffersize = 0;
	GetLogicalProcessorInformationEx(RelationCache, nullptr, &buffersize);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
		throw std::runtime_error("Failed to query CPU cache information");
	}
	std::cout << "NO. of logical cores  " << info.dwNumberOfProcessors << std::endl;
	MEMORYSTATUSEX memory;
	memory.dwLength = sizeof(MEMORYSTATUSEX);
	if (!GlobalMemoryStatusEx(&memory)) {
		std::cout << "Reading failed, Exiting";
		throw std::runtime_error("Memory reader failure");
	}
	double storage = memory.ullAvailPhys;
	std::cout << "Total Physical R.A.M: " << memory.ullTotalPhys / Gb << std::endl;
	std::cout << "Total Available R.A.M: " << memory.ullAvailPhys / Gb << std::endl;
	std::cout << " Occupied R.A.M: " << memory.ullTotalPhys / Gb - memory.ullAvailPhys / Gb << std::endl;

	int qubit = check();
	this->qubit = qubit;


}
int Checksystem::ReturnQubit() {
	return qubit;

}
