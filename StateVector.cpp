#include "StateVector.h"
void StateVector::PauliX() {
	std::string name = "Qubit";
	long long int Qubitnumber = ValidInput(qubit, name);
	long long int mask = 1ULL << (qubit - Qubitnumber);
#pragma omp parallel for schedule(static)
	for (long long int outer = 0; outer < Amplitude.size(); outer += (mask << 1)) {


		for (long long int inner = 0; inner < mask; inner++) {
			long long int idx0 = outer + inner;
			long long int idx1 = idx0 + mask;


			std::swap(Amplitude[idx0], Amplitude[idx1]);
		}
	}
	std::cout << "Pauli X applied succesfully" << std:: endl;
}

void StateVector::Ask(){
	std::string ask;
	std::cout << "Please enter the process you want to initiate" << std::endl;
	std::getline(std::cin, ask);
	std::transform(ask.begin(), ask.end(), ask.begin(), [](unsigned char c) {return std::tolower(c);});
	ask.erase(std::remove_if(ask.begin(), ask.end(), [](unsigned char c) {
		return std::isspace(c);
		}), ask.end());
	if(ask =="paulix"){
		PauliX();
	}
	else if(ask == "close"){
		std::cout << "Copyright[2026][Manas Pathak]" << std::endl;
		std::exit(0);
	}

}

std::string StateVector::CheckInput() {

	std::string input;
	if (!std::getline(std::cin, input)) {
		throw std::runtime_error("unexpected behaviour");
	}
	return input;
}
StateVector::StateVector(long long  int qubit) :
	qubit(qubit),
	Amplitude(1ULL << qubit, std::complex<double>(0.0, 0.0))

{
	NumberOfAmplitudes = 1ULL << qubit;
	Amplitude[0] = std::complex<double>(1.0, 0.0);
	
}
long long int StateVector::ValidInput( long long int Num, const std:: string& name){
	long long int value= 0;
	std::string input;
	std::cout << " Please tell adress or number of " << name << std::endl;
	input = CheckInput();
	auto result = std::from_chars(input.data(), input.data() + input.size(),value );
	bool verif = false;

	while (verif == false) {
		if (result.ec != std::errc{} || result.ptr != input.data() + input.size()) {
			std::cout << " Please enter a positive valid integer number of " << name << std::endl;
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
		result = std::from_chars(input.data(), input.data() + input.size(), value);
	}

	return value;
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

