#include <iostream>
#include <complex>
#include <vector>

class StateVector{
public:

	StateVector(int qubit);
	bool Normalized();
	const std::vector<std::complex<double>>& Amplitudes() const;
private:
	int qubit;
	std::vector<std::complex<double>>Amplitude;
	

};