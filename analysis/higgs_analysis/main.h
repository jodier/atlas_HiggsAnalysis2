/*-------------------------------------------------------------------------*/

#ifndef __H_ANALYSIS_H
#define __H_ANALYSIS_H

/*-------------------------------------------------------------------------*/

#include "utils.h"

/*-------------------------------------------------------------------------*/

#define MAX 1024

/*-------------------------------------------------------------------------*/

class THiggsBuilder: public TLeptonAnalysis
{
  public:
	TTree m_tree0;
	TTree m_tree1;

	TTree m_tree2;
	TTree m_tree3;

	TTree m_tree4;
	TTree m_tree5;
	TTree m_tree6;

	THiggsBuilder(TChain *chain): TLeptonAnalysis(chain)
	{
		m_tree0.SetName("Truth");
		m_tree1.SetName("Event");

		m_tree2.SetName("Z1");	// ee
		m_tree3.SetName("Z3");	// µµ

		TTree *ZTreeArray[2] = {&m_tree2, &m_tree3};

		m_tree4.SetName("H1");	// eeee
		m_tree5.SetName("H2");	// µµµµ
		m_tree6.SetName("H3");  // eeµµ

		TTree *HTreeArray[3] = {&m_tree4, &m_tree5, &m_tree6};

		/*---------------------------------------------------------*/
		/* TRUTH						   */
		/*---------------------------------------------------------*/

		m_truth.eeee_nr = 0;
		m_truth.uuuu_nr = 0;
		m_truth.eeuu_nr = 0;

		m_tree0.Branch("eeee_nr", &m_truth.eeee_nr, "eeee_nr/I");
		m_tree0.Branch("uuuu_nr", &m_truth.uuuu_nr, "uuuu_nr/I");
		m_tree0.Branch("eeuu_nr", &m_truth.eeuu_nr, "eeuu_nr/I");		

		/*---------------------------------------------------------*/
		/* EVENTS						   */
		/*---------------------------------------------------------*/

		m_tree1.Branch("RunNumber", &m_evt.RunNumber, "RunNumber/I");
		m_tree1.Branch("EventNumber", &m_evt.EventNumber, "EventNumber/I");
		m_tree1.Branch("LumiBlock", &m_evt.LumiBlock, "LumiBlock/I");

		m_tree1.Branch("nPV2", &m_evt.nPV2, "nPV2/I");
		m_tree1.Branch("nIntPerXing", &m_evt.nIntPerXing, "nIntPerXing/F");

		m_tree1.Branch("elTrigger", &m_evt.elTrigger, "elTrigger/I");
		m_tree1.Branch("muTrigger", &m_evt.muTrigger, "muTrigger/I");

		m_tree1.Branch("el_raw_n", &m_evt.el_raw_n, "el_raw_n/I");
		m_tree1.Branch("mu_raw_n", &m_evt.mu_raw_n, "mu_raw_n/I");
		m_tree1.Branch("lepton_raw_n", &m_evt.lepton_raw_n, "lepton_raw_n/I");

		m_tree1.Branch("el_1st_n", &m_evt.el_1st_n, "el_1st_n/I");
		m_tree1.Branch("mu_1st_n", &m_evt.mu_1st_n, "mu_1st_n/I");
		m_tree1.Branch("lepton_1st_n", &m_evt.lepton_1st_n, "lepton_1st_n/I");

		m_tree1.Branch("el_2nd_n", &m_evt.el_2nd_n, "el_2nd_n/I");
		m_tree1.Branch("mu_2nd_n", &m_evt.mu_2nd_n, "mu_2nd_n/I");
		m_tree1.Branch("lepton_2nd_n", &m_evt.lepton_2nd_n, "lepton_2nd_n/I");

		/*---------------------------------------------------------*/
		/* Z ANALYSIS						   */
		/*---------------------------------------------------------*/

		for(int i = 0; i < 2; i++)
		{
			TTree *tree = ZTreeArray[i];

			//

			tree->Branch("RunNumber", &m_Z[i].RunNumber, "RunNumber/I");
			tree->Branch("EventNumber", &m_Z[i].EventNumber, "EventNumber/I");
			tree->Branch("LumiBlock", &m_Z[i].LumiBlock, "LumiBlock/I");

			tree->Branch("nPV2", &m_Z[i].nPV2, "nPV2/I");
			tree->Branch("nIntPerXing", &m_Z[i].nIntPerXing, "nIntPerXing/F");

			tree->Branch("elTrigger", &m_Z[i].elTrigger, "elTrigger/I");
			tree->Branch("muTrigger", &m_Z[i].muTrigger, "muTrigger/I");

			tree->Branch("tn", &m_Z[i].tn, "tn/I");
			tree->Branch("ta", m_Z[i].ta, "ta[tn]/i");

			//

			tree->Branch("n", &m_Z[i].n, "n" "/I");

			tree->Branch("weight1", m_Z[i].weight1, "weight1[n]/F");
			tree->Branch("weight2", m_Z[i].weight2, "weight2[n]/F");
			tree->Branch("weight3", m_Z[i].weight3, "weight3[n]/F");

			tree->Branch("l1_tight", m_Z[i].l1_tight, "l1_tight[n]/I");
			tree->Branch("l2_tight", m_Z[i].l2_tight, "l2_tight[n]/I");

			tree->Branch("l1_truthMatch", m_Z[i].l1_truthMatch, "l1_truthMatch[n]/I");
			tree->Branch("l2_truthMatch", m_Z[i].l2_truthMatch, "l2_truthMatch[n]/I");
			tree->Branch("l1_triggerMatch", m_Z[i].l1_triggerMatch, "l1_triggerMatch[n]/I");
			tree->Branch("l2_triggerMatch", m_Z[i].l2_triggerMatch, "l2_triggerMatch[n]/I");

			tree->Branch("l1_e", m_Z[i].l1_e, "l1_e[n]/F");
			tree->Branch("l2_e", m_Z[i].l2_e, "l2_e[n]/F");
			tree->Branch("l1_pt", m_Z[i].l1_pt, "l1_pt[n]/F");
			tree->Branch("l2_pt", m_Z[i].l2_pt, "l2_pt[n]/F");
			tree->Branch("l1_eta", m_Z[i].l1_eta, "l1_eta[n]/F");
			tree->Branch("l2_eta", m_Z[i].l2_eta, "l2_eta[n]/F");
			tree->Branch("l1_phi", m_Z[i].l1_phi, "l1_phi[n]/F");
			tree->Branch("l2_phi", m_Z[i].l2_phi, "l2_phi[n]/F");

			tree->Branch("l1_tkIso20", m_Z[i].l1_tkIso20, "l1_tkIso20[n]/F");
			tree->Branch("l2_tkIso20", m_Z[i].l2_tkIso20, "l2_tkIso20[n]/F");
			tree->Branch("l1_clIso20", m_Z[i].l1_clIso20, "l1_clIso20[n]/F");
			tree->Branch("l2_clIso20", m_Z[i].l2_clIso20, "l2_clIso20[n]/F");
			tree->Branch("l1_d0sigma", m_Z[i].l1_d0sigma, "l1_d0sigma[n]/F");
			tree->Branch("l2_d0sigma", m_Z[i].l2_d0sigma, "l2_d0sigma[n]/F");

			tree->Branch("Z_m", m_Z[i].Z_m, "Z_m[n]/F");
			tree->Branch("Z_et", m_Z[i].Z_et, "Z_et[n]/F");
			tree->Branch("Z_pt", m_Z[i].Z_pt, "Z_pt[n]/F");
			tree->Branch("Z_eta", m_Z[i].Z_eta, "Z_eta[n]/F");
			tree->Branch("Z_phi", m_Z[i].Z_phi, "Z_phi[n]/F");

			tree->Branch("sameSign", m_Z[i].sameSign, "sameSign[n]/I");
		}

		/*---------------------------------------------------------*/
		/* H ANALYSIS						   */
		/*---------------------------------------------------------*/

		for(int i = 0; i < 3; i++)
		{
			TTree *tree = HTreeArray[i];

			//

			tree->Branch("RunNumber", &m_H[i].RunNumber, "RunNumber/I");
			tree->Branch("EventNumber", &m_H[i].EventNumber, "EventNumber/I");
			tree->Branch("LumiBlock", &m_H[i].LumiBlock, "LumiBlock/I");

			tree->Branch("nPV2", &m_Z[i].nPV2, "nPV2/I");
			tree->Branch("nIntPerXing", &m_H[i].nIntPerXing, "nIntPerXing/F");

			tree->Branch("elTrigger", &m_H[i].elTrigger, "elTrigger/I");
			tree->Branch("muTrigger", &m_H[i].muTrigger, "muTrigger/I");

			tree->Branch("tn", &m_H[i].tn, "tn/I");
			tree->Branch("ta", m_H[i].ta, "ta[tn]/i");

			//

			tree->Branch("n", &m_H[i].n, "n/I");

			tree->Branch("weight1", m_H[i].weight1, "weight1[n]/F");
			tree->Branch("weight2", m_H[i].weight2, "weight2[n]/F");
			tree->Branch("weight3", m_H[i].weight3, "weight3[n]/F");

			tree->Branch("l1_triggerMatch", m_H[i].l1_triggerMatch, "l1_triggerMatch[n]/I");
			tree->Branch("l2_triggerMatch", m_H[i].l2_triggerMatch, "l2_triggerMatch[n]/I");
			tree->Branch("l3_triggerMatch", m_H[i].l3_triggerMatch, "l3_triggerMatch[n]/I");
			tree->Branch("l4_triggerMatch", m_H[i].l4_triggerMatch, "l4_triggerMatch[n]/I");

			tree->Branch("l1_e", m_H[i].l1_e, "l1_e[n]/F");
			tree->Branch("l2_e", m_H[i].l2_e, "l2_e[n]/F");
			tree->Branch("l3_e", m_H[i].l3_e, "l3_e[n]/F");
			tree->Branch("l4_e", m_H[i].l4_e, "l4_e[n]/F");
			tree->Branch("l1_pt", m_H[i].l1_pt, "l1_pt[n]/F");
			tree->Branch("l2_pt", m_H[i].l2_pt, "l2_pt[n]/F");
			tree->Branch("l3_pt", m_H[i].l3_pt, "l3_pt[n]/F");
			tree->Branch("l4_pt", m_H[i].l4_pt, "l4_pt[n]/F");
			tree->Branch("l1_eta", m_H[i].l1_eta, "l1_eta[n]/F");
			tree->Branch("l2_eta", m_H[i].l2_eta, "l2_eta[n]/F");
			tree->Branch("l3_eta", m_H[i].l3_eta, "l3_eta[n]/F");
			tree->Branch("l4_eta", m_H[i].l4_eta, "l4_eta[n]/F");
			tree->Branch("l1_phi", m_H[i].l1_phi, "l1_phi[n]/F");
			tree->Branch("l2_phi", m_H[i].l2_phi, "l2_phi[n]/F");
			tree->Branch("l3_phi", m_H[i].l3_phi, "l3_phi[n]/F");
			tree->Branch("l4_phi", m_H[i].l4_phi, "l4_phi[n]/F");

			tree->Branch("l1_type", m_H[i].l1_type, "l1_type[n]/F");
			tree->Branch("l2_type", m_H[i].l2_type, "l2_type[n]/F");
			tree->Branch("l3_type", m_H[i].l3_type, "l3_type[n]/F");
			tree->Branch("l4_type", m_H[i].l4_type, "l4_type[n]/F");
			tree->Branch("l1_origin", m_H[i].l1_origin, "l1_origin[n]/F");
			tree->Branch("l2_origin", m_H[i].l2_origin, "l2_origin[n]/F");
			tree->Branch("l3_origin", m_H[i].l3_origin, "l3_origin[n]/F");
			tree->Branch("l4_origin", m_H[i].l4_origin, "l4_origin[n]/F");
			tree->Branch("l1_typebkg", m_H[i].l1_typebkg, "l1_typebkg[n]/F");
			tree->Branch("l2_typebkg", m_H[i].l2_typebkg, "l2_typebkg[n]/F");
			tree->Branch("l3_typebkg", m_H[i].l3_typebkg, "l3_typebkg[n]/F");
			tree->Branch("l4_typebkg", m_H[i].l4_typebkg, "l4_typebkg[n]/F");
			tree->Branch("l1_originbkg", m_H[i].l1_originbkg, "l1_originbkg[n]/F");
			tree->Branch("l2_originbkg", m_H[i].l2_originbkg, "l2_originbkg[n]/F");
			tree->Branch("l3_originbkg", m_H[i].l3_originbkg, "l3_originbkg[n]/F");
			tree->Branch("l4_originbkg", m_H[i].l4_originbkg, "l4_originbkg[n]/F");
			tree->Branch("l1_truth_type", m_H[i].l1_truth_type, "l1_truth_type[n]/F");
			tree->Branch("l2_truth_type", m_H[i].l2_truth_type, "l2_truth_type[n]/F");
			tree->Branch("l3_truth_type", m_H[i].l3_truth_type, "l3_truth_type[n]/F");
			tree->Branch("l4_truth_type", m_H[i].l4_truth_type, "l4_truth_type[n]/F");
			tree->Branch("l1_truth_mothertype", m_H[i].l1_truth_mothertype, "l1_truth_mothertype[n]/F");
			tree->Branch("l2_truth_mothertype", m_H[i].l2_truth_mothertype, "l2_truth_mothertype[n]/F");
			tree->Branch("l3_truth_mothertype", m_H[i].l3_truth_mothertype, "l3_truth_mothertype[n]/F");
			tree->Branch("l4_truth_mothertype", m_H[i].l4_truth_mothertype, "l4_truth_mothertype[n]/F");

			tree->Branch("l1_f1", m_H[i].l1_f1, "l1_f1[n]/F");
			tree->Branch("l2_f1", m_H[i].l2_f1, "l2_f1[n]/F");
			tree->Branch("l3_f1", m_H[i].l3_f1, "l3_f1[n]/F");
			tree->Branch("l4_f1", m_H[i].l4_f1, "l4_f1[n]/F");
			tree->Branch("l1_rphi", m_H[i].l1_rphi, "l1_rphi[n]/F");
			tree->Branch("l2_rphi", m_H[i].l2_rphi, "l2_rphi[n]/F");
			tree->Branch("l3_rphi", m_H[i].l3_rphi, "l3_rphi[n]/F");
			tree->Branch("l4_rphi", m_H[i].l4_rphi, "l4_rphi[n]/F");
			tree->Branch("l1_nBlayerHits", m_H[i].l1_nBlayerHits, "l1_nBlayerHits[n]/I");
			tree->Branch("l2_nBlayerHits", m_H[i].l2_nBlayerHits, "l2_nBlayerHits[n]/I");
			tree->Branch("l3_nBlayerHits", m_H[i].l3_nBlayerHits, "l3_nBlayerHits[n]/I");
			tree->Branch("l4_nBlayerHits", m_H[i].l4_nBlayerHits, "l4_nBlayerHits[n]/I");
			tree->Branch("l1_nPixelHits", m_H[i].l1_nPixelHits, "l1_nPixelHits[n]/I");
			tree->Branch("l2_nPixelHits", m_H[i].l2_nPixelHits, "l2_nPixelHits[n]/I");
			tree->Branch("l3_nPixelHits", m_H[i].l3_nPixelHits, "l3_nPixelHits[n]/I");
			tree->Branch("l4_nPixelHits", m_H[i].l4_nPixelHits, "l4_nPixelHits[n]/I");
			tree->Branch("l1_rTRT", m_H[i].l1_rTRT, "l1_rTRT[n]/F");
			tree->Branch("l2_rTRT", m_H[i].l2_rTRT, "l2_rTRT[n]/F");
			tree->Branch("l3_rTRT", m_H[i].l3_rTRT, "l3_rTRT[n]/F");
			tree->Branch("l4_rTRT", m_H[i].l4_rTRT, "l4_rTRT[n]/F");

			tree->Branch("Z12_m", m_H[i].Z12_m, "Z12_m[n]/F");
			tree->Branch("Z34_m", m_H[i].Z34_m, "Z34_m[n]/F");
			tree->Branch("Z12_et", m_H[i].Z12_et, "Z12_et[n]/F");
			tree->Branch("Z34_et", m_H[i].Z34_et, "Z34_et[n]/F");
			tree->Branch("Z12_pt", m_H[i].Z12_pt, "Z12_pt[n]/F");
			tree->Branch("Z34_pt", m_H[i].Z34_pt, "Z34_pt[n]/F");
			tree->Branch("Z12_eta", m_H[i].Z12_eta, "Z12_eta[n]/F");
			tree->Branch("Z34_eta", m_H[i].Z34_eta, "Z34_eta[n]/F");
			tree->Branch("Z12_phi", m_H[i].Z12_phi, "Z12_phi[n]/F");
			tree->Branch("Z34_phi", m_H[i].Z34_phi, "Z34_phi[n]/F");

			tree->Branch("H_m", m_H[i].H_m, "H_m[n]/F");
			tree->Branch("H_et", m_H[i].H_et, "H_et[n]/F");
			tree->Branch("H_pt", m_H[i].H_pt, "H_pt[n]/F");
			tree->Branch("H_eta", m_H[i].H_eta, "H_eta[n]/F");
			tree->Branch("H_phi", m_H[i].H_phi, "H_phi[n]/F");

			tree->Branch("eeuu", m_H[i].eeuu, "eeuu[n]/I");
			tree->Branch("good", m_H[i].good, "good[n]/I");

			tree->Branch("flag", m_H[i].flag, "flag[n]/i");

			tree->Branch("cnt0", &m_H[i].cnt[0], "cnt0/S");
			tree->Branch("cnt1", &m_H[i].cnt[1], "cnt1/S");
			tree->Branch("cnt2", &m_H[i].cnt[2], "cnt2/S");
			tree->Branch("cnt3", &m_H[i].cnt[3], "cnt3/S");
			tree->Branch("cnt4", &m_H[i].cnt[4], "cnt4/S");
			tree->Branch("cnt5", &m_H[i].cnt[5], "cnt5/S");
			tree->Branch("cnt6", &m_H[i].cnt[6], "cnt6/S");
			tree->Branch("cnt7", &m_H[i].cnt[7], "cnt7/S");
			tree->Branch("cnt8_eeuu", &m_H[i].cnt[8], "cnt8_eeuu/S");
			tree->Branch("cnt8_uuee", &m_H[i].cnt[9], "cnt8_uuee/S");
			tree->Branch("cnt9_eeuu", &m_H[i].cnt[10], "cnt9_eeuu/S");
			tree->Branch("cnt9_uuee", &m_H[i].cnt[11], "cnt9_uuee/S");
			tree->Branch("cnt10_eeuu", &m_H[i].cnt[12], "cnt10_eeuu/S");
			tree->Branch("cnt10_uuee", &m_H[i].cnt[13], "cnt10_uuee/S");
		}

		/*---------------------------------------------------------*/
	}

