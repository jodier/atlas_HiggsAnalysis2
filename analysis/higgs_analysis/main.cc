/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstring>
#include <iostream>

#include "main.h"

/*-------------------------------------------------------------------------*/

void core::execute(TChain *chain)
{
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << "/* EXECUTE                                                                 */" << std::endl;
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;

	THiggsBuilder algo(chain);
	algo.Loop();

	/**/

	TFile file(core::output.c_str(), "recreate");

	file.cd();

	algo.m_tree0.Write();
	algo.m_tree1.Write();
	algo.m_tree2.Write();
	algo.m_tree3.Write();
	algo.m_tree4.Write();
	algo.m_tree5.Write();
	algo.m_tree6.Write();

	file.Close();
}

/*-------------------------------------------------------------------------*/

extern Float_t getMassCut(Float_t H_mass);

/*-------------------------------------------------------------------------*/

void THiggsBuilder::selectQuadruplet(Int_t dest, Float_t Z_MASS)
{
	Float_t currDMass;
	Float_t currAMass;

	Float_t goodDMass = 999999.0f;
	Float_t goodAMass = 000000.0f;

	/*-------------------------------------------------*/
	/* PASS 1					   */
	/*-------------------------------------------------*/

	for(Int_t i = 0; i < m_H[dest].n; i++) if((m_H[dest].flag[i] & 127) == 127)
	{
		currDMass = fabs(Z_MASS - m_H[dest].Z12_m[i]);

		if(goodDMass > currDMass)
		{
			goodDMass = currDMass;
		}	
	}

	/*-------------------------------------------------*/
	/* PASS 2					   */
	/*-------------------------------------------------*/

	for(Int_t i = 0; i < m_H[dest].n; i++) if((m_H[dest].flag[i] & 127) == 127)
	{
		currDMass = fabs(Z_MASS - m_H[dest].Z12_m[i]);

		if(goodDMass == currDMass)
		{
			currAMass = fabs(0.000f - m_H[dest].Z34_m[i]);

			if(goodAMass < currAMass)
			{
				goodAMass = currAMass;
			}
		}
	}

	/*-------------------------------------------------*/
	/* PASS 3					   */
	/*-------------------------------------------------*/

	for(Int_t i = 0; i < m_H[dest].n; i++) if((m_H[dest].flag[i] & 127) == 127)
	{
		currDMass = fabs(Z_MASS - m_H[dest].Z12_m[i]);
		currAMass = fabs(0.000f - m_H[dest].Z34_m[i]);

		if(currDMass == goodDMass
		   &&
		   currAMass == goodAMass
		 ) {
			m_H[dest].good[i] = true;

/*			if(dest == ???)
			{
				std::cout << "Event number    : " << m_H[dest].EventNumber << std::endl;

				std::cout << "  M_4l          = " << m_H[dest].H_m[i] << std::endl;

				std::cout << "  M_Z1          = " << m_H[dest].Z12_m[i] << std::endl;
				std::cout << "  M_Z1-M_Z      = " << fabs(Z_MASS - m_H[dest].Z12_m[i]) << std::endl;

				std::cout << "  M_Z2          = " << m_H[dest].Z34_m[i] << std::endl;
				std::cout << "  M_Z2-M_Z      = " << fabs(Z_MASS - m_H[dest].Z34_m[i]) << std::endl;

				std::cout << "  CutM_34       = " << getMassCut(m_H[dest].H_m[i]) << std::endl;
				std::cout << "  Pass cut M_Z2 = " << (m_H[dest].flag[i] >= 0x3F) << std::endl;

				std::cout << "  pT_l1 = " << m_H[dest].l1_pt[i]
					  << ", pT_l2 = " << m_H[dest].l2_pt[i]
					  << ", pT_l3 = " << m_H[dest].l3_pt[i]
					  << ", pT_l4 = " << m_H[dest].l4_pt[i]
					  << std::endl;
			}
*/		}
	}

	/*-------------------------------------------------*/
	/* PASS 4					   */
	/*-------------------------------------------------*/

	Bool_t eeuu;

	for(Int_t i = 0; i < m_H[dest].n; i++)
	{
		if((m_H[dest].flag[i] &   1) ==   1) m_H[dest].cnt[0] = true;
		if((m_H[dest].flag[i] &   3) ==   3) m_H[dest].cnt[1] = true;
		if((m_H[dest].flag[i] &   7) ==   7) m_H[dest].cnt[2] = true;
		if((m_H[dest].flag[i] &  15) ==  15) m_H[dest].cnt[3] = true;
		if((m_H[dest].flag[i] &  31) ==  31) m_H[dest].cnt[4] = true;
		if((m_H[dest].flag[i] &  63) ==  63) m_H[dest].cnt[5] = true;
		if((m_H[dest].flag[i] & 127) == 127) m_H[dest].cnt[6] = true;
		if((m_H[dest].flag[i] & 255) == 255) m_H[dest].cnt[7] = true;

		if(m_H[dest].good[i] != false)
		{
			eeuu = m_H[dest].eeuu[i] != 0;

			if((m_H[dest].flag[i] &  511) ==  511) m_H[dest].cnt[eeuu ?  8 :  9] = true;
			if((m_H[dest].flag[i] & 1023) == 1023) m_H[dest].cnt[eeuu ? 10 : 11] = true;
			if((m_H[dest].flag[i] & 2047) == 2047) m_H[dest].cnt[eeuu ? 12 : 13] = true;
		}
	}
}

