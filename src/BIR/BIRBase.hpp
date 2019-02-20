#include <exception>
using namespace std;

#ifndef __BIRBase_h__
#define __BIRBase_h__

#include "util/Common.hpp"
#include "BIRKindType.hpp"

namespace MemorySpace
{
	class MemoryManager;
}

namespace BIR
{
	class BIRBase
	{
		friend class MemorySpace::MemoryManager;

		private: int _id;
		private: BIR::BIREnumerations::BIRKindType _kind;

		public: int id() const;

		public: void id(int id_);

		public: BIR::BIREnumerations::BIRKindType kind() const;
		public: string kindStr() const;

		public: virtual ~BIRBase() = 0;
	};
}

#endif
