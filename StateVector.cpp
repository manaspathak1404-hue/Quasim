#include "StateVector.h"
void StateVector::PauliX() {
	std::string name = "Qubit";
	long long int Qubitnumber = ValidInput(qubit, name);
	if (Qubitnumber != -1) {
		long long int mask = 1ULL << (Qubitnumber - 1);
		long long int limit = 131072;
		if (NumberOfAmplitudes > limit) {
			
#pragma omp parallel for proc_bind(spread) schedule(static)
			for (long long int outer = 0; outer < Amplitude.size(); outer += (mask << 1)) {
				for (long long int inner = 0; inner < mask; inner++) {
					long long int idx0 = outer ^ inner;
					long long int idx1 = idx0 ^ mask;
					std::swap(Amplitude[idx0], Amplitude[idx1]);
				}
			}
		}
		else {

			for (long long int outer = 0; outer < Amplitude.size(); outer += (mask << 1)) {
				for (long long int inner = 0; inner < mask; inner++) {
					long long int idx0 = outer ^ inner;
					long long int idx1 = idx0 ^ mask;
					std::swap(Amplitude[idx0], Amplitude[idx1]);
				}
			}
		}
		std::cout << "Pauli X applied successfully" << std::endl;
	}
	
	
	else{
		std::cout << "Paused and exited" << std::endl;
	}
	
	
}

void StateVector::Ask(){
	std::string ask;
	std::cout << "Please enter the process you want to initiate" << std::endl;
	std::cout << "The list of commands are:-" << std::endl << "1)Pauli X " << std::endl << "2)Enter Amplitudes" << std::endl << "3)close" << std::endl << "4)Print" << std::endl;
	std::getline(std::cin, ask);
	transfer(ask);
	if(ask =="paulix"){
	

		PauliX();
	
	}
	else if(ask == "close"){
		std::cout << "Copyright[2026][Manas Pathak] " << std::endl <<  "All Rights Reserved." << std::endl;
		std::exit(0);
	}
	else if(ask == "enteramplitudes" || ask == "modifyamplitudes" || ask == "enteramplitude" || ask=="modifyamplitude"){
		Modify();
	}
	else if(ask == "printamplitude"|| ask=="printamplitudes"||ask=="print"){
		
		long long ind = ValidInput(NumberOfAmplitudes, "Amplitude");
		if(ind == -1){
			std::cout << "Exited" << std::endl;
		}
		else {
			std::cout << Amplitude[ind - 1].real() << "+(" << Amplitude[ind - 1].imag() << ")i" << std::endl;
		}
	}
	else{
		std::cout << "Please enter a valid task" << std::endl;
	}

}

std::string StateVector::CheckInput() {

	std::string input;
	if (!std::getline(std::cin, input)) {
		throw std::runtime_error("unexpected behavior");
	}
	return input;
}
StateVector::StateVector(long long int qubit) :
    qubit(qubit),
    Amplitude(1ULL << qubit, std::complex<double>(0.0, 0.0))