/*-------------------------------------------------------------------------*/

void THiggsBuilder::Loop(void)
{
	Int_t elStacoNr1 = 0;
	Int_t muStacoNr1 = 0;
	Int_t muCaloNr1 = 0;

	Int_t elStacoNr2 = 0;
	Int_t muStacoNr2 = 0;
	Int_t muCaloNr2 = 0;

	Int_t elStacoIndexNr1;
	Int_t muStacoIndexNr1;
	Int_t muCaloIndexNr1;
	Int_t elStacoIndexArray1[1024];
	Int_t muStacoIndexArray1[1024];
	TLeptonType elStacoTypeArray1[1024];
	TLeptonType muStacoTypeArray1[1024];

	Int_t elStacoIndexNr2;
	Int_t muStacoIndexNr2;
	Int_t muCaloIndexNr2;
	Int_t elStacoIndexArray2[1024];
	Int_t muStacoIndexArray2[1024];
	TLeptonType elStacoTypeArray2[1024];
	TLeptonType muStacoTypeArray2[1024];

	Float_t Z_MASS = core::configFltLookup("Z_MASS");

	Float_t higgs_el_et = core::configFltLookup("higgs_el_et");
	Float_t higgs_mu_staco_pt = core::configFltLookup("higgs_mu_staco_pt");
	Float_t higgs_mu_calo_pt = core::configFltLookup("higgs_mu_calo_pt");

	const Long64_t eventNr = fChain->GetEntries();

	for(Long64_t event = 0; event < eventNr; event++)
	{
		/*---------------------------------------------------------*/

		LoadEvent(event, eventNr);

		if(event == 0)
		{
			triggerInit();
		}

		fixeEnergy();

		/*---------------------------------------------------------*/
		/* INIT							   */
		/*---------------------------------------------------------*/

		elStacoIndexNr1 = 0;
		muStacoIndexNr1 = 0;
		muCaloIndexNr1 = 0;

		elStacoIndexNr2 = 0;
		muStacoIndexNr2 = 0;
		muCaloIndexNr2 = 0;

		Int_t tmpNr;

		memset(&m_evt, 0x00, sizeof(m_evt));
		memset(  m_Z , 0x00, sizeof( m_Z ));
		memset(  m_H , 0x00, sizeof( m_H ));

		/**/

		m_evt.RunNumber = -1;
		m_evt.EventNumber = -1;
		m_evt.LumiBlock = -1;

		m_evt.nPV2 = -1;
		m_evt.nIntPerXing = -1.0f;

		m_evt.elTrigger = -1;
		m_evt.muTrigger = -1;

		for(Int_t i = 0; i < 2; i++)
		{
			m_Z[i].RunNumber = -1;
			m_Z[i].EventNumber = -1;
			m_Z[i].LumiBlock = -1;

			m_Z[i].nPV2 = -1;
			m_Z[i].nIntPerXing = -1.0f;

			m_Z[i].elTrigger = -1;
			m_Z[i].muTrigger = -1;
		}

		for(Int_t i = 0; i < 3; i++)
		{
			m_H[i].RunNumber = -1;
			m_H[i].EventNumber = -1;
			m_H[i].LumiBlock = -1;

			m_H[i].nPV2 = -1;
			m_H[i].nIntPerXing = -1.0f;

			m_H[i].elTrigger = -1;
			m_H[i].muTrigger = -1;
		}

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

		Bool_t isOkElTrigger = getElTrigger();
		Bool_t isOkMuTrigger = getMuTrigger();

		Bool_t useLoose = core::configFltLookup("EL_USE_LOOSE") != 0.0f;
		Bool_t useForward = core::configFltLookup("EL_USE_FORWARD") != 0.0f;

		/*---------------------------------------------------------*/
		/* µ SELECTION						   */
		/*---------------------------------------------------------*/

		Bool_t isOk;

		Float_t calo_eta;
		Float_t calo_phi;
		Float_t xxxx_eta;
		Float_t xxxx_phi;

		/*---------------------------------------------------------*/

		if(isOkMuTrigger != false && isOkVertex != false)
		{
			for(Int_t i = 0; i < mu_staco_n; i++)
			{
				if(checkObject(i, TYPE_MUON_STACO, higgs_el_et, higgs_mu_staco_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muStacoIndexArray1[muStacoIndexNr1] = i;
					muStacoTypeArray1[muStacoIndexNr1] = TYPE_MUON_STACO;

					muStacoNr1++;
					muStacoIndexNr1++;
				}
			}

			tmpNr = muStacoIndexNr1;

			for(Int_t i = 0; i < mu_calo_n; i++)
			{
				if(checkObject(i, TYPE_MUON_CALO, higgs_el_et, higgs_mu_staco_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					calo_eta = -logf(tanf(0.5f * mu_calo_id_theta->at(i)));
					calo_phi = mu_calo_id_phi->at(i);

					isOk = true;

					for(Int_t j = 0; j < tmpNr; j++)
					{
						xxxx_eta = -logf(tanf(0.5f * mu_staco_id_theta->at( muStacoIndexArray1[j] )));
						xxxx_phi = mu_staco_id_phi->at( muStacoIndexArray1[j] );

						if(sqrtf(__dR2(calo_eta, xxxx_eta, calo_phi, xxxx_phi)) < 0.1f)
						{
							isOk = false;

							break;
						}
					}

					if(isOk != false)
					{
						muStacoIndexArray1[muStacoIndexNr1] = i;
						muStacoTypeArray1[muStacoIndexNr1] = TYPE_MUON_CALO;

						muStacoIndexNr1++;
					}

					muCaloNr1++;
				}
			}
		}

		/*---------------------------------------------------------*/

		if((isOkElTrigger != false || isOkMuTrigger != false) && isOkVertex != false)
		{
			for(Int_t i = 0; i < mu_staco_n; i++)
			{
				if(checkObject(i, TYPE_MUON_STACO, higgs_el_et, higgs_mu_staco_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muStacoIndexArray2[muStacoIndexNr2] = i;
					muStacoTypeArray2[muStacoIndexNr2] = TYPE_MUON_STACO;

					muStacoNr2++;
					muStacoIndexNr2++;
				}
			}

			tmpNr = muStacoIndexNr2;

			for(Int_t i = 0; i < mu_calo_n; i++)
			{
				if(checkObject(i, TYPE_MUON_CALO, higgs_el_et, higgs_mu_staco_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					calo_eta = -logf(tanf(0.5f * mu_calo_id_theta->at(i)));
					calo_phi = mu_calo_id_phi->at(i);

					isOk = true;

					for(Int_t j = 0; j < tmpNr; j++)
					{
						xxxx_eta = -logf(tanf(0.5f * mu_staco_id_theta->at( muStacoIndexArray2[j] )));
						xxxx_phi = mu_staco_id_phi->at( muStacoIndexArray2[j] );

						if(sqrtf(__dR2(calo_eta, xxxx_eta, calo_phi, xxxx_phi)) < 0.1f)
						{
							isOk = false;

							break;
						}
					}

					if(isOk != false)
					{
						muStacoIndexArray2[muStacoIndexNr2] = i;
						muStacoTypeArray2[muStacoIndexNr2] = TYPE_MUON_CALO;

						muStacoIndexNr2++;
					}

					muCaloNr2++;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* e SELECTION						   */
		/*---------------------------------------------------------*/

		if(isOkElTrigger != false && isOkVertex != false)
		{
			for(Int_t i = 0; i < el_n; i++)
			{
				if(checkObject(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_staco_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					if(checkOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_staco_pt, higgs_mu_calo_pt, useLoose, useForward, muStacoIndexNr1, muStacoIndexArray1, muStacoTypeArray1) != false)
					{
						elStacoIndexArray1[elStacoIndexNr1] = i;
						elStacoTypeArray1[elStacoIndexNr1] = TYPE_ELECTRON;

						elStacoNr1++;
						elStacoIndexNr1++;
					}
				}
			}
		}

		/*---------------------------------------------------------*/

		if((isOkElTrigger != false || isOkMuTrigger != false) && isOkVertex != false)
		{
			for(Int_t i = 0; i < el_n; i++)
			{
				if(checkObject(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_staco_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					if(checkOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_staco_pt, higgs_mu_calo_pt, useLoose, useForward, muStacoIndexNr2, muStacoIndexArray2, muStacoTypeArray2) != false)
					{
						elStacoIndexArray2[elStacoIndexNr2] = i;
						elStacoTypeArray2[elStacoIndexNr2] = TYPE_ELECTRON;

						elStacoNr2++;
						elStacoIndexNr2++;
					}
				}
			}
		}

		/*---------------------------------------------------------*/
		/* TRUTH						   */
		/*---------------------------------------------------------*/
#ifdef __IS_MC
		Int_t cnt_e = 0;
		Int_t cnt_u = 0;

		for(Int_t i = 0; i < mc_n; i++)
		{
			if(mc_pdgId->at(i) == 25)
			{
				for(Int_t j = 0; j < (Int_t) (mc_children->at(i).size() + mc_child_index->at(i).size()) / 2; j++)
				{
					Int_t m = mc_children->at(i).at(j);
					Int_t n = mc_child_index->at(i).at(j);

					if(mc_pdgId->at(n) == 23)
					{
						Int_t pdg = mc_pdgId->at(m);

						switch(pdg < 0 ? -pdg : +pdg)
						{
							case 11:
								cnt_e++;
								break;

							case 13:
								cnt_u++;
								break;
						}
					}
				}
			}
		}

		/**/ if(cnt_e == 4 && cnt_u == 0) {
			m_truth.eeee_nr++;
		}
		else if(cnt_e == 0 && cnt_u == 4) {
			m_truth.uuuu_nr++;
		}
		else if(cnt_e == 2 && cnt_u == 2) {
			m_truth.eeuu_nr++;
		}
#endif
		/*---------------------------------------------------------*/
		/* EVENTS						   */
		/*---------------------------------------------------------*/

		m_evt.RunNumber   =  RunNumber ;
		m_evt.EventNumber = EventNumber;
		m_evt.LumiBlock   =     lbn    ;

		m_evt.nPV2 = nPV2;
		m_evt.nIntPerXing = averageIntPerXing;

		m_evt.elTrigger = isOkElTrigger;
		m_evt.muTrigger = isOkMuTrigger;

		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/

		Int_t mu_n = mu_staco_n;

		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/

		m_evt.el_raw_n = el_n;
		m_evt.mu_raw_n = mu_n;

		if((isOkElTrigger != false || isOkMuTrigger != false) && isOkVertex != false)
		{
			m_evt.el_1st_n = el_n;
			m_evt.mu_1st_n = mu_n;

			m_evt.el_2nd_n = elStacoIndexNr2;
			m_evt.mu_2nd_n = muStacoIndexNr2;
		}

		m_evt.lepton_raw_n = m_evt.el_raw_n + m_evt.mu_raw_n;
		m_evt.lepton_1st_n = m_evt.el_1st_n + m_evt.mu_1st_n;
		m_evt.lepton_2nd_n = m_evt.el_2nd_n + m_evt.mu_2nd_n;

		/*---------------------------------------------------------*/
		/* Z->ee, H->ZZ->eeee					   */
		/*---------------------------------------------------------*/

		Bool_t result_Z1 = false;
		Bool_t result_H1 = false;

		if(elStacoIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < elStacoIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < elStacoIndexNr1; j++)
				{
					if(Z_analysis(
						elStacoIndexArray1[i],
						elStacoIndexArray1[j],
						elStacoTypeArray1[i],
						elStacoTypeArray1[j], 0
					 ) != false) {
						result_Z1 = true;
					}

					for(Int_t k = j + 1; k < elStacoIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < elStacoIndexNr1; l++)
						{
							if(H_analysis(
								elStacoIndexArray1[i],
								elStacoIndexArray1[j],
								elStacoIndexArray1[k],
								elStacoIndexArray1[l],
								elStacoTypeArray1[i],
								elStacoTypeArray1[j],
								elStacoTypeArray1[k],
								elStacoTypeArray1[l], 0
							 ) != false) {
								result_H1 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(0, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* Z->µµ, H->ZZ->µµµµ					   */
		/*---------------------------------------------------------*/

		Bool_t result_Z2 = false;
		Bool_t result_H2 = false;

		if(muStacoIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < muStacoIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < muStacoIndexNr1; j++)
				{
					if(Z_analysis(
						muStacoIndexArray1[i],
						muStacoIndexArray1[j],
						muStacoTypeArray1[i],
						muStacoTypeArray1[j], 1
					 ) != false) {
						result_Z2 = true;
					}

					for(Int_t k = j + 1; k < muStacoIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < muStacoIndexNr1; l++)
						{
							if(H_analysis(
								muStacoIndexArray1[i],
								muStacoIndexArray1[j],
								muStacoIndexArray1[k],
								muStacoIndexArray1[l],
								muStacoTypeArray1[i],
								muStacoTypeArray1[j],
								muStacoTypeArray1[k],
								muStacoTypeArray1[l], 1
							 ) != false) {
								result_H2 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(1, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* H->ZZ->eeµµ						   */
		/*---------------------------------------------------------*/

		Bool_t result_H3 = false;

		if(elStacoIndexNr2 >= 2 && muStacoIndexNr2 >= 2)
		{
			for(Int_t i = 0 + 0; i < elStacoIndexNr2; i++)
			{
				for(Int_t j = i + 1; j < elStacoIndexNr2; j++)
				{
					for(Int_t k = 0 + 0; k < muStacoIndexNr2; k++)
					{
						for(Int_t l = k + 1; l < muStacoIndexNr2; l++)
						{
							if(H_analysis(
								elStacoIndexArray2[i],
								elStacoIndexArray2[j],
								muStacoIndexArray2[k],
								muStacoIndexArray2[l],
								elStacoTypeArray2[i],
								elStacoTypeArray2[j],
								muStacoTypeArray2[k],
								muStacoTypeArray2[l], 2
							 ) != false) {
								result_H3 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(2, Z_MASS);
		}

		/*---------------------------------------------------------*/

		m_tree1.Fill();

		if(result_Z1 != false) {	/* Z->ee */
			m_tree2.Fill();
		}
		if(result_Z2 != false) {	/* Z->µµ */
			m_tree3.Fill();
		}

		if(result_H1 != false) {	/* H->ZZ->eeee */
			m_tree4.Fill();
		}
		if(result_H2 != false) {	/* H->ZZ->µµµµ */
			m_tree5.Fill();
		}
		if(result_H3 != false) {	/* H->ZZ->eeµµ */
			m_tree6.Fill();
		}

		/*---------------------------------------------------------*/
	}

	m_tree0.Fill();

	std::cout << "Done:" << std::endl;

	std::cout << std::endl;
	std::cout << "H->eeee, H->µµµµµ" << std::endl;
	std::cout << "electons: " << elStacoNr1 << std::endl;
	std::cout << "muons: " << muStacoNr1 << std::endl;
	std::cout << "muons (calo): " << muCaloNr1 << std::endl;

	std::cout << std::endl;
	std::cout << "H->eeµµ, H->µµµee" << std::endl;
	std::cout << "electons: " << elStacoNr2 << std::endl;
	std::cout << "muons: " << muStacoNr2 << std::endl;
	std::cout << "muons (calo): " << muCaloNr2 << std::endl;
}

/*-------------------------------------------------------------------------*/

