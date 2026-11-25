#include "StateVector.h"
void StateVector::Ask() {
	std::string ask;
	std::cout << "Please enter the process you want to initiate" << std::endl;
	std::cout << "The list of commands are:-" << std::endl << "1)Pauli X " << std::endl << "2)Enter Amplitudes" << std::endl << "3)Hadamard" << std::endl << "4)Print" << std::endl << "5)CNOT" << std::endl << "6)Bell state" << std::endl << "7)Close" << std::endl;
	std::getline(std::cin, ask);
	Input::transfer(ask);
	if (ask == "paulix" || ask == "1" || ask == "01") {
		Gates::PauliX(*this);
	}
	else if (ask == "hadamardgate" || ask == "hadamard" || ask == "3" || ask == "03") {
		std::string name = "qubit";
		int64_t index = Input::ValidInput(qubit, name);
		if (index == -1) {
			std::cout << "Exited sucessfully" << std::endl;
			return;
		}
		Gates::Hadamard(*this, index);
		std::cout << "Hadamard gate applied correctly" << std::endl;
	}
	else if (ask == "close" || ask == "7" || ask == "07") {
		std::cout << "Copyright[2026][Manas Pathak] " << std::endl << "All Rights Reserved." << std::endl;
		std::exit(0);
	}
	else if (ask == "enteramplitudes" || ask == "modifyamplitudes" || ask == "enteramplitude" || ask == "modifyamplitude" || ask == "2" || ask == "02") {
		Modify();
	}
	else if (ask == "printamplitude" || ask == "printamplitudes" || ask == "print" || ask == "4" || ask == "04") {

		long long ind = Input::ValidInput(NumberOfAmplitudes, "Amplitude");
		if (ind == -1) {
			std::cout << "Exited" << std::endl;
		}
		else {
			std::cout << Amplitude[ind - 1].real() << "+(" << Amplitude[ind - 1].imag() << ")i" << std::endl;
		}
	}
	else if (ask == "cnot" || ask == "cnotgate" || ask == "05" || ask == "5") {
		std::string name = "Target qubit";
		int64_t target = 0;
		target = Input::ValidInput(qubit, name);
		if (target == -1) {
			std::cout << "Exited successfully" << std::endl;
			return;
		}
		name = "Control qubit";
		int64_t control = 0;
		if (control == -1) {
			std::cout << "Exited successfully" << std::endl;
			return;
		}
		control = Input::ValidInput(qubit, name);
		while (control == target) {
			std::cout << "invalid input" << std::endl;
			name = "Target qubit";
			target = 0;
			target = Input::ValidInput(qubit, name);
			if (target == -1) {
				std::cout << "Exited successfully" << std::endl;
				return;
			}
			name = "Control qubit";
			control = 0;
			control = Input::ValidInput(qubit, name);
			if (control == -1) {
				std::cout << "Exited successfully" << std::endl;
				return;
			}

			break;

		}
		
		Gates::CNOT(*this, control, target);
		
		std::cout << "CNOT applied succesfully" << std::endl;
	}
	else if (ask == "bellstate" || ask == "bell" || ask == "6" || ask == "06"){
		std::string name = "Target qubit";
		int64_t target = 0;
		target = Input::ValidInput(qubit, name);
		if (target == -1) {
			std::cout << "Exited successfully" << std::endl;
			return;
		}
		name = "Control qubit";
		int64_t control = 0;
		if (control == -1) {
			std::cout << "Exited successfully" << std::endl;
			return;
		}
		control = Input::ValidInput(qubit, name);
		while (control == target) {
			std::cout << "invalid input" << std::endl;
			name = "Target qubit";
			target = 0;
			target = Input::ValidInput(qubit, name);
			if (target == -1) {
				std::cout << "Exited successfully" << std::endl;
				return;
			}
			name = "Control qubit";
			control = 0;
			control = Input::ValidInput(qubit, name);
			if (control == -1) {
				std::cout << "Exited successfully" << std::endl;
				return;
			}

			break;

		}
		auto start = std::chrono::steady_clock::now();
		Gates::BellState(*this, target, control);
		std::cout << "Bell State successfully applied" << std::endl;
		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << "Execution time: " << duration.count() << " microseconds\n";
	}
	else{
		std::cout << "Please enter a valid task" << std::endl;
	}

}
StateVector::StateVector(uint64_t qubit) :
    qubit(qubit),
    Amplitude(1ULL << qubit, std::complex<double>(0.0, 0.0))

