#ifndef NOR_H
#define NOR_H

#include "logicgate.h"


class NOR : public LogicGate
{
	public:
		NOR(string name, unsigned int nbr_input);
		virtual ~NOR();

		virtual void calculate_output();

	protected:
	private:
};

#endif // NOR_H
