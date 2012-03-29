/*-------------------------------------------------------------------------*/

#include "utils.h"

#include <HiggsZZ4lUtils/IsEMPlusPlusH4lDefs.h>

/*-------------------------------------------------------------------------*/

bool isLoosePlusPlusH4l_cr(
	double eta,
	double eT,
	double rHad,
	double rHad1,
	double Reta,
	double w2,
	double f1,
	double wstot,
	double DEmaxs1,
	double deltaEta,
	int nSi,
	int nSiOutliers,
	int nPix,
	int nPixOutliers,
	bool debug,
	bool isTrigger
) {				 					
	unsigned int eTBin = getEtBinH4l(eT);

	if(isTrigger)
	{
		eTBin = getEtBinH4l(21.0f * 1000.0f);
	}

	unsigned int etaBin = getEtaBinH4l(eta);

	if(passRHad_looseH4l(rHad, rHad1, eTBin, etaBin) == false)
	{
		return false;
	}

	if(passReta_looseH4l(Reta, eTBin, etaBin) == false)
	{
		return false;
	}

	if(passW2_looseH4l(w2, eTBin, etaBin) == false)
	{
		return false;
	}

	if(f1 > 0.005)
	{
		if(passWstot_looseH4l(wstot, eTBin, etaBin) == false)
		{
			return false;
		}
	}

	if(nSi + nSiOutliers < 4)
	{
		return false;
	}

	return true;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::el_loosePP_at(Int_t index)
{
	float eta = el_cl_eta->at(index);
	float eT = el_cl_E->at(index) / coshf(eta);

	if(eT == 0.0f)
	{
		return false;
	}

	float rHad = el_Ethad->at(index) / eT;
	float rHad1 = el_Ethad1->at(index) / eT;
	float Reta = el_reta->at(index);
	float w2 = el_weta2->at(index);
	float f1 = el_f1->at(index);
	float wstot = el_wstot->at(index);
	float DEmaxs1 = (el_emaxs1->at(index) - el_Emax2->at(index)) / (el_emaxs1->at(index) + el_Emax2->at(index));
	float deltaEta = el_deltaeta1->at(index);

	Int_t nSi = el_nSiHits->at(index);
	Int_t nSiOutliers = el_nPixelOutliers->at(index) + el_nSCTOutliers->at(index);
	Int_t nPix = el_nPixHits->at(index);
	Int_t nPixOutliers = el_nPixelOutliers->at(index);

	return isLoosePlusPlusH4l(
		eta,
		eT,
		rHad,
		rHad1,
		Reta,
		w2,
		f1,
		wstot,
		DEmaxs1,
		deltaEta,
		nSi,
		nSiOutliers,
		nPix,
		nPixOutliers,
		false,
		false
	);
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::el_loosePP_cr_at(Int_t index)
{
	float eta = el_cl_eta->at(index);
	float eT = el_cl_E->at(index) / coshf(eta);

	if(eT == 0.0f)
	{
		return false;
	}

	float rHad = el_Ethad->at(index) / eT;
	float rHad1 = el_Ethad1->at(index) / eT;
	float Reta = el_reta->at(index);
	float w2 = el_weta2->at(index);
	float f1 = el_f1->at(index);
	float wstot = el_wstot->at(index);
	float DEmaxs1 = (el_emaxs1->at(index) - el_Emax2->at(index)) / (el_emaxs1->at(index) + el_Emax2->at(index));
	float deltaEta = el_deltaeta1->at(index);

	Int_t nSi = el_nSiHits->at(index);
	Int_t nSiOutliers = el_nPixelOutliers->at(index) + el_nSCTOutliers->at(index);
	Int_t nPix = el_nPixHits->at(index);
	Int_t nPixOutliers = el_nPixelOutliers->at(index);

	return isLoosePlusPlusH4l_cr(
		eta,
		eT,
		rHad,
		rHad1,
		Reta,
		w2,
		f1,
		wstot,
		DEmaxs1,
		deltaEta,
		nSi,
		nSiOutliers,
		nPix,
		nPixOutliers,
		false,
		false
	);
}

/*-------------------------------------------------------------------------*/

