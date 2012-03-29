/*-------------------------------------------------------------------------*/

#ifndef __L_ANALYSIS
#define __L_ANALYSIS

/*-------------------------------------------------------------------------*/

#include "../higgs_analysis/utils.h"

/*-------------------------------------------------------------------------*/

#define MAX 2048

/*-------------------------------------------------------------------------*/

class TLeptonFinder: public TLeptonAnalysis
{
  public:
	TTree m_tree1;
	TTree m_tree2;
	TTree m_tree3;
	TTree m_tree4;

	TLeptonFinder(TChain *chain): TLeptonAnalysis(chain)
	{
		m_tree1.SetName("eSTACO");
		m_tree2.SetName("eMUID");
		m_tree3.SetName("muSTACO");
		m_tree4.SetName("muMUID");

		TTree *LTreeArray[4] = {&m_tree1, &m_tree2, &m_tree3, &m_tree4};

		/*---------------------------------------------------------*/
		/* LEPTON ANALYSIS					   */
		/*---------------------------------------------------------*/

		for(int i = 0; i < 4; i++)
		{
			TTree *tree = LTreeArray[i];

			/**/

			tree->Branch("RunNumber", &m_l[i].RunNumber, "RunNumber/I");
			tree->Branch("EventNumber", &m_l[i].EventNumber, "EventNumber/I");
			tree->Branch("LumiBlock", &m_l[i].LumiBlock, "LumiBlock/I");

			tree->Branch("nPV2", &m_l[i].nPV2, "nPV2/I");
			tree->Branch("nIntPerXing", &m_l[i].nIntPerXing, "nIntPerXing/F");

			tree->Branch("elTrigger", &m_l[i].elTrigger, "elTrigger/I");
			tree->Branch("muTrigger", &m_l[i].muTrigger, "muTrigger/I");

			/**/

			tree->Branch("n", &m_l[i].n, "n" "/I");

			tree->Branch("weight1", m_l[i].weight1, "weight1[n]/F");
			tree->Branch("weight2", m_l[i].weight2, "weight2[n]/F");
			tree->Branch("weight3", m_l[i].weight3, "weight3[n]/F");

			tree->Branch("l_tight", m_l[i].l_tight, "l_tight[n]/I");

			tree->Branch("l_charge", m_l[i].l_charge, "l_charge[n]/F");
			tree->Branch("l_e", m_l[i].l_e, "l_e[n]/F");
			tree->Branch("l_pt", m_l[i].l_pt, "l_pt[n]/F");
			tree->Branch("l_eta", m_l[i].l_eta, "l_eta[n]/F");
			tree->Branch("l_phi", m_l[i].l_phi, "l_phi[n]/F");


			tree->Branch("l_tkIso20", m_l[i].l_tkIso20, "l_tkIso20[n]/F");
			tree->Branch("l_clIso20", m_l[i].l_clIso20, "l_clIso20[n]/F");
			tree->Branch("l_d0sigma", m_l[i].l_d0sigma, "l_d0sigma[n]/F");
		}

		/*---------------------------------------------------------*/
	}

	void Loop(void);

  private:

	struct __lepton_s
	{
		Int_t RunNumber;
		Int_t EventNumber;
		Int_t LumiBlock;

		Int_t nPV2;
		Float_t nIntPerXing;

		Int_t elTrigger;
		Int_t muTrigger;

		/**/

		Int_t n;

		Float_t weight1[MAX];
		Float_t weight2[MAX];
		Float_t weight3[MAX];

		Int_t l_tight[MAX];

		Float_t l_charge[MAX];
		Float_t l_e[MAX];
		Float_t l_pt[MAX];
		Float_t l_eta[MAX];
		Float_t l_phi[MAX];

		Float_t l_clIso20[MAX];
		Float_t l_tkIso20[MAX];
		Float_t l_d0sigma[MAX];

	} m_l[4];

};

/*-------------------------------------------------------------------------*/

#endif /* __L_ANALYSIS */

/*-------------------------------------------------------------------------*/

