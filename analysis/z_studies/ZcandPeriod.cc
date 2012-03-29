/*-------------------------------------------------------------------------*/

#include <cmath>
#include <fstream>
#include <iostream>

#include <TH1.h>

/*-------------------------------------------------------------------------*/

#define ZStudy_cxx
#include "ZStudy.h"

static bool isMC = false;
static const char *DataType = "";

TFile *file;

/*-------------------------------------------------------------------------*/

#define ET_MIN		20.0f		/* GeV */
#define ET_MAX		9000.0f		/* GeV */
#define MASS_CENTER	91.1876f	/* GeV */
#define MASS_WINDOW	15.0f		/* GeV */

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
	if(argc != 8)
	{
		std::cerr << argv[0] << " mc0.txt mc1.txt mc2.txt mc3.txt mc4.txt mc5.txt data.txt" << std::endl;
		return 1;
	}

	TChain *chain1 = new TChain("Z4");
	TChain *chain2 = new TChain("Z4");
	TChain *chain3 = new TChain("Z4");
	TChain *chain4 = new TChain("Z4");
	TChain *chain5 = new TChain("Z4");
	TChain *chain6 = new TChain("Z4");
	TChain *chain7 = new TChain("Z4");

	if(localLoader(chain1, argv[1]) == false
	   ||
	   localLoader(chain2, argv[2]) == false
	   ||
	   localLoader(chain3, argv[3]) == false
	   ||
	   localLoader(chain4, argv[4]) == false
	   ||
	   localLoader(chain5, argv[5]) == false
	   ||
	   localLoader(chain6, argv[6]) == false
	   ||
	   localLoader(chain7, argv[7]) == false
	 ) {
		delete chain1;
		delete chain2;
		delete chain3;
		delete chain4;
		delete chain5;
		delete chain6;
		delete chain7;

		return 1;
	}

	ZStudy alg1(chain1); //MC
	ZStudy alg2(chain2); //MC
	ZStudy alg3(chain3); //MC
	ZStudy alg4(chain4); //MC
	ZStudy alg5(chain5); //MC
	ZStudy alg6(chain6); //MC
	ZStudy alg7(chain7); //DATA

	file = new TFile("Z4candPeriod_trackIsoCut.root", "recreate");

	if(file != NULL)
	{
		isMC = true;

		DataType = "mc0";
		alg1.Loop();
		std::cout << std::endl;

		DataType = "mc1";
		alg2.Loop();
		std::cout << std::endl;

		DataType = "mc2";
		alg3.Loop();
		std::cout << std::endl;

		DataType = "mc3";
		alg4.Loop();
		std::cout << std::endl;

		DataType = "mc4";
		alg5.Loop();
		std::cout << std::endl;

		DataType = "mc5";
		alg6.Loop();
		std::cout << std::endl;

		isMC = false;

		DataType = "data";
		alg7.Loop();
		std::cout << std::endl;

		file->Close();

		delete file;
	}

	delete chain1;
	delete chain2;
	delete chain3;
	delete chain4;
	delete chain5;
	delete chain6;
	delete chain7;

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

	TH1D h(DataType, DataType, 11, 1, 12);

	/**/

	Long64_t eventNr = fChain->GetEntries();

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
			Bool_t isOk = false;

			#include "grlZ4.h"

			if(isOk == false)
			{
				continue;
			}
		}

		/**/

		for(int i = 0; i < n; i++)
		{
			if(l1_pt[i] < ET_MIN || l1_pt[i] > ET_MAX
			   ||
			   l2_pt[i] < ET_MIN || l2_pt[i] > ET_MAX
			   ||
			   fabs(Z_m[i] - MASS_CENTER) > MASS_WINDOW
			   ||
			   sameSign[i] == true
			   ||
			   l1_tkIso20[i] > 0.15 || l2_tkIso20[i] > 0.15 
			 ) {
				continue;
			}

			Float_t theWeight = weight1[i] * weight2[i] * weight3[i];

			if(isMC != false)
			{
				switch(RunNumber)
				{
					case 180164:
						//theWeight = theWeight / 1.06f;

						h.Fill(1, theWeight);
						h.Fill(2, theWeight);
						break;

					case 183003:
						//theWeight = theWeight / 1.08f;

						h.Fill(3, theWeight);
						h.Fill(4, theWeight);
						h.Fill(5, theWeight);
						h.Fill(6, theWeight);
						break;

					case 186169:
						//theWeight = theWeight / 0.87f;

						h.Fill(7, theWeight);
						h.Fill(8, theWeight);
						h.Fill(9, theWeight);
						break;

					case 186275:
						//theWeight = theWeight / 1.03f;

						h.Fill(10, theWeight);
						h.Fill(11, theWeight);
						break;

					default:
						std::cout << "TLeptonAnalysis::eventGetWeight2() - Oula !" << std::endl;
						theWeight = 0.0f;
						break;
				}
			}

			else
			{
				/**/ if(RunNumber >= 177986 && RunNumber <= 178109) { h.Fill(1, theWeight); }
				else if(RunNumber >= 179710 && RunNumber <= 180481) { h.Fill(2, theWeight); }
				else if(RunNumber >= 180614 && RunNumber <= 180776) { h.Fill(3, theWeight); }
				else if(RunNumber >= 182013 && RunNumber <= 182519) { h.Fill(4, theWeight); }
				else if(RunNumber >= 182726 && RunNumber <= 183462) { h.Fill(5, theWeight); }
				else if(RunNumber >= 183544 && RunNumber <= 184169) { h.Fill(6, theWeight); }
				else if(RunNumber >= 185353 && RunNumber <= 186493) { h.Fill(7, theWeight); }
				else if(RunNumber >= 186516 && RunNumber <= 186755) { h.Fill(8, theWeight); }
				else if(RunNumber >= 186873 && RunNumber <= 187815) { h.Fill(9, theWeight); }
				else if(RunNumber >= 188902 && RunNumber <= 190343) { h.Fill(10, theWeight);}
				else if(RunNumber >= 190503 && RunNumber <= 191933) { h.Fill(11, theWeight);}
			}
		}
	}

	/**/

	file->cd();

	h.Write();

}

/*-------------------------------------------------------------------------*/

