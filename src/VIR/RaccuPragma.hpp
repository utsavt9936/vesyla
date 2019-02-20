#include <exception>
using namespace std;

#ifndef __RaccuPragma_h__
#define __RaccuPragma_h__

#include "../BIR/RACCUMode.hpp"
#include "AssignmentPragma.hpp"
#include "RaccuOptions.hpp"

namespace BIR
{
namespace BIREnumerations
{
// enum RACCUMode;
}
} // namespace BIR
namespace VIR
{
// class AssignmentPragma;
class RaccuPragma;
namespace VirEnumerations
{
// enum RaccuOptions;
}
} // namespace VIR

namespace VIR
{
class RaccuPragma : public VIR::AssignmentPragma
{
public:
	BIR::BIREnumerations::RACCUMode raccuMode;

public:
	VIR::VirEnumerations::RaccuOptions raccuOptions;

public:
	RaccuPragma();
};
} // namespace VIR

#endif
