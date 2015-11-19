#include <bitset>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <time.h>
#include <vector>

#include "../include/logicgate.h"
#include "../include/and.h"
#include "../include/nand.h"
#include "../include/not.h"
#include "../include/or.h"
#include "../include/nor.h"
#include "../include/xor.h"

#define INPUT_PREFIX	"I_"
#define OUTPUT_PREFIX	"O_"
#define LINK_PREFIX		"L"
#define GATE_PREFIX		"gate_"

using namespace std;

int nbr_inputs = 0, nbr_outputs = 0, nbr_logicgates = 0;

int main(int argc, char* argv[]){
	system("clear");
	cout << "Starting program." << endl << endl;
	
	vector<LogicGate*> gates;

	/***** Gates tests *****/
	if(0){
		cout << "Beginning tests." << endl << endl;

		// We create each kind of gate
		vector<LogicGate*> _gates_tests;
		_gates_tests.push_back(new AND("AND",3));
		_gates_tests.push_back(new NAND("NAND",3));
		_gates_tests.push_back(new NOT("NOT",1));
		_gates_tests.push_back(new OR("OR",3));
		_gates_tests.push_back(new NOR("NOR",3));
		_gates_tests.push_back(new XOR("XOR",3));

		cout << "Input\t=>\tOutput" << endl << "----------------------" << endl << endl;

		// For each gate we test 2^(nbr_input) possibilities
		for(unsigned int i = 0; i < _gates_tests.size(); i++){
			unsigned int i2 = pow(2,_gates_tests[i]->get_nbr_input());	// pow(2,3) = 2^3
			cout << "Test on \"" << _gates_tests[i]->get_name() << "\" :" << endl;
			for(unsigned int j = 0; j < i2; j++){	// 000,001,010,011 etc....
				_gates_tests[i]->set_input(j);
				cout << "";
				for(int k = _gates_tests[i]->get_nbr_input()-1; k >= 0; k--){
					cout << bitset<1>(_gates_tests[i]->get_input() >> k);
				}
				cout << "\t=>\t" << bitset<1>(_gates_tests[i]->get_output()) << endl;
			}
			cout << endl;
		}
		_gates_tests[0]->print_info();
	}

	/***** Reading of the map in "map.txt" *****/
		vector<string> lines;	//	Get every line of the file
		string temp = "";		//	Temporary string containing current line
		ifstream file;			//	File containing the map
		file.open("map.txt");
		vector<string> all_gate_lines, inputs, outputs;
		if(file.is_open()){
			file >> temp;	// Remove the "INPUT" word
			file >> temp;
			while(temp != ";"){
				stringstream tmp;
				tmp << INPUT_PREFIX;
				tmp << inputs.size()+1;
				inputs.push_back(tmp.str());
				nbr_inputs++;
				//cout << temp << endl;
				file >> temp;
			}
			//inputs.at(0) = 500;
			file >> temp;	// Remove the "OUTPUT" word
			file >> temp;
			while(temp != ";"){
				stringstream tmp;
				tmp << OUTPUT_PREFIX;
				tmp << outputs.size()+1;
				outputs.push_back(tmp.str());
				nbr_outputs++;
				//cout << temp << endl;
				file >> temp;
			}
			getline(file,temp); // Necessary cause of the end of line after the ";" of the second line
			while(getline(file,temp)){
				nbr_logicgates++;
				all_gate_lines.push_back(temp);
				//cout << temp << endl;
			}
			
			/***** Print informations *****/
				/*for(int i = 0; i < all_gate_lines.size(); i++){
					cout << all_gate_lines[i] << endl;
				}
				for(int i = 0; i < inputs.size(); i++){
					cout << inputs[i] << endl;
				}
				for(int i = 0; i < outputs.size(); i++){
					cout << outputs[i] << endl;
				}*/

				cout << "nbr_inputs :     " << nbr_inputs << endl;
				cout << "nbr_outputs :    " << nbr_outputs << endl;
				cout << "nbr_logicgates : " << nbr_logicgates << endl;
			
			
			//for(int i = 0; i < nbr_inputs)
			/*while(getline(file,temp)){
//					cout << temp << endl;
					if(	temp[temp.length()-1] == 10	||	// If the last character is a "line feed" or "carriage return"
						temp[temp.length()-1] == 13){
						temp[temp.length()-1] = 0;		// Replaced by '\0'
					}
//					cout << "length : " << temp.length() << endl;
					for(unsigned int i = 0; i < temp.length()-1 ; i++){
						if(temp[i] != ' '){		// If there is something else than spaces, we include it in the vector
							lines.push_back(temp);
							break;
						}
					}
				if(file.eof()){		// If we have reached the end of file, we stop getting new lineu

					break;
				}
			}
			if(lines.size() < 3){
				cout << "The map file doesn't contain enough information." << endl;
				cout << "At least 3 lines :" << endl;
				cout << "    1. All inputs" << endl;
				cout << "    2. All outputs" << endl;
				cout << "    3+. list of gates" << endl;
				exit(1);
			}else{
				for(unsigned int i = 0; i < lines.size() ; i++){
					cout << "\"" << lines[i] << "\"" << endl;
				}
			}*/
		}else{
			cout << "Impossible to open the map file." << endl;
			exit(1);
		}
		file.close();

	/***** Creation of the logic gates *****/
		string tmp;
		vector<string>			type, // List of Type, Name and Outputs of the i-th gate
								name,
								output;
		vector<vector<string> >	lists_inputs;
		vector<string>			list_links_name, list_outputs_name, list_inputs_name;
		vector<int>				list_links_gate, list_outputs_gate;
		vector<vector<int> >	list_inputs_gate;
		for(int i = 0; i < all_gate_lines.size(); i++){
			stringstream line;
			line << all_gate_lines[i];
			vector<string> tmp_inputs;
			int j = 0;
			while(line >> tmp){
				if(tmp != ";"){
					if(j == 0){			// Type of the gate
						type.push_back(tmp);
					}else if(j == 1){	// Name of the gate
						name.push_back(tmp);
					}else if(j == 2){	// Output of the gate
						output.push_back(tmp);
						if(tmp.find(LINK_PREFIX) != -1){
							list_links_name.push_back(tmp);
							list_links_gate.push_back(i);
						}else{
							list_outputs_name.push_back(tmp);
							list_outputs_gate.push_back(i);
						}
					}else{				// Inputs of the gate
						tmp_inputs.push_back(tmp);
						if(tmp.find(INPUT_PREFIX) != -1){
							vector<int> x;
							if(list_inputs_name.size() == 0){
								list_inputs_name.push_back(tmp);
								list_inputs_gate.push_back(new vector<int>(0));
								list_inputs_gate[0].push_back(i);
							}else{
								bool exists = false;
								for(int k = 0; k < list_inputs_name.size(); k++){
									if(list_inputs_name[k] == tmp){
										list_inputs_gate[k].push_back(i);
										exists = true;
									}
								}
								if(!exists){
									//cout << list_inputs_name.size() << " " << list_inputs_gate.size() << endl;
									list_inputs_name.push_back(tmp);
									list_inputs_gate.push_back(new vector<int>(0));
									list_inputs_gate[list_inputs_name.size()-1].push_back(i);
								}
							}
						}
					}
					//cout << j << endl;
					//cout << "j : " << j << " : " << tmp << endl;
					j++;
				}
			}
			lists_inputs.push_back(tmp_inputs);
			if(type[i] == "and"){
				gates.push_back(new AND(type[i],tmp_inputs.size()));
				//gates.push_back(new AND("and",3));
				gates[i]->output_name = output[i];
				gates[i]->input_names = lists_inputs[i];
			}else if(type[i] == "nand"){
				gates.push_back(new NAND(type[i],tmp_inputs.size()));
				gates[i]->output_name = output[i];
				gates[i]->input_names = lists_inputs[i];
			}else if(type[i] == "or"){
				gates.push_back(new OR(type[i],tmp_inputs.size()));
				gates[i]->output_name = output[i];
				gates[i]->input_names = lists_inputs[i];
			}else if(type[i] == "nor"){
				gates.push_back(new NOR(type[i],tmp_inputs.size()));
				gates[i]->output_name = output[i];
				gates[i]->input_names = lists_inputs[i];
			}else if(type[i] == "xor"){
				gates.push_back(new XOR(type[i],tmp_inputs.size()));
				gates[i]->output_name = output[i];
				gates[i]->input_names = lists_inputs[i];
			}else if(type[i] == "not"){
				gates.push_back(new NOT(type[i],tmp_inputs.size()));
				gates[i]->output_name = output[i];
				gates[i]->input_names = lists_inputs[i];
			}
			//gates[i]->print_info();
			//cout << endl;
		}
		cout << endl;
		for(int i = 0; i < list_inputs_name.size(); i++){
			cout << list_inputs_name[i] << " : ";
			for(int j = 0; j < list_inputs_gate.size(); j++){
				cout << list_inputs_gate[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		for(int i = 0; i < list_links_name.size(); i++){
			cout << list_links_name[i] << " : " << list_links_gate[i] << endl;
		}
		cout << endl;
		for(int i = 0; i < list_outputs_name.size(); i++){
			cout << list_outputs_name[i] << " : " << list_outputs_gate[i] << endl;
		}
		
	/***** Cration of the adjacence matrix *****/
	
	
	/***** Reading of the input file *****/

	/***** Calculation of output *****/

	/***** Writing the output in "output.txt" *****/


	cout << endl << "End of the program." << endl;
	//system("clear");
}
