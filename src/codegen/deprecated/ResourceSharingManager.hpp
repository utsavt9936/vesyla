#ifndef __VESYLA_CODE_GEN_RESOURCE_SHARING_MANAGER_HPP__
#define __VESYLA_CODE_GEN_RESOURCE_SHARING_MANAGER_HPP__

#include "VIR/VIRIncludeAll.hpp"
#include "BIR/BIRIncludeAll.hpp"

namespace vesyla{
namespace codegen{

class ResourceSharingManager{
private:
	map<string, RefiInstruction*> *_currResourceSharingVariableMap;
	bool _isResourceSharingRegion;
	vector<ResourceSharingVariableMap> _resourceSharingVariableMaps;
	
public:
	ResourceSharingManager() : _isResourceSharingRegion(false){ }
	void enableResourceSharingRegion(VIR::PragmaStatement * pragmaStatement_, bool isMapCreation_ = false, bool goToNextMap_ = false);
	bool & isResourceSharingRegion(){return _isResourceSharingRegion;}
	vector<ResourceSharingVariableMap>& resourceSharingVariableMaps(){return _resourceSharingVariableMaps;}
	map<string, RefiInstruction*> *currResourceSharingVariableMap(){return _currResourceSharingVariableMap;}

};

}
}

#endif // __VESYLA_CODE_GEN_RESOURCE_SHARING_MANAGER_HPP__
