/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstdlib>

#include "utils.h"

/*-------------------------------------------------------------------------*/

void TLeptonAnalysis::fixeEnergy(void)
{
	if(core::ER != false)
	{
		for(Int_t i = 0; i < el_n; i++)
		{
#ifndef __IS_MC
			el_cl_E->at(i) = m_energyRescaler->applyEnergyCorrectionMeV(
				el_cl_eta->at(i),
				el_cl_phi->at(i),
				el_cl_E->at(i),
				electronGetEt(i),
				0,
				"ELECTRON"
			);
#endif
			el_cl_E->at(i) = el_cl_E->at(i) * m_energyRescaler->applyMCCalibrationMeV(
				el_cl_eta->at(i),
				electronGetEt(i),
				"ELECTRON"
			);
		}
	}
#ifdef __IS_MC
	if(core::SM != false)
	{
		float pT_ME;
		float pT_ID;
		float pT_old;
		float pT_new;

		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < el_n; i++)
		{
			m_energyRescaler->SetRandomSeed(EventNumber + 100 * i);

			el_cl_E->at(i) = el_cl_E->at(i) * m_energyRescaler->getSmearingCorrectionMeV(
				el_cl_eta->at(i),
				el_cl_E->at(i),
				0, true, "2011"
			);
		}

		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < mu_staco_n; i++)
		{
			pT_ME = (mu_staco_me_qoverp_exPV->at(i) != 0.0f) ? sin(mu_staco_me_theta_exPV->at(i)) / fabs(mu_staco_me_qoverp_exPV->at(i)) : 0.0f;
			pT_ID = (mu_staco_id_qoverp_exPV->at(i) != 0.0f) ? sin(mu_staco_id_theta_exPV->at(i)) / fabs(mu_staco_id_qoverp_exPV->at(i)) : 0.0f;

			pT_old = pT_new = mu_staco_pt->at(i);

			m_stacoSM->SetSeed(EventNumber, i);

			if(mu_staco_isCombinedMuon->at(i) != false)
			{
				m_stacoSM->Event(
					pT_ME,
					pT_ID,
					pT_old,
					mu_staco_eta->at(i)
				);

				pT_new = m_stacoSM->pTCB();
			}

			if(mu_staco_isSegmentTaggedMuon->at(i) != false)
			{
				m_stacoSM->Event(
					pT_old,
					mu_staco_eta->at(i),
					"ID"
				);

				pT_new = m_stacoSM->pTID();
			}

			mu_staco_E->at(i) = (pT_new / pT_old) * mu_staco_E->at(i);
			mu_staco_pt->at(i) = pT_new;
		}

		/*---------------------------------------------------------*/
	}
