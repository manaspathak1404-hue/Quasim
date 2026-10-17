#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include<charconv>
#include <complex>
#include <cstdint>
#include <vector>
#include <memory>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <string>
using namespace std;
double Gb = 1024.0 * 1024.0 * 1024.0;
string CheckInput(){
	string input;
	if(!getline(cin, input)){
		throw runtime_error("unexpected behaviour");
	}
	return input;
}
int GetValidQubit() {
	int qubit = 0;
	string input;
	cout << " Please tell the number of Qubits you want to process: ";
	input = CheckInput();
	auto result = from_chars(input.data(), input.data() + input.size(), qubit);
	auto maxValue = numeric_limits<unsigned long long>::max() / sizeof(complex<double>);
	bool verif = false;
	
	while (verif == false) {
		if (result.ec != errc{} || result.ptr != input.data() + input.size()) {
			cout << " Please enter a positive valid integer number of qubits ";
			input = CheckInput();
		}
		else if (qubit <= 0) {


			cout << " Please enter positive value for number of qubits ";
			input = CheckInput();


		}
		else if (qubit > 0 && qubit < numeric_limits<unsigned long long>::digits && (1ULL << qubit) <= maxValue && result.ptr == input.data() + input.size()) {
			verif = true;
			break;
		}

		else {
			cout << "Please enter a count of more than 0 and less than 64 within range of int ";
			input = CheckInput();
		}
		result = from_chars(input.data(), input.data() + input.size(), qubit);
	}

	return qubit;
}
int check() {
	int qubit = GetValidQubit();
	double size = ((1ULL << qubit) * sizeof(complex<double>)) / Gb;
	bool verification = false;
	while (verification != true) {
		MEMORYSTATUSEX memory;
		memory.dwLength = sizeof(MEMORYSTATUSEX);
		if (!GlobalMemoryStatusEx(&memory)) {
			cout << "Reading failed, Exiting";
			throw runtime_error("Memory reader failure");

		}
		double storage = memory.ullAvailPhys;
		if (storage / Gb - size >= 1) {
			verification = true;
			cout << "thank you for telling Initializing system" << endl;
		}
		else {
			cout << "Memory limit exceeded ";
			qubit = GetValidQubit();

			size = ((1ULL << qubit) * sizeof(complex<double>)) / Gb;
		}
	}
	cout << "The size is " << ((1ULL << qubit) * sizeof(complex<double>)) << "bytes";
	return qubit;
}

void getsystem() {
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	cout << "NO. of logical cores  " << info.dwNumberOfProcessors << endl;
	MEMORYSTATUSEX memory;
	memory.dwLength = sizeof(MEMORYSTATUSEX);
	if (!GlobalMemoryStatusEx(&memory)) {
		cout << "Reading failed, Exiting";
		throw runtime_error("Memory reader failure");

	}
	double storage = memory.ullAvailPhys;
	cout << "Total Physical R.A.M: " << memory.ullTotalPhys / Gb << endl;
	cout << "Total Available R.A.M: " << memory.ullAvailPhys / Gb << endl;
	cout << " Occupied R.A.M: " << memory.ullTotalPhys / Gb - memory.ullAvailPhys / Gb << endl;

	int qubit = check();


}

int main() {
	try {
		getsystem();
	}
	catch (const  runtime_error& e) {
		cout << e.what();
	}
}
