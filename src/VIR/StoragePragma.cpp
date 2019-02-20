#include <exception>
#include <vector>
using namespace std;

#include "StoragePragma.hpp"
#include "ReferencePragma.hpp"
#include "StorageDistribution.hpp"
#include "StorageType.hpp"
#include "VariableType.hpp"

int VIR::StoragePragma::getPositionIndex(int index_) const {
	for (unsigned i = 0; i < maxIndexes.size(); ++i)
		if (index_ <= maxIndexes[i])
			return i;
	return -1;
}

VIR::VirEnumerations::StorageDistribution VIR::StoragePragma::distribution() const {
	return _distribution;
}

void VIR::StoragePragma::distribution(
		VIR::VirEnumerations::StorageDistribution distribution_) {
	_distribution = distribution_;
}

VIR::VirEnumerations::StorageType VIR::StoragePragma::storageType() const {
	return _storageType;
}

void VIR::StoragePragma::storageType(
		VIR::VirEnumerations::StorageType storageType_) {
	_storageType = storageType_;
}

bool VIR::StoragePragma::isForIndirectAddress() const {
	return _isForIndirectAddress;
}

void VIR::StoragePragma::isForIndirectAddress(bool isForIndirectAddress_) {
	_isForIndirectAddress = isForIndirectAddress_;
}

VIR::VirEnumerations::VariableType VIR::StoragePragma::variableType() const {
	return _variableType;
}

void VIR::StoragePragma::variableType(
		VIR::VirEnumerations::VariableType variableType_) {
	_variableType = variableType_;
}