	void Loop(void);

	/* ANALYSIS */

	bool Z_analysis(
		int index1,
		int index2,
		TLeptonType type1,
		TLeptonType type2,
		int dest
	);

	bool H_analysis(
		int index1,
		int index2,
		int index3,
		int index4,
		TLeptonType type1,
		TLeptonType type2,
		TLeptonType type3,
		TLeptonType type4,
		int dest
	);

	void selectQuadruplet(int dest, Float_t Z_MASS);

  private:
	struct __truth_s
	{
		Int_t eeee_nr;
		Int_t uuuu_nr;
		Int_t eeuu_nr;

	} m_truth;

	struct __event_s
	{
		Int_t RunNumber;
		Int_t EventNumber;
		Int_t LumiBlock;

		Int_t nPV2;
		Float_t nIntPerXing;

		Int_t elTrigger;
		Int_t muTrigger;

		/**/

		Int_t el_raw_n;
		Int_t mu_raw_n;
		Int_t lepton_raw_n;

		Int_t el_1st_n;
		Int_t mu_1st_n;
		Int_t lepton_1st_n;

		Int_t el_2nd_n;
		Int_t mu_2nd_n;
		Int_t lepton_2nd_n;

	} m_evt;

	struct __z_boson_s
	{
		Int_t RunNumber;
		Int_t EventNumber;
		Int_t LumiBlock;

