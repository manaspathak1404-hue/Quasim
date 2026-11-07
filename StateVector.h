#include <iostream>
#include <complex>
#include <vector>
#include <charconv>
#include <bitset>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include<omp.h>
#include <Windows.h>
#include <bit>
#include <chrono>
#include <optional>
class StateVector{
public:

	StateVector(long long int qubit);
	std::pair<bool, std::optional<double>> Normalized();
	const std::vector<std::complex<double>>& Amplitudes() const;
	void PauliX();
	long long int ValidInput(long long int number, const std::string& name);
	std::string CheckInput();
	void Ask();
	void Modify();
	std::complex<double> GetAmp();
	std::complex<double>getcorrect();
	void transfer(std::string& input);
	bool Check(std::string& input);
	void Iterate();
private:
	long long int qubit;
	std::vector<std::complex<double>>Amplitude;
	long long int NumberOfAmplitudes;
};
