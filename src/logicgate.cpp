#include <iostream>
#include <bitset>

#include "../include/logicgate.h"

using namespace std;

LogicGate::LogicGate(string name, unsigned int nbr_input)
{
	_name = name;
//	if(nbr_entrees > 0){
		_nbr_input = nbr_input;
//	}else{
//		cerr << "Entree nulle ou negative." << endl;
//		cerr << "\033[1;31mEntree nulle ou negative sur la porte \"" << _name << "\"\033[0m\n" << endl;
//		exit(1);
//	}
}

LogicGate::~LogicGate()
{
	//dtor
}

void LogicGate::set_input(unsigned int input){
//	cout << "ss : " << entrees << endl;
	_input = input;
	calculate_output();
}

void LogicGate::set_output(unsigned int output){
	_output = output;
}

void LogicGate::set_name(string name){
	_name = name;
}

string LogicGate::get_name(){
	return _name;
}
unsigned int LogicGate::get_input(){
	return _input;
}

unsigned int LogicGate::get_output(){
	return _output;
}

unsigned int LogicGate::get_nbr_input(){
	return _nbr_input;
}

void LogicGate::print_info(){
	cout << "Gate \"" << _name << "\" :" << endl;
	cout << "\tNbr of input : " << _nbr_input << endl;
	cout << "\tInput : ";
		for(int i = _nbr_input-1; i >= 0; i--){
			cout << bitset<1>(_input >> i);
		}
	cout << endl;
	cout << "\tOutput : ";
		cout << bitset<1>(_output);
	cout << endl;
}
