/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstring>
#include <iostream>

#include <egammaAnalysisUtils/CaloIsoCorrection.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

void core::execute(TChain *chain)
{
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << "/* EXECUTE                                                                 */" << std::endl;
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;

	TLeptonFinder algo(chain);
	algo.Loop();

	/**/

	TFile file(core::output.c_str(), "recreate");

	file.cd();

	algo.m_tree1.Write();
	algo.m_tree2.Write();
	algo.m_tree3.Write();
	algo.m_tree4.Write();

	file.Close();

}
/*-------------------------------------------------------------------------*/

extern Float_t getMassCut(Float_t H_mass);

/*-------------------------------------------------------------------------*/

void TLeptonFinder::Loop(void)
{
	Int_t elStacoIndexNr;
	Int_t elMuidIndexNr;
	Int_t elCaloIndexNr;
	Int_t muStacoIndexNr;
	Int_t muMuidIndexNr;
	Int_t muCaloIndexNr;

	Int_t elStacoIndexArray[1024];
	Int_t elMuidIndexArray[1024];
	Int_t elCaloIndexArray[1024];
	Int_t muStacoIndexArray[1024];
	Int_t muMuidIndexArray[1024];
	Int_t muCaloIndexArray[1024];

	Float_t higgs_el_et = core::configFltLookup("higgs_el_et");
	Float_t higgs_mu_pt = core::configFltLookup("higgs_mu_pt");
	Float_t higgs_mu_calo_pt = core::configFltLookup("higgs_mu_calo_pt");

	const Long64_t eventNr = fChain->GetEntries();

	for(Long64_t event = 0; event < eventNr; event++)
	{

		/*---------------------------------------------------------*/

		LoadEvent(event, eventNr);

		fixeEnergy();

		/*---------------------------------------------------------*/
		/* INIT							   */
		/*---------------------------------------------------------*/	

		elStacoIndexNr = 0;
		elMuidIndexNr = 0;
		elCaloIndexNr = 0;
		muStacoIndexNr = 0;
		muMuidIndexNr = 0;
		muCaloIndexNr = 0;

		/*---------------------------------------------------------*/
		/* AT LEAST 3 PRIMARY TRACKS AND LAR ERROR		   */
		/*---------------------------------------------------------*/

		nPV2 = 0;
		nPV3 = 0;

		for(Int_t i = 0; i < Int_t(vxp_nTracks->size()); i++)
		{
			if(vxp_nTracks->at(i) >= 2) {
				nPV2++;
			}

			if(vxp_nTracks->at(i) >= 3) {
				nPV3++;
			}
		}

		/**/
#ifdef __IS_MC
		Bool_t isOkVertex = (nPV3 > 0) && (0x00000000001);
#else
		Bool_t isOkVertex = (nPV3 > 0) && (larError != 2);
#endif
		/*---------------------------------------------------------*/
		/* SELECTION e or mu					   */
		/*---------------------------------------------------------*/

		Bool_t isOkElTrigger = getElTrigger();
		Bool_t isOkMuTrigger = getMuTrigger();

		Bool_t useLoose = core::configFltLookup("EL_USE_LOOSE") != 0.0f;
		Bool_t useForward = core::configFltLookup("EL_USE_FORWARD") != 0.0f;

		/*---------------------------------------------------------*/

		if(isOkElTrigger != false && isOkVertex != false)
		{
			for(Int_t i = 0; i < el_n; i++)
			{
				if(checkObject(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					if(checkStacoOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elStacoIndexArray[elStacoIndexNr++] = i;
					}

					if(checkMuidOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elMuidIndexArray[elMuidIndexNr++] = i;
					}

					if(checkCaloOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elCaloIndexArray[elCaloIndexNr++] = i;
					}
				}
			}
		}

		if(isOkMuTrigger != false && isOkVertex != false)
		{
			for(Int_t i = 0; i < mu_staco_n; i++)
			{
				if(checkObject(i, TYPE_MUON_STACO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muStacoIndexArray[muStacoIndexNr++] = i;
				}
			}

			for(Int_t i = 0; i < mu_muid_n; i++)
			{
				if(checkObject(i, TYPE_MUON_MUID, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muMuidIndexArray[muMuidIndexNr++] = i;
				}
			}

			for(Int_t i = 0; i < mu_calo_n; i++)
			{
				if(checkObject(i, TYPE_MUON_CALO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muCaloIndexArray[muCaloIndexNr++] = i;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* Loop electron (staco)				   */
		/*---------------------------------------------------------*/

		Int_t nrElStaco = 0;

		m_l[0].n = elStacoIndexNr;

		for(Int_t i = 0; i < elStacoIndexNr; i++)
		{
			Int_t index = elStacoIndexArray[i];

			/**/

			m_l[0].RunNumber = RunNumber;
			m_l[0].EventNumber = EventNumber;
			m_l[0].LumiBlock = lbn;

			m_l[0].nPV2 = nPV2;
			m_l[0].nIntPerXing = averageIntPerXing;

			m_l[0].elTrigger = isOkElTrigger;
			m_l[0].muTrigger = isOkMuTrigger;

			/**/

			m_l[0].weight1[i] = eventGetWeight1();
			m_l[0].weight2[i] = eventGetWeight2();
			m_l[0].weight3[i] = eventGetWeight3(index, TYPE_ELECTRON);

			m_l[0].l_tight[i] = el_tight->at(index) != 0;

			m_l[0].l_charge[i] = el_charge->at(index);
			m_l[0].l_e[i] = el_cl_E->at(index);
			m_l[0].l_pt[i] = electronGetEt(index);
			m_l[0].l_eta[i] = electronGetEtaDirection(index);
			m_l[0].l_phi[i] = electronGetPhiDirection(index);

			m_l[0].l_clIso20[i] = CaloIsoCorrection::GetNPVCorrectedIsolation(nPV2, el_etas2->at(index), 20, __isMC, el_Etcone20->at(index), CaloIsoCorrection::ELECTRON) / electronGetEt(index);
			m_l[0].l_tkIso20[i] = el_ptcone20->at(index) / electronGetEt(index);
			m_l[0].l_d0sigma[i] = fabs(el_trackd0pvunbiased->at(index) / el_tracksigd0pvunbiased->at(index));

			for(Int_t j = i + 1; j < elStacoIndexNr; j++)
			{
				Int_t index2 = elStacoIndexArray[j];

				if(sqrtf(__dR2(m_l[0].l_eta[i], electronGetEtaDirection(index2), m_l[0].l_phi[i], electronGetPhiDirection(index2))) < 0.20f)
				{
					m_l[0].l_tkIso20[i] -= el_trackpt->at(index2) / m_l[0].l_pt[i];
				}

				if(sqrtf(__dR2(m_l[0].l_eta[i], electronGetEtaDirection(index2), m_l[0].l_phi[i], electronGetPhiDirection(index2))) < 0.18f)
				{
					m_l[0].l_clIso20[i] -= electronGetEt(index2) / m_l[0].l_pt[i];
				}
			}

			if(m_l[0].l_pt[i] > 7000.0) {
				nrElStaco++;
			}
		}

		/*---------------------------------------------------------*/
		/* Loop electron (muid)					   */
		/*---------------------------------------------------------*/

		Int_t nrElMuid = 0;

		m_l[1].n = elMuidIndexNr;

		for(Int_t i = 0; i < elMuidIndexNr; i++)
		{
			Int_t index = elMuidIndexArray[i];

			/**/

			m_l[1].RunNumber = RunNumber;
			m_l[1].EventNumber = EventNumber;
			m_l[1].LumiBlock = lbn;

			m_l[1].nPV2 = nPV2;
			m_l[1].nIntPerXing = averageIntPerXing;

			m_l[1].elTrigger = isOkElTrigger;
			m_l[1].muTrigger = isOkMuTrigger;

			/**/

			m_l[1].weight1[i] = eventGetWeight1();
			m_l[1].weight2[i] = eventGetWeight2();
			m_l[1].weight3[i] = eventGetWeight3(index, TYPE_ELECTRON);

			m_l[1].l_tight[i] = el_tight->at(index) != 0;

			m_l[1].l_charge[i] = el_charge->at(index);
			m_l[1].l_e[i] = el_cl_E->at(index);
			m_l[1].l_pt[i] = electronGetEt(index);
			m_l[1].l_eta[i] = electronGetEtaDirection(index);
			m_l[1].l_phi[i] = electronGetPhiDirection(index);

			m_l[1].l_clIso20[i] = CaloIsoCorrection::GetNPVCorrectedIsolation(nPV2, el_etas2->at(index), 20, __isMC, el_Etcone20->at(index), CaloIsoCorrection::ELECTRON) / electronGetEt(index);
			m_l[1].l_tkIso20[i] = el_ptcone20->at(index) / electronGetEt(index);
			m_l[1].l_d0sigma[i] = fabs(el_trackd0pvunbiased->at(index) / el_tracksigd0pvunbiased->at(index));

			for(Int_t j = i + 1; j < elMuidIndexNr; j++)
			{
				Int_t index2 = elMuidIndexArray[j];

				if(sqrtf(__dR2(m_l[1].l_eta[i], electronGetEtaDirection(index2), m_l[1].l_phi[i], electronGetPhiDirection(index2))) < 0.20f)
				{
					m_l[1].l_tkIso20[i] -= el_trackpt->at(index2) / m_l[1].l_pt[i];
				}

				if(sqrtf(__dR2(m_l[1].l_eta[i], electronGetEtaDirection(index2), m_l[1].l_phi[i], electronGetPhiDirection(index2))) < 0.18f)
				{
					m_l[1].l_clIso20[i] -= electronGetEt(index2) / m_l[1].l_pt[i];
				}
			}

			if(m_l[1].l_pt[i] > 7000.0) {
				nrElMuid++;
			}
		}

		/*---------------------------------------------------------*/
		/* Loop Muon (STACO)					   */
		/*---------------------------------------------------------*/

		Int_t nrMuStaco = 0;

		m_l[2].n = muStacoIndexNr;

		for(Int_t i = 0; i < muStacoIndexNr; i++)
		{
			Int_t index = muStacoIndexArray[i];

			/**/

			m_l[2].RunNumber = RunNumber;
			m_l[2].EventNumber = EventNumber;
			m_l[2].LumiBlock = lbn;

			m_l[2].nPV2 = nPV2;
			m_l[2].nIntPerXing = averageIntPerXing;

			m_l[2].elTrigger = isOkElTrigger;
			m_l[2].muTrigger = isOkMuTrigger;

			/**/

			m_l[2].weight1[i] = eventGetWeight1();
			m_l[2].weight2[i] = eventGetWeight2();
			m_l[2].weight3[i] = eventGetWeight3(index, TYPE_MUON_STACO);

			m_l[2].l_tight[i] = mu_staco_tight->at(index) != 0;

			m_l[2].l_charge[i] = mu_staco_charge->at(index);
			m_l[2].l_e[i] = mu_staco_E->at(index);
			m_l[2].l_pt[i] = mu_staco_pt->at(index);
			m_l[2].l_eta[i] = mu_staco_eta->at(index);
			m_l[2].l_phi[i] = mu_staco_phi->at(index);

			m_l[2].l_clIso20[i] = (mu_staco_etcone20->at(index) - Float_t(nPV2 - 1) * 33.5f) / mu_staco_pt->at(index);
			m_l[2].l_tkIso20[i] = mu_staco_ptcone20->at(index) / mu_staco_pt->at(index);
			m_l[2].l_d0sigma[i] = fabs(mu_staco_trackIPEstimate_d0_unbiasedpvunbiased->at(index) / mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index));

			for(Int_t j = i + 1; j < muStacoIndexNr; j++)
			{
				Int_t index2 = muStacoIndexArray[j];

				if(sqrtf(__dR2(m_l[2].l_eta[i], mu_staco_eta->at(index2), m_l[2].l_phi[i], mu_staco_phi->at(index2))) < 0.20f)
				{
					m_l[2].l_tkIso20[i] -= ((mu_staco_id_qoverp_exPV->at(index2) != 0.0f) ? sinf(mu_staco_id_theta_exPV->at(index2)) / fabs(mu_staco_id_qoverp_exPV->at(index2)) : 0.0f) / m_l[2].l_pt[i];
				}
			}

			if(m_l[2].l_pt[i] > 7000.0) {
				nrMuStaco++;
			}
		}

		/*---------------------------------------------------------*/
		/* Loop Muon (MUID)				  	   */
		/*---------------------------------------------------------*/

		Int_t nrMuMuid = 0;

		m_l[3].n = muMuidIndexNr;

		for(Int_t i = 0; i < muMuidIndexNr; i++)
		{
			Int_t index = muMuidIndexArray[i];

			/**/

			m_l[3].RunNumber = RunNumber;
			m_l[3].EventNumber = EventNumber;
			m_l[3].LumiBlock = lbn;

			m_l[3].nPV2 = nPV2;
			m_l[3].nIntPerXing = averageIntPerXing;

			m_l[3].elTrigger = isOkElTrigger;
			m_l[3].muTrigger = isOkMuTrigger;

			/**/

			m_l[3].weight1[i] = eventGetWeight1();
			m_l[3].weight2[i] = eventGetWeight2();
			m_l[3].weight3[i] = eventGetWeight3(index, TYPE_MUON_MUID);

			m_l[3].l_tight[i] = mu_muid_tight->at(index) != 0;

			m_l[3].l_charge[i] = mu_muid_charge->at(index);
			m_l[3].l_e[i] = mu_muid_E->at(index);
			m_l[3].l_pt[i] = mu_muid_pt->at(index);
			m_l[3].l_eta[i] = mu_muid_eta->at(index);
			m_l[3].l_phi[i] = mu_muid_phi->at(index);

			m_l[3].l_clIso20[i] = (mu_muid_etcone20->at(index) - Float_t(nPV2 - 1) * 33.5f) / mu_muid_pt->at(index);
			m_l[3].l_tkIso20[i] = mu_muid_ptcone20->at(index) / mu_muid_pt->at(index);
			m_l[3].l_d0sigma[i] = fabs(mu_muid_trackIPEstimate_d0_unbiasedpvunbiased->at(index) / mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index));

			for(Int_t j = i + 1; j < muMuidIndexNr; j++)
			{
				Int_t index2 = muMuidIndexArray[j];

				if(sqrtf(__dR2(m_l[3].l_eta[i], mu_muid_eta->at(index2), m_l[3].l_phi[i], mu_muid_phi->at(index2))) < 0.20f)
				{
					m_l[3].l_tkIso20[i] -= ((mu_muid_id_qoverp_exPV->at(index2) != 0.0f) ? sinf(mu_muid_id_theta_exPV->at(index2)) / fabs(mu_muid_id_qoverp_exPV->at(index2)) : 0.0f) / m_l[3].l_pt[i];
				}
			}

			if(m_l[3].l_pt[i] > 7000.0) {
				nrMuMuid++;
			}
		}

		/*---------------------------------------------------------*/

		if(nrElStaco >= 2 && nrMuStaco >= 2) {
			m_tree1.Fill();
			m_tree3.Fill();
		}
		if(nrElMuid >= 2 && nrMuMuid >= 2) {
			m_tree2.Fill();
			m_tree4.Fill();
		}

		/*---------------------------------------------------------*/
	}
}

/*-------------------------------------------------------------------------*/

