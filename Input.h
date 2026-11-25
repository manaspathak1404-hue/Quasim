#pragma once
#include <iostream>
#include <complex>
#include <vector>
#include <charconv>
#include <bitset>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include<omp.h>
#include <Windows.h>
#include <bit>
#include <chrono>
#include <optional>

namespace Input{
	std::string CheckInput();
	uint64_t ValidInput(long long int number, const std::string& name);
	void transfer(std::string& input);
}