#endif
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::eventGetWeight1(void)
{
#ifdef __IS_MC
	Float_t weight = 1.0f;

	if(mcevt_weight[0].size() > 0)
	{
		if(mcevt_weight[0][0].size() == 1)
		{
			weight = mcevt_weight[0][0][0];
		}
	}

	if(weight == 0.0f)
	{
		weight = 1.0f;
	}

	return weight;
#else
	return 1.000f;
#endif
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::eventGetWeight2(void)
{
#ifdef __IS_MC
	return m_pileupReweighting->GetCombinedWeight(RunNumber, mc_channel_number, averageIntPerXing);
#else
	return 1.000f;
#endif
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::eventGetWeight3(Int_t index, TLeptonType type)
{
#ifdef __IS_MC
	Float_t et;
	Float_t eta;

	TLorentzVector tlv;

	Float_t weight;

	switch(type)
	{
		/*---------------------------------------------------------*/
		/* TYPE_ELECTRON					   */
		/*---------------------------------------------------------*/

		case TYPE_ELECTRON:
			et = electronGetEt(index);
			eta = el_cl_eta->at(index);

			weight = \
				m_egammaSF->scaleFactor(eta, et, 5, 0, 5, true).first
				*
				m_egammaSF->scaleFactor(eta, et, 4, 0, 5, true).first
			;
			break;

		/*---------------------------------------------------------*/
		/* MUON_STACO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_STACO:
			tlv.SetPtEtaPhiE(mu_staco_pt->at(index), mu_staco_eta->at(index), mu_staco_phi->at(index), mu_staco_E->at(index));

			weight = m_stacoSF->scaleFactor(tlv);
			break;

		/*---------------------------------------------------------*/
		/* MUON_CALO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_CALO:
			weight = 1.0f;
			break;

		/*---------------------------------------------------------*/

		default:
			std::cout << "TLeptonAnalysis::eventGetWeight3() - Oula !" << std::endl;
			weight = 0.0f;
			break;

		/*---------------------------------------------------------*/
	}

	return weight;
#else
	return 1.000f;
#endif
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetEtaDirection(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_tracketa->at(index) : el_cl_eta->at(index);
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetPhiDirection(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_trackphi->at(index) : el_cl_phi->at(index);
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetEt(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_cl_E->at(index) / coshf(el_tracketa->at(index)) : el_cl_pt->at(index);
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkObject(
	Int_t index,
	TLeptonType type,
	Float_t __el_et,
	Float_t __mu_staco_pt,
	Float_t __mu_calo_pt,
	Bool_t useLoose,
	Bool_t useForward
) {
	Int_t n;

	if(useForward != false)
	{
		std::cerr << "Forward electrons not implemented !" << std::endl;

		return false;
	}

	switch(type)
	{
		/*---------------------------------------------------------*/
		/* TYPE_ELECTRON					   */
		/*---------------------------------------------------------*/

		case TYPE_ELECTRON:
			if(el_author->at(index) != 1
			   &&
			   el_author->at(index) != 3
			 ) {
				goto __error;
			}

			if(useLoose == false)
			{
				if(el_medium->at(index) == 0) {
					goto __error;
				}
			}
			else
			{
#ifndef __CR
				if(el_loosePP_at(index) == 0) {
#else
				if(el_loosePP_cr_at(index) == 0) {
#endif
					goto __error;
				}
			}

			if(fabs(el_cl_eta->at(index)) > 2.47f) {
				goto __error;
			}

			if(electronGetEt(index) < __el_et) {
				goto __error;
			}

			if((el_OQ->at(index) & 1446) != 0) {
				goto __error;
			}

			if(fabs(el_trackz0pvunbiased->at(index)) > 10.0f) {
				goto __error;
			}

			break;

		/*---------------------------------------------------------*/
		/* MUON_STACO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_STACO:
			if(mu_staco_author->at(index) != 6
			   &&
			   mu_staco_author->at(index) != 7
			 ) {
				goto __error;
			}

			if(mu_staco_pt->at(index) < __mu_staco_pt && fabs(mu_staco_eta->at(index)) < 2.7f) {
				goto __error;
			}

			if(mu_staco_expectBLayerHit->at(index) != 0 && mu_staco_nBLHits->at(index) <= 0) {
				goto __error;
			}

			if(mu_staco_nPixHits->at(index) + mu_staco_nPixelDeadSensors->at(index) < 2) {
				goto __error;
			}

			if(mu_staco_nSCTHits->at(index) + mu_staco_nSCTDeadSensors->at(index) < 6) {
				goto __error;
			}

			if(mu_staco_nPixHoles->at(index) + mu_staco_nSCTHoles->at(index) > 2) {
				goto __error;
			}

			n = mu_staco_nTRTHits->at(index) + mu_staco_nTRTOutliers->at(index);

			if(fabs(mu_staco_eta->at(index)) < 1.9f)
			{
				if(n < 6 || mu_staco_nTRTOutliers->at(index) > 0.9f * n) {
					goto __error;
				}
			}
			else
			{
				if(n > 5 && mu_staco_nTRTOutliers->at(index) > 0.9f * n) {
					goto __error;
				}
			}

			if(fabs(mu_staco_d0_exPV->at(index)) > 1.0f) {
				goto __error;
			}

			if(fabs(mu_staco_z0_exPV->at(index)) > 10.0f) {
				goto __error;
			}

			break;

		/*---------------------------------------------------------*/
		/* MUON_CALO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_CALO:
			if(mu_calo_author->at(index) != 16) {
				goto __error;
			}

			if(mu_calo_caloMuonIdTag->at(index) < 11
			   &&
			   mu_calo_caloLRLikelihood->at(index) < 0.9f
			 ) {
				goto __error;
			}

			if(fabs(mu_calo_eta->at(index)) > 0.1f) {
				goto __error;
			}

			if(mu_calo_pt->at(index) < __mu_calo_pt) {
				goto __error;
			}

			if(mu_calo_expectBLayerHit->at(index) != 0 && mu_calo_nBLHits->at(index) <= 0) {
				goto __error;
			}

			if(mu_calo_nPixHits->at(index) + mu_calo_nPixelDeadSensors->at(index) < 2) {
				goto __error;
			}

			if(mu_calo_nSCTHits->at(index) + mu_calo_nSCTDeadSensors->at(index) < 6) {
				goto __error;
			}

			if(mu_calo_nPixHoles->at(index) + mu_calo_nSCTHoles->at(index) > 2) {
				goto __error;
			}

			n = mu_calo_nTRTHits->at(index) + mu_calo_nTRTOutliers->at(index);

			if(n > 5 && mu_calo_nTRTOutliers->at(index) > n * 0.9) {
				goto __error;
			}

			if(fabs(mu_calo_z0_exPV->at(index)) > 10.0f) {
				goto __error;
			}

			break;

		/*---------------------------------------------------------*/

		__error:
		default:
			return false;
	}

	return true;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkOverlapping(
	Int_t index,
	TLeptonType type,
	Float_t __el_et,
	Float_t __mu_staco_pt,
	Float_t __mu_calo_pt,
	Bool_t useLoose,
	Bool_t useForward,
	Int_t muonIndexNr, Int_t muonIndexArray[], TLeptonType muonTypeArray[]
) {
	Bool_t result = true;

	if(type == TYPE_ELECTRON)
	{
		/*---------------------------------------------------------*/
		/* ELECTRONS						   */
		/*---------------------------------------------------------*/

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
				if(checkObject(xedni, TYPE_ELECTRON, __el_et, __mu_staco_pt, __mu_calo_pt, useLoose, useForward) != false && electronGetEt(index) <= electronGetEt(xedni))
				{
					result = false;

					break;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* MUONS						   */
		/*---------------------------------------------------------*/

		Float_t mu_id_eta;
		Float_t mu_id_phi;

		for(Int_t i = 0; i < muonIndexNr; i++)
		{
			Int_t xedni = muonIndexArray[i];

			switch(muonTypeArray[i])
			{
				case TYPE_MUON_STACO:
					mu_id_eta = -logf(tanf(0.5f * mu_staco_id_theta->at(xedni)));
					mu_id_phi = mu_staco_id_phi->at(xedni);
					break;

				case TYPE_MUON_CALO:
					mu_id_eta = -logf(tanf(0.5f * mu_calo_id_theta->at(xedni)));
					mu_id_phi = mu_calo_id_phi->at(xedni);
					break;

				default:
					result = false;

					goto __ok;
			}

			if(sqrtf(__dR2(el_tracketa->at(index), mu_id_eta, el_trackphi->at(index), mu_id_phi)) < 0.02f)
			{
				result = false;
	
				break;
			}
		}

		/*---------------------------------------------------------*/
	}
__ok:
	return result;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::truthMatch(
	Int_t index,
	TLeptonType type
) {
#ifdef __IS_MC
	switch(type)
	{
		case TYPE_ELECTRON:
			if((el_type->at(index) != 2 || (((((((((((((((((((el_origin->at(index) != 13))))))))))))))))))))
			   &&
			   (el_type->at(index) != 4 || (el_originbkg->at(index) != 13 && el_originbkg->at(index) != 40))
			 ) {
				goto __error;
			}
			break;

		case TYPE_MUON_STACO:
			if(abs(mu_staco_truth_type->at(index)) != 13 || mu_staco_truth_mothertype->at(index) != 23) {
				goto __error;
			}
			break;

		case TYPE_MUON_CALO:
			if(abs(mu_calo_truth_type->at(index)) != 13 || mu_calo_truth_mothertype->at(index) != 23) {
				goto __error;
			}
			break;

		__error:
		default:
			return false;
	}
#endif
	return true;
}

/*-------------------------------------------------------------------------*/

Float_t __dR2(
	Float_t eta1, Float_t eta2,
	Float_t phi1, Float_t phi2
) {
	Float_t dEta = eta1 - eta2;
	Float_t dPhi = phi1 - phi2;

	while(dPhi < -M_PI) {
		dPhi += 2.0 * M_PI;
	}

	while(dPhi >= +M_PI) {
		dPhi -= 2.0 * M_PI;
	}

	return dEta * dEta + dPhi * dPhi;
}

/*-------------------------------------------------------------------------*/

TLeptonClass getLeptonClass(TLeptonType type)
{
	TLeptonClass result;

	switch(type)
	{
		case TYPE_ELECTRON:
			result = CLASS_ELECTRON;
			break;

		case TYPE_MUON_STACO:
			result = CLASS_MUON;
			break;

		case TYPE_MUON_CALO:
			result = CLASS_MUON;
			break;

		default:
			std::cout << "Oula !!!\n" << std::endl;
			exit(1);
	}

	return result;
}

/*-------------------------------------------------------------------------*/

Bool_t buildPair(
	Int_t pair[2],
	Float_t charge1,
	Float_t charge2
) {
	/**/ if(charge1 < 0.0f
		&&
		charge2 > 0.0f
	 ) {
		pair[0] = 1;
		pair[1] = 0;
	}
	else if(charge1 > 0.0f
		&&
		charge2 < 0.0f
	 ) {
		pair[0] = 0;
		pair[1] = 1;
	}
	else
	{
		pair[0] = 0;
		pair[1] = 1;

		return false;
	}

	return true;
}

/*-------------------------------------------------------------------------*/

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
) {
	/**/ if(getLeptonClass(type1) == getLeptonClass(type2)
		&&
		getLeptonClass(type2) == getLeptonClass(type3)
		&&
		getLeptonClass(type3) == getLeptonClass(type4)
	 ) {
		Int_t negatives[4];
		Int_t positives[4];

		Int_t negativeNr = 0;
		Int_t positiveNr = 0;

		/**/ if(charge1 < 0.0f) {
			negatives[negativeNr++] = 0;
		}
		else if(charge1 > 0.0f) {
			positives[positiveNr++] = 0;
		}

		/**/ if(charge2 < 0.0f) {
			negatives[negativeNr++] = 1;
		}
		else if(charge2 > 0.0f) {
			positives[positiveNr++] = 1;
		}

		/**/ if(charge3 < 0.0f) {
			negatives[negativeNr++] = 2;
		}
		else if(charge3 > 0.0f) {
			positives[positiveNr++] = 2;
		}

		/**/ if(charge4 < 0.0f) {
			negatives[negativeNr++] = 3;
		}
		else if(charge4 > 0.0f) {
			positives[positiveNr++] = 3;
		}

		if(positiveNr != 2
		   ||
		   negativeNr != 2
		 ) {
			return false;
		}

		/* 1st quadruplet */

		pair1[0] = positives[0];
		pair1[1] = negatives[0];

		pair2[0] = positives[1];
		pair2[1] = negatives[1];

		/* 2nd quadruplet */

		pair3[0] = positives[0];
		pair3[1] = negatives[1];

		pair4[0] = positives[1];
		pair4[1] = negatives[0];
	}
	else if(getLeptonClass(type1) == getLeptonClass(type2)
		&&
		getLeptonClass(type3) == getLeptonClass(type4)
	 ) {
		/* 1st quadruplet */

		if(buildPair(pair1, charge1, charge2) == false
		   ||
		   buildPair(pair2, charge3, charge4) == false
		 ) {
			return false;
		}

		pair1[0] += 0;
		pair1[1] += 0;

		pair2[0] += 2;
		pair2[1] += 2;

		/* 2nd quadruplet */

		pair3[0] = pair1[0];
		pair3[1] = pair1[1];

		pair4[0] = pair2[0];
		pair4[1] = pair2[1];
	}
	else
	{
		return false;
	}

	return true;
}

/*-------------------------------------------------------------------------*/

void reIndex(
	Int_t L[4],
	Float_t M[4],
	Int_t (* func)(const void *, const void *)
) {
	Float_t U[4] = {
		M[0],
		M[1],
		M[2],
		M[3],
	};

	Float_t V[4] = {
		M[0],
		M[1],
		M[2],
		M[3],
	};

	/**/

	qsort(U, 4, sizeof(Float_t), func);

	/**/

	for(Int_t i = 0; i < 4; i++)
	{
		for(Int_t j = 0; j < 4; j++)
		{
			if(U[i] == V[j])
			{
				L[i] =     j    ;
				V[j] = -999999.0;

				break;
			}
		}
	}
}

/*-------------------------------------------------------------------------*/

