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
#include "StateVector.h"
#include "Checksystem.h"


int main() {

	try {
		Checksystem system;
		bool open = true;
		system.getsystem();
		int Qubit = system.ReturnQubit();
		StateVector state(Qubit);
		std::cout << "The number of amplitudes are :-" << (1ULL << Qubit) << std::endl;
		

		state.Normalized();
	


		while(open){
			state.Ask();
		}
		
	}
	catch (const  std::runtime_error& e) {
		std::cout << e.what();
	}
	catch(const std::bad_alloc& e){
		std::cout << e.what() << std::endl;
	}

}