		Int_t nPV2;
		Float_t nIntPerXing;

		Int_t elTrigger;
		Int_t muTrigger;

		Int_t tn;
		UInt_t ta[MAX];

		/**/

		Int_t n;

		Float_t weight1[MAX];
		Float_t weight2[MAX];
		Float_t weight3[MAX];

		Int_t l1_tight[MAX];
		Int_t l2_tight[MAX];

		Int_t l1_truthMatch[MAX];
		Int_t l2_truthMatch[MAX];
		Int_t l1_triggerMatch[MAX];
		Int_t l2_triggerMatch[MAX];

		Float_t l1_e[MAX];
		Float_t l2_e[MAX];
		Float_t l1_pt[MAX];
		Float_t l2_pt[MAX];
		Float_t l1_eta[MAX];
		Float_t l2_eta[MAX];
		Float_t l1_phi[MAX];
		Float_t l2_phi[MAX];

		Float_t l1_clIso20[MAX];
		Float_t l2_clIso20[MAX];
		Float_t l1_tkIso20[MAX];
		Float_t l2_tkIso20[MAX];
		Float_t l1_d0sigma[MAX];
		Float_t l2_d0sigma[MAX];

		Float_t Z_m[MAX];
		Float_t Z_et[MAX];
		Float_t Z_pt[MAX];
		Float_t Z_eta[MAX];
		Float_t Z_phi[MAX];

