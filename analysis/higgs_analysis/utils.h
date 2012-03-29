/*-------------------------------------------------------------------------*/

#ifndef __LEPTON_ANALYSIS_H
#define __LEPTON_ANALYSIS_H

/*-------------------------------------------------------------------------*/

#include "../../core/include/core.h"

#include <PileupReweighting/TPileupReweighting.h>

#include <MuonEfficiencyCorrections/AnalysisMuonEfficiencyScaleFactors.h>
#include <MuonMomentumCorrections/SmearingClass.h>
#include <MuonIsolationCorrection/CorrectCaloIso.h>

#include <egammaAnalysisUtils/EnergyRescaler.h>
#include <egammaAnalysisUtils/egammaSFclass.h>

#include <TrigMuonEfficiency/TriggerNavigationVariables.h>
#include <TrigMuonEfficiency/ElectronTriggerMatching.h>
#include <TrigMuonEfficiency/MuonTriggerMatching.h>

/*-------------------------------------------------------------------------*/

using namespace Root;
using namespace eg2011;
using namespace Analysis;
using namespace MuonSmear;

/*-------------------------------------------------------------------------*/

typedef enum TLeptonClass
{
	CLASS_ELECTRON
	,
	CLASS_MUON

} TLeptonClass;

/*-------------------------------------------------------------------------*/

typedef enum TLeptonType
{
	TYPE_ELECTRON
	,
	TYPE_MUON_STACO
	,
	TYPE_MUON_CALO

} TLeptonType;

/*-------------------------------------------------------------------------*/

class TLeptonAnalysis: public TNTuple
{
  protected:
	void fixeEnergy(void);

  public:
	Int_t nPV2;
	Int_t nPV3;

	UInt_t elTrigger;
	UInt_t muTrigger;

	/*-----------------------------------------------------------------*/
	/* TOOLS							   */
	/*-----------------------------------------------------------------*/

	TPileupReweighting *m_pileupReweighting;

	AnalysisMuonEfficiencyScaleFactors *m_stacoSF;

	SmearingClass *m_stacoSM;

	EnergyRescaler *m_energyRescaler;
	egammaSFclass *m_egammaSF;
	CorrectCaloIso *m_correctCaloIso;

	TriggerNavigationVariables *m_triggerNavigationVariables;
	ElectronTriggerMatching *m_elTriggerMatching;
	MuonTriggerMatching *m_muTriggerMatching;

	/*-----------------------------------------------------------------*/

	Float_t lumiPeriodB;
	Float_t lumiPeriodD;
	Float_t lumiPeriodE;
	Float_t lumiPeriodF;
	Float_t lumiPeriodG;
	Float_t lumiPeriodH;
	Float_t lumiPeriodI;
	Float_t lumiPeriodJ;
	Float_t lumiPeriodK;
	Float_t lumiPeriodL;
	Float_t lumiPeriodM;

	/*-----------------------------------------------------------------*/

