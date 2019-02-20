
#ifndef _ConfigManager_H_
#define _ConfigManager_H_

#include <fstream>
#include <map>
#include <string>
#include "HWSetting.hpp"
#include "VManager/VFileNames.hpp"
#include "util/Common.hpp"

using std::string;

class ConfigManager
{
public:
	ConfigManager();

	HWSetting & hwSetting();
	void readConfiguration();

private:
	enum Section { sOthers, sInstruction };
	enum SubSection { ssGeneral, ssRefi1, ssRefi2, ssRefi3, ssDpu, ssDrra, ssDimarch };
	enum SettingsVariable { svDimarchRow, svDimarchCol, svDpuConstantWidth, svDrraCol, svDrraRow, svInitialDelay, svInstructionWidth, 
							svMiddleDelay, svMiddleDelayExt, svNumOfRepetition, svNumOfRepetitionExt, svRaccuMaxLoopNo, 
							svRaccuRegFileDepth, svRegFileDepth, svRepetitionDelay, svRepetitionStepValue, 
							svRepetitionStepValueExt, svSeqRegFileDepth, svSramWidth, svSramDepth, svStartingAddress, svStepValue
						  };

	typedef std::map<string, SettingsVariable> SettingsMap;

	Section _currSection;
	SubSection _currSubSection;
	HWSetting _hwSetting;
	std::ifstream _inFile;
	SettingsMap _settingsMap;

	void changeSection(const string & strLine);
	void fillSettingsMap();
	void updateSetting(const string & strLine);
	void changeSubSection(const string & strLine);
};

#endif // _ConfigManager_H_
