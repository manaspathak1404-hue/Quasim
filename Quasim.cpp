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
using namespace std;

int main() {
	Checksystem system;
	try {
		system.getsystem();
		int Qubit = system.ReturnQubit();
	}
	catch (const  runtime_error& e) {
		cout << e.what();
	}
}
