#pragma once
#include "Input.h"
#include <cmath>
#include "StateVector.h"
class StateVector;
namespace Gates {
	void PauliX(StateVector& state);
	void Hadamard(StateVector& state, int64_t index);
	void CNOT(StateVector& state, int64_t control, int64_t target);
	void BellState(StateVector& state,int64_t target, int64_t index);
}