		Int_t sameSign[MAX];

	} m_Z[2];

	struct __higgs_boson_s
	{
		Int_t RunNumber;
		Int_t EventNumber;
		Int_t LumiBlock;

		Int_t nPV2;
		Float_t nIntPerXing;

		Int_t elTrigger;
		Int_t muTrigger;

		Int_t tn;
		UInt_t ta[MAX];

		/**/

		Int_t n;

		Float_t weight1[MAX];
		Float_t weight2[MAX];
		Float_t weight3[MAX];

		Int_t l1_triggerMatch[MAX];
		Int_t l2_triggerMatch[MAX];
		Int_t l3_triggerMatch[MAX];
		Int_t l4_triggerMatch[MAX];

		Float_t l1_e[MAX];
		Float_t l2_e[MAX];
		Float_t l3_e[MAX];
		Float_t l4_e[MAX];
		Float_t l1_pt[MAX];
		Float_t l2_pt[MAX];
		Float_t l3_pt[MAX];
		Float_t l4_pt[MAX];
		Float_t l1_eta[MAX];
		Float_t l2_eta[MAX];
		Float_t l3_eta[MAX];
		Float_t l4_eta[MAX];
		Float_t l1_phi[MAX];
		Float_t l2_phi[MAX];
		Float_t l3_phi[MAX];
		Float_t l4_phi[MAX];

