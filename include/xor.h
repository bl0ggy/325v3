#ifndef XOR_H
#define XOR_H

#include "logicgate.h"


class XOR : public LogicGate
{
	public:
		XOR(string name, unsigned int nbr_input);
		virtual ~XOR();

		virtual void calculate_output();

	protected:
	private:
};

#endif // XOR_H
