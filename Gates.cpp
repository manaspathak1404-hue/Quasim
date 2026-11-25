#include  "StateVector.h"
#include "Gates.h"
void Gates::Hadamard(StateVector& state,int64_t index) {
		auto mask = 1ULL << (index - 1);
		auto result = 0.707106781186547524400844362104849039284835937688474036588339;
		
#pragma omp parallel for  schedule(static) proc_bind(spread) 
		for (uint64_t i = 0; i < state.NumberOfAmplitudes; i +=(mask << 1)) {
#pragma omp simd
			for (uint64_t k = 0; k < mask; k++) {
				uint64_t main = i + k;
				uint64_t partner = main ^ mask;
				std::complex<double> plus = (state.Amplitude[main] + state.Amplitude[partner])*result;
				std::complex<double> minus = (state.Amplitude[main] - state.Amplitude[partner])*result;
				state.Amplitude[main] = plus;
				state.Amplitude[partner] = minus;

			}
		}
}

void Gates::PauliX(StateVector& state) {
    
	std::string name = "Qubit";
	uint64_t Qubitnumber = Input::ValidInput(state.qubit, name);
	if (Qubitnumber != -1) {
		uint64_t mask = 1ULL << (Qubitnumber - 1);
		uint64_t limit = 131072;
		if (state.NumberOfAmplitudes > limit) {

#pragma omp parallel for proc_bind(spread) schedule(static) collapse(2)
			for (uint64_t outer = 0; outer < state.Amplitude.size(); outer += (mask << 1)) {
				for (uint64_t inner = 0; inner < mask; inner++) {
					uint64_t idx0 = outer ^ inner;
					uint64_t idx1 = idx0 ^ mask;
					std::swap(state.Amplitude[idx0], state.Amplitude[idx1]);
				}
			}
		}
		else {

			for (uint64_t outer = 0; outer < state.Amplitude.size(); outer += (mask << 1)) {
				for (uint64_t inner = 0; inner < mask; inner++) {
					uint64_t idx0 = outer ^ inner;
					uint64_t idx1 = idx0 ^ mask;
					std::swap(state.Amplitude[idx0], state.Amplitude[idx1]);
				}
			}
		}
		std::cout << "Pauli X applied successfully" << std::endl;
	}


	else {
		std::cout << "Paused and exited" << std::endl;
	}


}
void Gates::CNOT(StateVector& state,int64_t control, int64_t target) {
		uint64_t mask = 1ULL << (target - 1);
		uint64_t mask2 = 1ULL << (control - 1);
		
		if (control > target) {

#pragma omp parallel for proc_bind(spread) schedule(static) 
			for (uint64_t i = mask2; i < state.NumberOfAmplitudes; i += mask2 << 1) {
#pragma omp simd
				for (uint64_t k = 0; k < mask2; k += mask << 1) {
					for (uint64_t j = 0; j < mask; j++) {
						uint64_t index = j + k + i;
						uint64_t partner = index ^ mask;
						std::swap(state.Amplitude[index], state.Amplitude[partner]);
					}
				}
			}
		}
		else if (target > control) {
#pragma omp parallel for proc_bind(spread) schedule(static)
			for (uint64_t i = mask2; i < state.NumberOfAmplitudes; i += mask << 1) {
#pragma omp simd
				for (uint64_t k = 0; k < mask; k += mask2 << 1) {
					for (uint64_t j = 0; j < mask2; j++) {
						uint64_t index = i + k + j;
						uint64_t partner = index ^ mask;
						std::swap(state.Amplitude[index], state.Amplitude[partner]);
					}
				}
			}

		}
		
	}
void Gates::BellState(StateVector& state, int64_t target, int64_t index){
	Gates::Hadamard(state, index);
	Gates::CNOT(state, index, target);
}