		Float_t l1_type[MAX];
		Float_t l2_type[MAX];
		Float_t l3_type[MAX];
		Float_t l4_type[MAX];
		Float_t l1_origin[MAX];
		Float_t l2_origin[MAX];
		Float_t l3_origin[MAX];
		Float_t l4_origin[MAX];
		Float_t l1_typebkg[MAX];
		Float_t l2_typebkg[MAX];
		Float_t l3_typebkg[MAX];
		Float_t l4_typebkg[MAX];
		Float_t l1_originbkg[MAX];
		Float_t l2_originbkg[MAX];
		Float_t l3_originbkg[MAX];
		Float_t l4_originbkg[MAX];
		Float_t l1_truth_type[MAX];
		Float_t l2_truth_type[MAX];
		Float_t l3_truth_type[MAX];
		Float_t l4_truth_type[MAX];
		Float_t l1_truth_mothertype[MAX];
		Float_t l2_truth_mothertype[MAX];
		Float_t l3_truth_mothertype[MAX];
		Float_t l4_truth_mothertype[MAX];

		Float_t l1_f1[MAX];
		Float_t l2_f1[MAX];
		Float_t l3_f1[MAX];
		Float_t l4_f1[MAX];
		Float_t l1_rphi[MAX];
		Float_t l2_rphi[MAX];
		Float_t l3_rphi[MAX];
		Float_t l4_rphi[MAX];
		Int_t l1_nBlayerHits[MAX];
		Int_t l2_nBlayerHits[MAX];
		Int_t l3_nBlayerHits[MAX];
		Int_t l4_nBlayerHits[MAX];
		Int_t l1_nPixelHits[MAX];
		Int_t l2_nPixelHits[MAX];
		Int_t l3_nPixelHits[MAX];
		Int_t l4_nPixelHits[MAX];
		Float_t l1_rTRT[MAX];
		Float_t l2_rTRT[MAX];
		Float_t l3_rTRT[MAX];
		Float_t l4_rTRT[MAX];

		Float_t Z12_m[MAX];
		Float_t Z34_m[MAX];
		Float_t Z12_et[MAX];
		Float_t Z34_et[MAX];
		Float_t Z12_pt[MAX];
		Float_t Z34_pt[MAX];
		Float_t Z12_eta[MAX];
		Float_t Z34_eta[MAX];
		Float_t Z12_phi[MAX];
		Float_t Z34_phi[MAX];

		Float_t H_m[MAX];
		Float_t H_et[MAX];
		Float_t H_pt[MAX];
		Float_t H_eta[MAX];
		Float_t H_phi[MAX];

		Int_t eeuu[MAX];
		Int_t good[MAX];

		UInt_t flag[MAX];

		Short_t cnt[8 + 2 * 3];

	} m_H[3];
};

/*-------------------------------------------------------------------------*/

#endif /* __H_ANALYSIS_H */

/*-------------------------------------------------------------------------*/

