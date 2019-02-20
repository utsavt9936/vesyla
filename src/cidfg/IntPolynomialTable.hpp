#ifndef __VESYLA_CIDFG_INT_POLYNOMIAL_TABLE_HPP__
#define __VESYLA_CIDFG_INT_POLYNOMIAL_TABLE_HPP__

#include "util/Common.hpp"
#include <set>

namespace vesyla
{
namespace cidfg
{
class IntPolynomialTable
{
private:
	map<multiset<string>, int> _table;

public:
	IntPolynomialTable();
	IntPolynomialTable(map<multiset<string>, int> t_);
	~IntPolynomialTable();

	void add(IntPolynomialTable ipt_);
	void mul(IntPolynomialTable ipt_);
	void sub(IntPolynomialTable ipt_);
	void div_const(IntPolynomialTable ipt_);
	void div_const(int n_);

	bool is_const_divisable(IntPolynomialTable ipt_);
	bool is_const_divisable(int n_);
	bool is_constant();
	bool is_zero();

	int get_bias();

	const map<multiset<string>, int> get_table();

	string serialize();

private:
	void drop_zero_terms();
};
} // namespace cidfg
} // namespace vesyla

#endif // __VESYLA_CIDFG_INT_POLYNOMIAL_TABLE_HPP__