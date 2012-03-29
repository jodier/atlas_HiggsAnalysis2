/*-------------------------------------------------------------------------*/

#include <fstream>
#include <iostream>

#include "include/core.h"

/*-------------------------------------------------------------------------*/

static bool __prunLoader(Vector_t<String_t> &vector)
{
	size_t i;
	size_t n;

	String_t str = core::input;

	for(i = 0; i <= str.length(); i = n + 1)
	{
		n = str.find_first_of(',', i);

		if(n == String_t::npos)
		{
			n = str.length();
		}

		String_t fName = str.substr(i, n - i);

		std::cout << "Loading '" << fName << "'..." << std::endl;

		vector.push_back(fName);
	}

	return true;
}

/*-------------------------------------------------------------------------*/

static bool __localLoader(Vector_t<String_t> &vector)
{
	std::ifstream stream;

	stream.open(core::input.c_str());

	if(stream.is_open() == false)
	{
		std::cerr << "Could not open '" << core::input << "' !" << std::endl;

		return false;
	}

	/**/

	String_t fName;

	while(stream >> fName)
	{
		std::cout << "Loading '" << fName << "'..." << std::endl;

		vector.push_back(fName);
	}

	/**/

	stream.close();

	return true;
}

/*-------------------------------------------------------------------------*/

bool core::loader(TChain *chain1, TChain *chain2)
{
	/*----------------------------------------------------------------*/

	Vector_t<String_t> vector;

	if(((grid != false) ? __prunLoader(vector) : __localLoader(vector)) == false)
	{
		std::cerr << "Could not load '" << core::input << "' !" << std::endl;

		return false;
	}

	/*----------------------------------------------------------------*/

	chain1->SetName("physics");

	for(size_t i = 0; i < vector.size(); i++)
	{
		chain1->AddFile(vector.at(i).c_str());
	}

	/*----------------------------------------------------------------*/

	return true;
}

/*-------------------------------------------------------------------------*/

