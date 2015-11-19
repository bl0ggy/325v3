#ifndef NAND_H
#define NAND_H

#include "logicgate.h"


class NAND : public LogicGate
{
	public:
		NAND(string name, unsigned int nbr_input);
		virtual ~NAND();

		virtual void calculate_output();

	protected:
	private:
};

#endif // NAND_H
