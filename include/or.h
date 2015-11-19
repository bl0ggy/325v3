#ifndef OR_H
#define OR_H

#include "logicgate.h"


class OR : public LogicGate
{
	public:
		OR(string name, unsigned int nbr_input);
		virtual ~OR();

		virtual void calculate_output();

	protected:
	private:
};

#endif // OR_H
