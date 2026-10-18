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
using namespace std;
class Checksystem{
public:
	string CheckInput();
	int GetValidQubit();
	int check();
	void getsystem();
	int ReturnQubit();
private:
	int qubit;
	double Gb = 1024.0 * 1024.0 * 1024.0;

};