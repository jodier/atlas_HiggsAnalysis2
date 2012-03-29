/*-------------------------------------------------------------------------*/

#include <fstream>
#include <iostream>

#include "include/core.h"

/*-------------------------------------------------------------------------*/

core::TFltParamMap core::fltParamMap;
core::TStrParamMap core::strParamMap;

/*-------------------------------------------------------------------------*/

void core::configReset(void)
{
	fltParamMap.clear();
	strParamMap.clear();
}

/*-------------------------------------------------------------------------*/

bool core::configLoad(String_t fName)
{
	std::ifstream stream;

	stream.open(fName.c_str());

	if(stream.is_open() == false)
	{
		std::cerr << "Could not open '" << fName << "' !" << std::endl;

		return false;
	}

	/**/

	Float_t VALUE;

	String_t pName;
	String_t value;

	while(stream.eof() == false)
	{
		if((stream >> pName >> value) != NULL)
		{
			if(sscanf(value.c_str(), "%f", &VALUE) != 0)
			{
				fltParamMap[pName] = VALUE;
			}
			else
			{
				strParamMap[pName] = value;
			}
		}
	}

	/**/

	stream.close();

	return true;
}

/*-------------------------------------------------------------------------*/

Float_t core::configFltLookup(String_t pName)
{
	TFltParamMap::iterator it = fltParamMap.find(pName);

	return (it != fltParamMap.end()) ? it->second : -999999.0;
}

/*-------------------------------------------------------------------------*/

String_t core::configStrLookup(String_t pName)
{
	TStrParamMap::iterator it = strParamMap.find(pName);

	return (it != strParamMap.end()) ? it->second : "unknown";
}

/*-------------------------------------------------------------------------*/

