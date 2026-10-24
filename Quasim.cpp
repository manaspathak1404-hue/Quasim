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
#include "Checksystem.h"
#include "StateVector.h"


int main() {
	Checksystem system;
	try {
		bool open = true;
		system.getsystem();
		int Qubit = system.ReturnQubit();
		StateVector state(Qubit);
		std::cout << "The number of amplitudes are:  " << state.Amplitudes().size() << std::endl;
		state.Normalized();
		while(open){
			state.Ask();
		}
		
	}
	catch (const  std::runtime_error& e) {
		std::cout << e.what();
	}


}