	TLeptonAnalysis(TChain *chain): TNTuple(chain), elTrigger(0), muTrigger(0)
	{
		m_pileupReweighting = new TPileupReweighting();

		/**/

		m_pileupReweighting->SetUnrepresentedDataAction(2);
		m_pileupReweighting->AddConfigFile("analysis/MC11c.prw.root");
		m_pileupReweighting->AddLumiCalcFile("analysis/ilumicalc_period_AllYear_Higgs_4l_2e2mu.root"); 
		m_pileupReweighting->SetDefaultChannel(109292);
		m_pileupReweighting->Initialize();

		lumiPeriodB = m_pileupReweighting->GetIntegratedLumi(177986, 178109);
		lumiPeriodD = m_pileupReweighting->GetIntegratedLumi(179710, 180481);
		lumiPeriodE = m_pileupReweighting->GetIntegratedLumi(180614, 180776);
		lumiPeriodF = m_pileupReweighting->GetIntegratedLumi(182013, 182519);
		lumiPeriodG = m_pileupReweighting->GetIntegratedLumi(182726, 183462);
		lumiPeriodH = m_pileupReweighting->GetIntegratedLumi(183544, 184169);
		lumiPeriodI = m_pileupReweighting->GetIntegratedLumi(185353, 186493);
		lumiPeriodJ = m_pileupReweighting->GetIntegratedLumi(186516, 186755);
		lumiPeriodK = m_pileupReweighting->GetIntegratedLumi(186873, 187815);
		lumiPeriodL = m_pileupReweighting->GetIntegratedLumi(188902, 190343);
		lumiPeriodM = m_pileupReweighting->GetIntegratedLumi(190503, 191933);

		/**/

		Vector_t<Double_t> int_lum(11);

		int_lum[ 0] = lumiPeriodB;
		int_lum[ 1] = lumiPeriodD;
		int_lum[ 2] = lumiPeriodE;
		int_lum[ 3] = lumiPeriodF;
		int_lum[ 4] = lumiPeriodG;
		int_lum[ 5] = lumiPeriodH;
		int_lum[ 6] = lumiPeriodI;
		int_lum[ 7] = lumiPeriodJ;
		int_lum[ 8] = lumiPeriodK;
		int_lum[ 9] = lumiPeriodL;
		int_lum[10] = lumiPeriodM;

		m_stacoSF = new AnalysisMuonEfficiencyScaleFactors("STACO_CB", int_lum, "MeV", "./tools/MuonEfficiencyCorrections-01-01-03/share/");

		m_stacoSM = new SmearingClass("Data11", "staco", "pT", "Rel17", "./tools/MuonMomentumCorrections-00-05-03/share/");

		m_energyRescaler = new EnergyRescaler();
		m_egammaSF = new egammaSFclass();
		m_correctCaloIso = new CorrectCaloIso();

		/**/

		m_triggerNavigationVariables = new TriggerNavigationVariables();

		m_elTriggerMatching = new ElectronTriggerMatching(m_triggerNavigationVariables);
		m_muTriggerMatching = new MuonTriggerMatching(m_triggerNavigationVariables);

		/**/

		m_stacoSM->UseScale(1);

		m_energyRescaler->useDefaultCalibConstants("2011");
	}

	/*-----------------------------------------------------------------*/

