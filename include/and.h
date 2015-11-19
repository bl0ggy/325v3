#ifndef AND_H
#define AND_H

#include "logicgate.h"


class AND : public LogicGate
{
	public:
		AND(string name, unsigned int nbr_entrees);
		virtual ~AND();

		virtual void calculate_output();

	protected:
	private:
};

#endif // AND_H
