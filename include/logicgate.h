#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <vector>
#include <string>

using namespace std;

class LogicGate
{
	public:
		LogicGate(string name, unsigned int nbr_input);
		virtual ~LogicGate();

		void set_input(unsigned int input);
		virtual void calculate_output() = 0;
		void set_output(unsigned int output);
		void print_info();

		void set_name(string name);

		string get_name();
		unsigned int get_input();
		unsigned int get_output();
		unsigned int get_nbr_input();
		
		vector<string>	input_names;
		string			output_name;

	protected:
	private:
		string			_name;
		unsigned int	_input;
		unsigned int	_output;
		unsigned int	_nbr_input;
};

#endif // LOGICGATE_H
