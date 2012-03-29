/*-------------------------------------------------------------------------*/

#include <cmath>
#include <fstream>
#include <iostream>

#include <TH1.h>

/*-------------------------------------------------------------------------*/

#define ZStudy_cxx
#include "ZStudy.h"

static bool bkgd = false;
static bool isMC = false;

TFile *file;

/*-------------------------------------------------------------------------*/

#define ET_MIN		10.0f	/* GeV */
#define ET_MAX		5000.0f	/* GeV */

/*-------------------------------------------------------------------------*/

bool localLoader(TChain *chain, const char *fname)
{
	std::ifstream stream;

	stream.open(fname);

	if(stream.is_open() == false)
	{
		std::cerr << "Could not open '" << fname << "' !" << std::endl;

		return false;
	}

	/**/

	std::string fName;

	while(stream >> fName)
	{
//		std::cout << "Loading '" << fName << "'..." << std::endl;

		chain->AddFile(fName.c_str());
	}

	/**/

	stream.close();

	return true;
}

/*-------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cerr << argv[0] << " mc.txt data.txt" << std::endl;

		return 1;
	}

	TChain *chain1 = new TChain("Z1");
	TChain *chain2 = new TChain("Z1");

	if(localLoader(chain1, argv[1]) == false
	   ||
	   localLoader(chain2, argv[2]) == false
	 ) {
		delete chain1;
		delete chain2;

		return 1;
	}

	ZStudy alg1(chain1);
	ZStudy alg2(chain2);

	file = new TFile("Z1_mass.root", "recreate");

	if(file != NULL)
	{
		bkgd = false;
		isMC = true;
		alg1.Loop();

		std::cout << std::endl;

		bkgd = true;
		isMC = true;
		alg1.Loop();

		std::cout << std::endl;

		bkgd = false;
		isMC = false;
		alg2.Loop();

		std::cout << std::endl;

		file->Close();

		delete file;
	}

	delete chain1;
	delete chain2;

	std::cout << "Bye." << std::endl;

	return 0;
}

/*-------------------------------------------------------------------------*/

void ZStudy::Loop(void)
{
	if(fChain == 0)
	{
		return;
	}	

	/**/

	TH1F h("", "", 200, 0.0f, 200.0f);

	if(isMC != false)
	{
		if(bkgd != false)
		{
			h.SetName("bkgd");
		}
		else
		{
			h.SetName("mc");
		}
	}
	else
	{
		h.SetName("data");
	}

	/**/

	Long64_t eventNr = fChain->GetEntries();

	/**/

	for(Long64_t event = 0; event < eventNr; event++)
	{
		if(this->LoadTree(event) < 0)
		{
			break;
		}

		fChain->GetEntry(event);

		if((event % 1000) == 0)
		{
			std::cout << "\033[sEvent " << event << "/" << eventNr << "\033[u" << std::flush;
		}

		/**/

		if(isMC == false)
		{
			Bool_t isOk = true;

			#include "grlZ1.h"

			if(isOk == false)
			{
				continue;
			}
		}

		/**/

		for(int i = 0; i < n; i++)
		{
			if(sameSign[i] == true
			   ||
			   l1_pt[i] < ET_MIN || l1_pt[i] > ET_MAX
			   ||
			   l2_pt[i] < ET_MIN || l2_pt[i] > ET_MAX
			   ||
			   fabs(l1_eta[i]) > 2.47f
			   ||
			   fabs(l2_eta[i]) > 2.47f
			 ) {
				continue;
			}

			if(bkgd != false && (l1_truthMatch[i] != false && l2_truthMatch[i] != false))
			{
				continue;
			}

			Float_t theWeight = weight1[i] * weight2[i] * weight3[i];

			if((l1_pt[i] > 10.0f && l2_pt[i] > 20.0f && l2_tight[i] != false && l2_tkIso20[i] < 0.15f)
			   ||
			   (l1_pt[i] > 20.0f && l2_pt[i] > 10.0f && l1_tight[i] != false && l1_tkIso20[i] < 0.15f)
			 ) {
				h.Fill(Z_m[i], theWeight);
			}
		}
	}

	/**/

	file->cd();

	h.Write();
}

/*-------------------------------------------------------------------------*/

