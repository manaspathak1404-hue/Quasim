#include <iostream>
#include <complex>
#include <vector>
#include <charconv>
#include <bitset>
#include <cstdlib>
#include <algorithm>
#include <cctype>
class StateVector{
public:

	StateVector(long long int qubit);
	bool Normalized();
	const std::vector<std::complex<double>>& Amplitudes() const;
	void PauliX();
	long long int ValidInput(long long int number, const std::string& name);
	std::string CheckInput();
	void Ask();
private:
	int qubit;
	std::vector<std::complex<double>>Amplitude;
	int NumberOfAmplitudes;
};
