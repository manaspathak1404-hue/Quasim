#pragma once
#include <iostream>
#include <complex>
#include <vector>
#include <charconv>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <Windows.h>
#include <optional>
#include "Gates.h"

class StateVector{ 
public:
    StateVector(uint64_t qubit);
    std::pair<bool, std::optional<double>> Normalized();
    std::vector<std::complex<double>>& Amplitudes();
    std::complex<double> GetAmp();
    std::complex<double>getcorrect();
    bool Check(std::string& input);
    void Ask();
    void Modify();
    void Iterate();
  

private:
   
    long long int qubit;
    friend void Gates::PauliX(StateVector& state);
    friend void Gates::Hadamard(StateVector& statint64_t, int64_t index);
    friend void Gates::CNOT(StateVector& state,int64_t control, int64_t target);
    std::vector<std::complex<double>>Amplitude;
    uint64_t NumberOfAmplitudes;
};
