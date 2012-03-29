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
}

/*-------------------------------------------------------------------------*/

void THiggsBuilder::Loop(void)
{
	Int_t n;

	Int_t nPV2;
	Int_t nPV3;

	int elSTACONr0 = 0;
	int elSTACONr1 = 0;
	int elSTACONr2 = 0;
	int elSTACONr3 = 0;
	int elSTACONr4 = 0;
	int elSTACONr5 = 0;
	int elSTACONr6 = 0;
	int elSTACONr7 = 0;
	int elSTACONr8 = 0;
	int elSTACONr9 = 0;

	int muSTACONr0 = 0;
	int muSTACONr1 = 0;
	int muSTACONr2 = 0;
	int muSTACONr3 = 0;
	int muSTACONr4 = 0;
	int muSTACONr5 = 0;
	int muSTACONr6 = 0;
	int muSTACONr7 = 0;
	int muSTACONr8 = 0;
	int muSTACONr9 = 0;
	int muSTACONr10 = 0;
	int muSTACONr11 = 0;
	int muSTACONr12 = 0;

	int muCALONr0 = 0;
	int muCALONr1 = 0;
	int muCALONr2 = 0;
	int muCALONr3 = 0;
	int muCALONr4 = 0;
	int muCALONr5 = 0;
	int muCALONr6 = 0;
	int muCALONr7 = 0;
	int muCALONr8 = 0;
	int muCALONr9 = 0;
	int muCALONr10 = 0;
	int muCALONr11 = 0;

	int staco_n = 0;

	Float_t etaArray[1024];
	Float_t phiArray[1024];

	const Long64_t eventNr = fChain->GetEntries();

	for(Long64_t event = 0; event < eventNr; event++)
	{
		/*---------------------------------------------------------*/

		LoadEvent(event, eventNr);

		/*---------------------------------------------------------*/
		/* AT LEAST 3 PRIMARY TRACKS				   */
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
		/* TRIGGER						   */
		/*---------------------------------------------------------*/

		Bool_t isOkElTrigger = getElTrigger();
		Bool_t isOkMuTrigger = getMuTrigger();

		/*---------------------------------------------------------*/
		/* ELECTRON STACO					   */
		/*---------------------------------------------------------*/

		Bool_t isOk;

		for(Int_t index = 0; index < el_n; index++)
		{
			elSTACONr0++;

			if(isOkVertex == false) {
				continue;
			}

			elSTACONr1++;

			if(isOkElTrigger == false) {
				continue;
			}

			elSTACONr2++;

			if(el_author->at(index) != 1
			   &&
			   el_author->at(index) != 3
			 ) {
				continue;
			}

			elSTACONr3++;

			if(el_loosePP_at(index) == 0) {
				continue;
			}

			elSTACONr4++;

			if(fabs(el_cl_eta->at(index)) > 2.47f) {
				continue;
			}

			elSTACONr5++;

			if(electronGetEt(index) < 7000.0f) {
				continue;
			}

			elSTACONr6++;

			if((el_OQ->at(index) & 1446) != 0) {
				continue;
			}

			elSTACONr7++;

			if(fabs(el_trackz0pvunbiased->at(index)) > 10.0f) {
				continue;
			}

			elSTACONr8++;

			isOk = true;

			for(Int_t xedni = 0; xedni < el_n; xedni++)
			{
				if(index != xedni
				   &&
				   el_trackd0->at(index) == el_trackd0->at(xedni)
				   &&
				   el_trackz0->at(index) == el_trackz0->at(xedni)
				   &&
				   el_tracktheta->at(index) == el_tracktheta->at(xedni)
				   &&
				   el_trackphi->at(index) == el_trackphi->at(xedni)
				   &&
				   el_trackqoverp->at(index) == el_trackqoverp->at(xedni)
				 ) {
					if(checkObject(xedni, TYPE_ELECTRON, 7000.0, 7000.0, 0.0f, true, false) != false && electronGetEt(index) <= electronGetEt(xedni))
					{
						isOk = false;

						break;
					}
				}
			}

			if(isOk == false) {
				continue;
			}

			elSTACONr9++;
		}

		/*---------------------------------------------------------*/
		/* MUON STACO						   */
		/*---------------------------------------------------------*/

		staco_n = 0;

		for(Int_t index = 0; index < mu_staco_n; index++)
		{
			muSTACONr0++;

			if(isOkVertex == false) {
				continue;
			}

			muSTACONr1++;

			if(isOkMuTrigger == false) {
				continue;
			}

			muSTACONr2++;

			if(mu_staco_author->at(index) != 6
			   &&
			   mu_staco_author->at(index) != 7
			 ) {
				continue;
			}

			muSTACONr3++;

			if(mu_staco_pt->at(index) < 7000.0f) {
				continue;
			}

			muSTACONr4++;

//			if(fabs(mu_staco_eta->at(index)) > 2.7f) {
//				continue;
//			}

			muSTACONr5++;

			if(mu_staco_expectBLayerHit->at(index) != 0 && mu_staco_nBLHits->at(index) <= 0) {
				continue;
			}

			muSTACONr6++;

			if(mu_staco_nPixHits->at(index) + mu_staco_nPixelDeadSensors->at(index) < 2) {
				continue;
			}

			muSTACONr7++;

			if(mu_staco_nSCTHits->at(index) + mu_staco_nSCTDeadSensors->at(index) < 6) {
				continue;
			}

			muSTACONr8++;

			if(mu_staco_nPixHoles->at(index) + mu_staco_nSCTHoles->at(index) > 2) {
				continue;
			}

			muSTACONr9++;

			n = mu_staco_nTRTHits->at(index) + mu_staco_nTRTOutliers->at(index);

			if(fabs(mu_staco_eta->at(index)) < 1.9f)
			{
				if(n < 6 || mu_staco_nTRTOutliers->at(index) > 0.9f * n) {
					continue;
				}
			}
			else
			{
				if(n > 5 && mu_staco_nTRTOutliers->at(index) > 0.9f * n) {
					continue;
				}
			}

			muSTACONr10++;

			if(fabs(mu_staco_d0_exPV->at(index)) > 1.0f) {
				continue;
			}

			muSTACONr11++;

			if(fabs(mu_staco_z0_exPV->at(index)) > 10.0f) {
				continue;
			}

			muSTACONr12++;

			etaArray[staco_n] = -logf(tanf(0.5f * mu_staco_id_theta->at(index)));
			phiArray[staco_n] = mu_staco_id_phi->at(index);
			staco_n++;
		}

		/*---------------------------------------------------------*/
		/* MUON CALO						   */
		/*---------------------------------------------------------*/

		for(Int_t index = 0; index < mu_calo_n; index++)
		{
			for(Int_t xedni = 0; xedni < staco_n; xedni++)
			{
				if(sqrtf(__dR2(-logf(tanf(0.5f * mu_calo_id_theta->at(index))), etaArray[xedni], mu_calo_id_phi->at(index), phiArray[xedni])) < 0.1f)
				{
					goto __continue;
				}
			}

			/**/

			muCALONr0++;

			if(isOkVertex == false) {
				continue;
			}

			muCALONr1++;

			if(isOkMuTrigger == false) {
				continue;
			}

			muCALONr2++;

			if(mu_calo_author->at(index) != 16) {
				continue;
			}

			if(mu_calo_caloMuonIdTag->at(index) < 11
			   &&
			   mu_calo_caloLRLikelihood->at(index) < 0.9f
			 ) {
				continue;
			}

			muCALONr3++;

			if(fabs(mu_calo_eta->at(index)) > 0.1f) {
				continue;
			}

			muCALONr4++;

			if(mu_calo_pt->at(index) < 15000.0) {
				continue;
			}

			muCALONr5++;

			if(mu_calo_expectBLayerHit->at(index) != 0 && mu_calo_nBLHits->at(index) <= 0) {
				continue;
			}

			muCALONr6++;

			if(mu_calo_nPixHits->at(index) + mu_calo_nPixelDeadSensors->at(index) < 2) {
				continue;
			}

			muCALONr7++;

			if(mu_calo_nSCTHits->at(index) + mu_calo_nSCTDeadSensors->at(index) < 6) {
				continue;
			}

			muCALONr8++;

			if(mu_calo_nPixHoles->at(index) + mu_calo_nSCTHoles->at(index) > 2) {
				continue;
			}

			muCALONr9++;

			n = mu_calo_nTRTHits->at(index) + mu_calo_nTRTOutliers->at(index);

			if(n > 5 && mu_calo_nTRTOutliers->at(index) > n * 0.9) {
				continue;
			}

			muCALONr10++;

			if(fabs(mu_calo_z0_exPV->at(index)) > 10.0f) {
				continue;
			}

			muCALONr11++;
__continue:if(0){}
		}

		/*---------------------------------------------------------*/
	}

	std::cout << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# ELECTRON STACO                                                            #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut    : " << elSTACONr0 << std::endl;
	std::cout << "after vertex      : " << elSTACONr1 << std::endl;
	std::cout << "after trigger     : " << elSTACONr2 << std::endl;
	std::cout << "after author=1||3 : " << elSTACONr3 << std::endl;
	std::cout << "after loose++     : " << elSTACONr4 << std::endl;
	std::cout << "after |η|<2.47    : " << elSTACONr5 << std::endl;
	std::cout << "after pt>7        : " << elSTACONr6 << std::endl;
	std::cout << "after OQ          : " << elSTACONr7 << std::endl;
	std::cout << "after z0          : " << elSTACONr8 << std::endl;
	std::cout << "e-e overlap       : " << elSTACONr9 << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# MUON STACO                                                                #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut     : " << muSTACONr0 << std::endl;
	std::cout << "after vertex       : " << muSTACONr1 << std::endl;
	std::cout << "after trigger      : " << muSTACONr2 << std::endl;
	std::cout << "after author=6||7  : " << muSTACONr3 << std::endl;
	std::cout << "after pt>4.7       : " << muSTACONr4 << std::endl;
	std::cout << "after |η|<2.5      : " << muSTACONr5 << std::endl;
	std::cout << "after b-Layer      : " << muSTACONr6 << std::endl;
	std::cout << "after Pix          : " << muSTACONr7 << std::endl;
	std::cout << "after SCT          : " << muSTACONr8 << std::endl;
	std::cout << "after holes        : " << muSTACONr9 << std::endl;
	std::cout << "after TRT/outliers : " << muSTACONr10 << std::endl;
	std::cout << "after d0           : " << muSTACONr11 << std::endl;
	std::cout << "after z0           : " << muSTACONr12 << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# MUON CALO                                                                 #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut      : " << muCALONr0 << std::endl;
	std::cout << "after vertex        : " << muCALONr1 << std::endl;
	std::cout << "after trigger       : " << muCALONr2 << std::endl;
	std::cout << "after author=16 ... : " << muCALONr3 << std::endl;
	std::cout << "after |η|<0.1       : " << muCALONr4 << std::endl;
	std::cout << "after pt>15         : " << muCALONr5 << std::endl;
	std::cout << "after b-Layer       : " << muCALONr6 << std::endl;
	std::cout << "after Pix           : " << muCALONr7 << std::endl;
	std::cout << "after SCT           : " << muCALONr8 << std::endl;
	std::cout << "after holes         : " << muCALONr9 << std::endl;
	std::cout << "after TRT/outliers  : " << muCALONr10 << std::endl;
	std::cout << "after z0            : " << muCALONr11 << std::endl;

	std::cout << "#############################################################################" << std::endl;
}

/*-------------------------------------------------------------------------*/

