#include "StateVector.h"



StateVector::StateVector(int qubit) :
	qubit(qubit),
	Amplitude(1ULL << qubit, std::complex<double>(0.0, 0.0))
{
	Amplitude[0] = std::complex<double>(1.0, 0.0);
}
bool StateVector::Normalized(){
	const double tolerance = 1e-12;
	double Normalization = 0;
	for(std::complex<double>x : Amplitude){
		Normalization += std::norm(x);
	}
	if(std::abs(Normalization -1.0)<tolerance){
		std::cout << "Your state is normalized" << std::endl;
		return true;
		
	}
	else{
		return false;
	}
}
const std::vector<std::complex<double>>& StateVector::Amplitudes() const{
	return Amplitude;
}