{
	NumberOfAmplitudes = 1ULL << qubit;
	Amplitude[0] = std::complex<double>(1.0, 0.0);
	
}
long long int StateVector::ValidInput( long long int Num, const std:: string& name){
	long long int value= 0;
	std::string input;
	std::cout << " Please tell address or number of " << name << std::endl;
	input = CheckInput();
	transfer(input);
	if(input == "exit"){
		return -1;
	}
	else {
		auto result = std::from_chars(input.data(), input.data() + input.size(), value);
		bool verif = false;

		while (verif == false) {
			if (result.ec != std::errc{} || result.ptr != input.data() + input.size()) {
				std::cout << " Please enter a positive valid integer number of " << name << " and type exit to exit the function"<< std::endl;
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
			if(input == "exit"){
				return -1;
			}
			else{
				result = std::from_chars(input.data(), input.data() + input.size(), value);
			}
			
		}

		return value;
	}
	
}

std::pair<bool, std::optional<double>> StateVector::Normalized(){
    const double tolerance = 1e-12;
    double Normalization = 0;
	omp_set_num_threads(6);
#pragma omp parallel for simd reduction(+:Normalization)
	
	for(long long int i =0; i<NumberOfAmplitudes; ++i){
		auto real = Amplitude[i].real();
		auto imag = Amplitude[i].imag();
		Normalization += (real * real) + (imag * imag);
	}
	if(std::abs(Normalization -1.0)<tolerance){
		std::cout << "Your state is normalized" << std::endl;
		return { true,std::nullopt };
		
	}
	else{
		return { false, Normalization };

	}
}
const std::vector<std::complex<double>>& StateVector::Amplitudes() const{
	return Amplitude;
}
void StateVector::Modify(){
	std::cout << "Initiated the process The value of index 1 is 1+0i so you can now change it if interrupting normalization process and is based on 1 based index" << std::endl;
	Iterate();
	auto result = Normalized();
	bool isNorm = result.first;
	std::optional<double> normVal = result.second;
	while (!isNorm) {
		std::cout << "Your state is not normalized " << std::endl;
		std::cout << "The sum of amps of current state is " << normVal.value_or(0.0) << std::endl;
		Iterate();
		result = Normalized();
		isNorm = result.first;
		normVal = result.second;
	}

	std::cout << "Exited modifying and adding amplitudes" << std::endl;
}
std::complex<double> StateVector::GetAmp(){
	std::complex<double> correct;
	bool cor = false;
	while(cor == false){
		correct = getcorrect();
		if(((correct.real()*correct.real()) + (correct.imag()*correct.imag())) >1){
			std::cout << "You have entered a state disrupting normalization please try again" << std::endl;
			
		}
		else if((correct.real() * correct.real()) > 1 && (correct.imag() * correct.imag()) > 1){
			std::cout << "You have entered a state disrupting normalization please try again" << std::endl;
		}
		else{
			cor = true;
			
			
		}
	}
	return correct;
}
std::complex<double> StateVector:: getcorrect(){
	std::string input;

	std::cout << "Please enter the value of amplitude" << std::endl;
		std::getline(std::cin, input);
		
		while (Check(input) != true){
			std::cout << "You have entered a wrong input" << std::endl;
			std::cout << "Please enter the value of amplitude" << std::endl;
			std::getline(std::cin, input);
			Check(input);
		}

		
		auto index = input.find_first_of('i');
		auto index2 = input.find_last_of('i');
		double value = 0;
		double real = 0;
		double img =0;


		if (index == std::string::npos) {
			auto result = std::from_chars(input.data(), input.data() + input.size(), value);
			if (result.ec == std::errc() && result.ptr == input.data() + input.size()) {
				return std::complex<double>(value, 0);
			}
			else {
				std::cout << "Invalid Input" << std::endl;
			}

		}
		else if (index == index2) {
			if ((index != input.length() - 1 && (input[index + 1] == '+')) || (index != input.length() - 1 && (input[index + 1] == '-'))) {
				std::from_chars(input.data(), input.data() + index, img);
				auto sign = input.find_last_of('+')+1;
				if (sign == 0 || sign == std::string::npos) {
					sign = input.find_last_of('-');

				}

				std::from_chars(input.data() + sign, input.data() + input.size(), real);
				return std::complex<double>(real, img);

			}
			else if(input=="i"){
				return std::complex<double>(0, 1);
			}
			else if(input =="+i"||input=="-i"){
				if(input == "+i"){
					return std::complex<double>(0, 1);
				}
				else if (input == "-i") {
					return std::complex<double>(0, -1);
				}
				
			}
			else if (index == input.length() - 1) {
				auto sign = input.find_last_of('+') + 1;
				if(input[index-1] == '+' or input[index - 1] == '-'){
					if (input[index - 1] == '-') {
						img = -1;
					}
					else {
						img = 1;
					}
					std::from_chars(input.data(), input.data() + index - 1, real);
					return std::complex<double>(real, img);
				}
				if (sign == 0 || sign == std::string::npos) {
					sign = input.find_last_of('-');
					if (sign > 0 && sign != std::string::npos && std::isdigit(static_cast<unsigned char>(input[sign - 1]))) {
						std::from_chars(input.data(), input.data() + sign, real);
						std::from_chars(input.data() + sign, input.data() + input.size(), img);
						return std::complex<double>(real, img);

					}
					else if (sign == std::string::npos || sign == 0) {

						std::from_chars(input.data(), input.data() + input.length() - 1, img);
						return std::complex<double>(0, img);
					}
				}
				else if (sign != 0) {
						std::from_chars(input.data(), input.data() + sign - 1, real);
						std::from_chars(input.data() + sign, input.data() + index, img);
						return std::complex<double>(real, img);
					
				}

			
				



			}


		}

		
			std::cout << "Please enter valid input" << std::endl;
			return std::complex<double>(0.0, 0.0);
		
	
}
void StateVector::transfer(std::string& input){
	std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {return std::tolower(c);});
	input.erase(std::remove_if(input.begin(), input.end(), [](unsigned char c) {
		return std::isspace(c);
		}), input.end());
}
bool StateVector::Check(std::string& input){
	transfer(input);

	
	constexpr std::string_view ALLOWED = "0123456789i+-.";

	if (input.empty() || input.find_first_not_of(ALLOWED) != std::string::npos) {
		
		return false;
	}
	else{
		return true;
	}

}
void StateVector::Iterate(){
	std::string name = "amplitude";
	long long int index = ValidInput(NumberOfAmplitudes, name);
	while (index != -1) {
		Amplitude[index-1] = GetAmp();
		index = ValidInput(NumberOfAmplitudes, name);
	}
}