{
	NumberOfAmplitudes = 1ULL << qubit;
	Amplitude[0] = std::complex<double>(1.0, 0.0);
	
}
std::pair<bool, std::optional<double>> StateVector::Normalized(){
    const double tolerance = 1e-12;
    double Normalization = 0;
#pragma omp parallel for simd reduction(+:Normalization) proc_bind(spread) 
	for(uint64_t i =0; i<NumberOfAmplitudes; ++i){
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
std::complex<double> StateVector::getcorrect() {
	std::string input;
	bool correct = false;
	while (!correct) {
	std::cout << "Please enter the value of amplitude" << std::endl;
	std::getline(std::cin, input);
	
		while (Check(input) != true) {
			std::cout << "You have entered a wrong input" << std::endl;
			std::cout << "Please enter the value of amplitude" << std::endl;
			std::getline(std::cin, input);
			Check(input);
		}


		auto index = input.find_first_of('i');
		auto index2 = input.find_last_of('i');
		double value = 0;
		double real = 0;
		double img = 0;


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
				auto img_res = std::from_chars(input.data(), input.data() + index, img);
				auto sign = input.find_last_of('+') + 1;
				if (sign == 0 || sign == std::string::npos) {
					sign = input.find_last_of('-');
				}

				auto k = std::from_chars(input.data() + sign, input.data() + input.size(), real);
				if (img_res.ec == std::errc{} && img_res.ptr == input.data() + index && k.ec == std::errc{} && k.ptr == input.data() + input.size()) {	
					return std::complex<double>(real, img);
				}
				else {
					std::cout << "Invalid input" << std::endl;
				}

			}
			else if (input == "i") {
				return std::complex<double>(0, 1);
			}
			else if (input == "+i" || input == "-i") {
				if (input == "+i") {
					return std::complex<double>(0, 1);
				}
				else if (input == "-i") {
					return std::complex<double>(0, -1);
				}

			}
			else if (index == input.length() - 1) {
				auto sign = input.find_last_of('+') + 1;
				if (input[index - 1] == '+' or input[index - 1] == '-') {
					if (input[index - 1] == '-') {
						img = -1;
					}
					else {
						img = 1;
					}

					auto r = std::from_chars(input.data(), input.data() + index - 1, real);
					if (r.ec == std::errc{} && r.ptr == input.data() + index - 1) {
						return std::complex<double>(real, img);
					}
					else {
						std::cout << "Invalid input" << std::endl;
						
					}

				}
				if (sign == 0 || sign == std::string::npos) {
					sign = input.find_last_of('-');
					if (sign > 0 && sign != std::string::npos && std::isdigit(static_cast<unsigned char>(input[sign - 1]))) {
						auto p = std::from_chars(input.data(), input.data() + sign, real);
						auto t = std::from_chars(input.data() + sign, input.data() + index, img);
						if (p.ec == std::errc{} && p.ptr == input.data() + sign && t.ec == std::errc{} && t.ptr == input.data() + index) {
							return std::complex<double>(real, img);
						}
						else {
							std::cout << "Invalid input" << std::endl;
						
						}




					}
					else if (sign == std::string::npos || sign == 0) {

						auto y = std::from_chars(input.data(), input.data() + input.length() - 1, img);
						if (y.ec == std::errc{} && y.ptr == input.data() + input.length() - 1) {
							return std::complex<double>(0, img);
						}
						else {
							std::cout << "Invalid input" << std::endl;
							
						}

					}
				}
				else if (sign != 0) {
					auto q = std::from_chars(input.data(), input.data() + sign - 1, real);
					auto g = std::from_chars(input.data() + sign, input.data() + index, img);
					if (g.ec == std::errc{} && g.ptr == input.data() + index && q.ec == std::errc{} && q.ptr == input.data() + sign - 1) {
						return std::complex<double>(real, img);
					}
					else {
						std::cout << "Invalid input" << std::endl;
						
					}


				}
			}
		}
		std::cout << "Please enter valid input" << std::endl;
	}

}
bool StateVector::Check(std::string& input){
	Input::transfer(input);

	
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
	uint64_t index = Input::ValidInput(NumberOfAmplitudes, name);
	while (index != -1) {
		Amplitude[index-1] = GetAmp();
		index = Input::ValidInput(NumberOfAmplitudes, name);
	}
}
