#ifndef NOT_H
#define NOT_H

#include "logicgate.h"


class NOT : public LogicGate
{
	public:
		NOT(string name, unsigned int nbr_input);
		virtual ~NOT();

		virtual void calculate_output();

	protected:
	private:
};

#endif // NOT_H