	~TLeptonAnalysis(void)
	{
		delete m_pileupReweighting;

		delete m_stacoSF;

		delete m_stacoSM;

		delete m_energyRescaler;
		delete m_egammaSF;
		delete m_correctCaloIso;

		delete m_triggerNavigationVariables;
		delete m_elTriggerMatching;
		delete m_muTriggerMatching;
	}

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	void triggerInit(void)
	{
		m_triggerNavigationVariables->set_trig_DB_SMK(trig_DB_SMK);
		m_triggerNavigationVariables->set_trig_Nav_n(trig_Nav_n);
		m_triggerNavigationVariables->set_trig_Nav_chain_ChainId(trig_Nav_chain_ChainId);
		m_triggerNavigationVariables->set_trig_Nav_chain_RoIType(trig_Nav_chain_RoIType);
		m_triggerNavigationVariables->set_trig_Nav_chain_RoIIndex(trig_Nav_chain_RoIIndex);

		/* electron */
		m_triggerNavigationVariables->set_trig_RoI_EF_e_egammaContainer_egamma_Electrons(trig_RoI_EF_e_egammaContainer_egamma_Electrons);
		m_triggerNavigationVariables->set_trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus(trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus);
		m_triggerNavigationVariables->set_trig_EF_el_n(trig_EF_el_n);
		m_triggerNavigationVariables->set_trig_EF_el_eta(trig_EF_el_eta);
		m_triggerNavigationVariables->set_trig_EF_el_phi(trig_EF_el_phi);

		/* muon */
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_Muon_ROI(trig_RoI_EF_mu_Muon_ROI);
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainer(trig_RoI_EF_mu_TrigMuonEFInfoContainer);
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_CombinedMuonFeature(trig_RoI_L2_mu_CombinedMuonFeature);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_CombinedMuonFeatureStatus(trig_RoI_L2_mu_CombinedMuonFeatureStatus);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_MuonFeature(trig_RoI_L2_mu_MuonFeature);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_Muon_ROI(trig_RoI_L2_mu_Muon_ROI);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_pt(trig_EF_trigmuonef_track_CB_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_eta(trig_EF_trigmuonef_track_CB_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_phi(trig_EF_trigmuonef_track_CB_phi);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_pt(trig_EF_trigmuonef_track_SA_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_eta(trig_EF_trigmuonef_track_SA_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_phi(trig_EF_trigmuonef_track_SA_phi);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_pt(trig_EF_trigmugirl_track_CB_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_eta(trig_EF_trigmugirl_track_CB_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_phi(trig_EF_trigmugirl_track_CB_phi);
		m_triggerNavigationVariables->set_trig_L2_combmuonfeature_eta(trig_L2_combmuonfeature_eta);
		m_triggerNavigationVariables->set_trig_L2_combmuonfeature_phi(trig_L2_combmuonfeature_phi);
		m_triggerNavigationVariables->set_trig_L2_muonfeature_eta(trig_L2_muonfeature_eta);
		m_triggerNavigationVariables->set_trig_L2_muonfeature_phi(trig_L2_muonfeature_phi);
		m_triggerNavigationVariables->set_trig_L1_mu_eta(trig_L1_mu_eta);
		m_triggerNavigationVariables->set_trig_L1_mu_phi(trig_L1_mu_phi);
		m_triggerNavigationVariables->set_trig_L1_mu_thrName(trig_L1_mu_thrName);

		if(m_triggerNavigationVariables->isValid() == false)
		{
			std::cerr << "VARIABLES NOT CORRECTLY SET\n";

			exit(1);
		}
	}

	/*-----------------------------------------------------------------*/
	/* DEFINITIONS							   */
	/*-----------------------------------------------------------------*/

	Float_t eventGetWeight1(void);
	Float_t eventGetWeight2(void);
	Float_t eventGetWeight3(
		Int_t index,
		TLeptonType type
	);

	Float_t electronGetEtaDirection(Int_t index);
	Float_t electronGetPhiDirection(Int_t index);
	Float_t electronGetEt(Int_t index);

	Bool_t el_loosePP_at(Int_t index);
	Bool_t el_loosePP_cr_at(Int_t index);

	/*-----------------------------------------------------------------*/
	/* SELECTION							   */
	/*-----------------------------------------------------------------*/

	Bool_t checkObject(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Float_t __mu_calo_pt,
		Bool_t useLoose,
		Bool_t useForward
	);

	Bool_t checkOverlapping(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Float_t __mu_calo_pt,
		Bool_t useLoose,
		Bool_t useForward,
		Int_t muonIndexNr, Int_t muonIndexArray[], TLeptonType muonTypeArray[]
	);

	/*-----------------------------------------------------------------*/
	/* TRUTH							   */
	/*-----------------------------------------------------------------*/

	Bool_t truthMatch(
		Int_t index,
		TLeptonType type
	);

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	UInt_t getElTrigger(void);
	UInt_t getMuTrigger(void);

	UInt_t triggerMatch(
		Int_t index,
		TLeptonType type
	);

	Int_t triggerTrace(UInt_t result[]);

	/*-----------------------------------------------------------------*/
};

/*-------------------------------------------------------------------------*/
/* UTILS								   */
/*-------------------------------------------------------------------------*/

Float_t __dR2(
	Float_t eta1, Float_t eta2,
	Float_t phi1, Float_t phi2
);

TLeptonClass getLeptonClass(TLeptonType type);

Bool_t buildPair(
	Int_t pair[2],
	Float_t charge1,
	Float_t charge2
);

Bool_t buildPairs(
	Int_t pair1[2],
	Int_t pair2[2],
	Int_t pair3[2],
	Int_t pair4[2],
	TLeptonType type1,
	TLeptonType type2,
	TLeptonType type3,
	TLeptonType type4,
	Float_t charge1,
	Float_t charge2,
	Float_t charge3,
	Float_t charge4
);

void reIndex(
	Int_t L[4],
	Float_t M[4],
	Int_t (* func)(const void *, const void *)
);

/*-------------------------------------------------------------------------*/

#endif /* __LEPTON_ANALYSIS_H */

/*-------------------------------------------------------------------------*/

