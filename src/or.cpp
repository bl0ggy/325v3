#include <stdio.h>
#include <iostream>

#include "../include/or.h"

using namespace std;

OR::OR(string name, unsigned int nbr_input):LogicGate(name,nbr_input)
{
	set_input(0);
	calculate_output();
}

OR::~OR(){}

void OR::calculate_output(){
	int temp = 0;
	temp = get_input() & 1;
	for(unsigned int i = 1; i < get_nbr_input() ; i++){
		temp = temp | ((get_input() >> i) & 1);
	}
	set_output(temp);
}
