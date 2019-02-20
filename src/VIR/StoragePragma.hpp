#include <exception>
#include <vector>
using namespace std;

#ifndef __StoragePragma_h__
#define __StoragePragma_h__

#include "ReferencePragma.hpp"
#include "StorageDistribution.hpp"
#include "StorageType.hpp"
#include "VariableType.hpp"

namespace VIR {
// class ReferencePragma;
class StoragePragma;
namespace VirEnumerations {
// enum StorageDistribution;
// enum StorageType;
// enum VariableType;
}
}

namespace VIR {
class StoragePragma: public VIR::ReferencePragma {
public:
	vector<int> maxIndexes;
public:
	vector<int> startAddresses;
private:
	VIR::VirEnumerations::StorageDistribution _distribution;
private:
	VIR::VirEnumerations::StorageType _storageType;
private:
	bool _isForIndirectAddress;
private:
	VIR::VirEnumerations::VariableType _variableType;

public:
	int getPositionIndex(int index_) const;

public:
	VIR::VirEnumerations::StorageDistribution distribution() const;

public:
	void distribution(VIR::VirEnumerations::StorageDistribution distribution_);

public:
	VIR::VirEnumerations::StorageType storageType() const;

public:
	void storageType(VIR::VirEnumerations::StorageType storageType_);

public:
	bool isForIndirectAddress() const;

public:
	void isForIndirectAddress(bool isForIndirectAddress_);

public:
	VIR::VirEnumerations::VariableType variableType() const;

public:
	void variableType(VIR::VirEnumerations::VariableType variableType_);
};
}

#endif
