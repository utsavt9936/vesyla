#ifndef __VESYLA_VIR_ADDRESS_HPP__
#define __VESYLA_VIR_ADDRESS_HPP__

#include "AddressFunction.hpp"

//namespace vesyla{
namespace VIR
{
class Address
{
public:
	AddressFunction b;
	AddressFunction a0;
	AddressFunction n0;
	AddressFunction a1;
	AddressFunction n1;

public:
	Address()
	{
		b.b(0);
		a0.b(0);
		n0.b(1);
		a1.b(0);
		n1.b(1);
	}
	~Address() {}
};
} // namespace VIR
//}

#endif // __VESYLA_VIR_ADDRESS_HPP__