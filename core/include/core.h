/*-------------------------------------------------------------------------*/

#ifndef __CORE_H
#define __CORE_H

/*-------------------------------------------------------------------------*/

#include <map>
#include <set>
#include <string>
#include <vector>

#include <TChain.h>

/*-------------------------------------------------------------------------*/

#ifdef __IS_CORE
  #define THiggsD3PD_cxx
#endif

#include "THiggsD3PD.h"
#define TNTuple THiggsD3PD

/*-------------------------------------------------------------------------*/

#ifdef __IS_MC
  #define __isMC true
#else
  #define __isMC false
#endif

/*-------------------------------------------------------------------------*/

#define Map_t		std::map
#define String_t	std::string
#define Vector_t	std::vector

/*-------------------------------------------------------------------------*/

#define SWAP(a, b) \
	{				\
		__typeof__(a) c;	\
					\
		(c) = (a);		\
		(a) = (b);		\
		(b) = (c);		\
	}

/*-------------------------------------------------------------------------*/

#define SAME(a, b)

/*-------------------------------------------------------------------------*/

#define LoadEvent(event, eventNr) \
		if(this->LoadTree(event) < 0)									\
		{												\
			break;											\
		}												\
														\
		this->fChain->GetEntry(event);									\
														\
		if(event % 250 == 0)										\
		{												\
			std::cout << "\033[sEvent " << event << "/" << eventNr << "\033[u" << std::flush;	\
		}

/*-------------------------------------------------------------------------*/

namespace core
{
	extern String_t input;
	extern String_t output;
	extern Bool_t grid;
	extern Bool_t ER;
	extern Bool_t SM;
	extern Bool_t OF;

	/*-----------------------------------------------------------------*/
	/* CONFIG							   */
	/*-----------------------------------------------------------------*/

	typedef Map_t<String_t,  Float_t> TFltParamMap;
	typedef Map_t<String_t, String_t> TStrParamMap;

	/*-----------------------------------------------------------------*/

	extern TFltParamMap fltParamMap;
	extern TStrParamMap strParamMap;

	/*-----------------------------------------------------------------*/

	void configReset(void);

	bool configLoad(String_t fName);

	Float_t configFltLookup(String_t pName);
	String_t configStrLookup(String_t pName);

	/*-----------------------------------------------------------------*/
	/* LOADER							   */
	/*-----------------------------------------------------------------*/

	bool loader(TChain *chain1, TChain *chain2);

	/*-----------------------------------------------------------------*/
	/* CORE								   */
	/*-----------------------------------------------------------------*/

	void execute(TChain *chain);

	/*-----------------------------------------------------------------*/
	/* UTILS							   */
	/*-----------------------------------------------------------------*/

	Double_t binomialError(Double_t x, Double_t y);

	/*-----------------------------------------------------------------*/
}

/*-------------------------------------------------------------------------*/

#endif /* __CORE_H */

/*-------------------------------------------------------------------------*/

