# Quasim
Quasim is a low level quantum simulator designed to mimic the features of a quantum computer. Quasim is equipped a hardware checker that check your hardware and qubit requirement that your system can process by scaling the amplitudes by 2^N and then multiplies it by size of complex<double> object. It compares the required storage with R.A.M available in your system and lefts 1 Gib i.e. 1024^3 bytes. This simulator asks the user about what process they want to initiate and processes it.
This project is enabled with Pauli X[NOT gate] and given function that enables user to change amplitudes without disturbing normalization and integrity of state. In the next update support to scientific notations like e will be introduced in the simulator too.
# How to use this project 
In order to use this project you have to input the number of qubits you want to process and then it checks your system and tell if the desired amount of qubits are possible or not. Once you enter the valid number of qubit, It asks you for what process to initiate. You can enter Enter amplitude, close, print and Pauli X. If you select Pauli X you have to enter the number of qubit you want to initiate Pauli X on. If you select Enter Amplitudes it will ask you for index of amplitude and then you enter the value of amplitudes and this program will not let you exit modifying amplitudes until normalization is not maintained and once you are done with modifying you may type exit to exit the function. If you select print it will ask you for index which will be 1 based and then print the amplitude and in casae you change mind you may type exit.
# Supported devices
OS:- Windows 

Language :- c++

Processor:- Minimum 8thread processor
version:- c++ 17 and above.
# Update
Added multithreading for faster process and function enabling user to change value of amplitudes on their own
# Future Updates
As of now the project will get updated to process gates and soon circuits with multi OS compatibility.
# Version:- 1.02
# Copyright[2026][Manas Pathak]
