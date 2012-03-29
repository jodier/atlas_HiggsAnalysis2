/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

#include <TH1.h>
#include <TMath.h>

/*-------------------------------------------------------------------------*/

#define ZStudy_cxx
#include "ZStudy.h"

#include "../../tools/PileupReweighting/PileupReweighting/TPileupReweighting.h"

/*-------------------------------------------------------------------------*/

#define MASS_CENTER	90.2f	/* GeV */

#define FIT_LW		48.0f	/* GeV */
#define FIT_UP		130.0f	/* GeV */

#define ET_MIN		10.0f	/* GeV */
#define ET_MAX		5000.0f	/* GeV */

/*-------------------------------------------------------------------------*/

static const char *output = NULL;
static float window = 10.0f;
static bool truth = false;
static bool isMC = false;
static int cut = 0;

/*-------------------------------------------------------------------------*/

Double_t myBinomialError(Double_t cut_probe, Double_t all_probe, Double_t cut_probe_err = 0.0, Double_t all_probe_err = 0.0)
{
	Double_t r = 0.0;

	if(cut_probe == 0.0
	   ||
	   all_probe == 0.0
	 ) {
		return r;
	}

	if(cut_probe_err == 0.0
	   &&
	   all_probe_err == 0.0
	 ) {
		r = TMath::Sqrt(
			TMath::Beta(cut_probe + 3, all_probe - cut_probe + 1)
			/
			TMath::Beta(cut_probe + 1, all_probe - cut_probe + 1)
			-
			TMath::Power(
				TMath::Beta(cut_probe + 2, all_probe - cut_probe + 1)
				/
				TMath::Beta(cut_probe + 1, all_probe - cut_probe + 1)
			, 2.0)
		);
	}

	if(cut_probe_err != 0.0
	   ||
	   all_probe_err != 0.0
	   ||
	   TMath::IsNaN(r) != false
	 ) {
		Double_t eff = cut_probe / all_probe;

		Double_t a = cut_probe + cut_probe_err * cut_probe_err;
		Double_t b = all_probe + all_probe_err * all_probe_err;

		Double_t c = (1.0 - 2.0 * eff) * a + eff * eff * b;

		r = (c >= 0.0) ? sqrt(c) / all_probe : 0.0;
	}

	return r;
}

/*-------------------------------------------------------------------------*/

#include <RooAddPdf.h>
#include <RooRealVar.h>
#include <RooDataHist.h>
#include <RooExtendPdf.h>
#include <RooFFTConvPdf.h>
#include <RooRealConstant.h>

/*-------------------------------------------------------------------------*/

#include <RooCBShape.h>
#include <RooBreitWigner.h>
#include <RooExponential.h>

/*-------------------------------------------------------------------------*/

Float_t mySignalEvent(TH1F *h, Float_t &error, Bool_t force = false)
{
	float SIG_LW = MASS_CENTER - window;
	float SIG_UP = MASS_CENTER + window;

	/*------------------------------------*/
	/* SIDE BAND			      */
	/*------------------------------------*/

	Int_t binLw = h->FindBin(SIG_LW + 0.1f);
	Int_t binUp = h->FindBin(SIG_UP - 0.1f);

	Int_t bin60  = h->FindBin(60.0f + 0.1f);
	Int_t bin120 = h->FindBin(120.0f - 0.1f);

	Float_t evtNr0 = h->Integral(binLw, binUp);

	if(evtNr0 == 0.0f || truth != false)
	{
		error = 0.0f;

		return evtNr0;
	}

	Float_t alpha = (SIG_UP - SIG_LW) / ((SIG_LW - 60.0f) + (120.0f - SIG_UP));

	Float_t bkgNr0 = alpha * (h->Integral(bin60, binLw - 1) + h->Integral(binUp + 1, bin120)), sigNr0 = evtNr0 - bkgNr0;

	/*------------------------------------*/
	/* X				      */
	/*------------------------------------*/

	RooRealVar X("X", "m_{ee} [GeV]", FIT_LW, FIT_UP);

	X.setBins(10000, "cache");
	X.setRange("peakRange", SIG_LW, SIG_UP);

	/*------------------------------------*/
	/* Crystal Ball			      */
	/*------------------------------------*/

	RooRealVar mass1("mass1", "mass1", 0.0, -5.0, +5.0);
	RooRealVar sigma1("sigma1", "sigma1", 3.5, 1.0, 10.0);
	RooRealVar a("a", "a", 1.0, 0.0, 5.0);
	RooRealVar n("n", "n", 4.0, 0.0, 20.0);

	RooCBShape CB("CB", "CB", X, mass1, sigma1, a, n);

	/*------------------------------------*/
	/* Breit & Wigner		      */
	/*------------------------------------*/

	RooBreitWigner BW("BW", "BW", X, RooRealConstant::value(MASS_CENTER), RooRealConstant::value(2.5));

	/*------------------------------------*/
	/* Breit & Wigner (x) Crystal Ball    */
	/*------------------------------------*/

	RooFFTConvPdf CBBW("CBBW", "CB (x) BW", X, BW, CB);

	CBBW.setBufferFraction(0.2);

	/*------------------------------------*/
	/* Background			      */
	/*------------------------------------*/

	RooRealVar tau("tau", "tau", -0.01, -1.0, 0.0);

	RooExponential BKGD("BKGD", "BKGD", X, tau);

	/*------------------------------------*/
	/* Signal			      */
	/*------------------------------------*/

	RooRealVar rooNSig("n_sig", "n_sig", sigNr0, 0.0, evtNr0);
	RooRealVar rooNBkg("n_bkg", "n_bkg", bkgNr0, 0.0, evtNr0);

	RooExtendPdf sigPdf("sig_pdf", "sig_pdf", CBBW, rooNSig, "peakRange");
	RooExtendPdf bkgPdf("bkg_pdf", "bkg_pdf", BKGD, rooNBkg, "peakRange");

	RooAddPdf fitPdf("fit_pdf", "fit_pdf", RooArgList(sigPdf, bkgPdf));

	/*------------------------------------*/
	/* Import & Fit			      */
	/*------------------------------------*/

	RooDataHist import("import", "import", X, RooFit::Import(*h));

	fitPdf.fitTo(import, RooFit::Extended(kTRUE), RooFit::SumW2Error(kFALSE), RooFit::Save(kTRUE));

	/*------------------------------------*/
	/* Result			      */
	/*------------------------------------*/

	Float_t result;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "#############################################################################" << std::endl;
	std::cout << "#############################################################################" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	result = evtNr0 - rooNBkg.getVal();

	error = rooNBkg.getError();

	std::cout << "Signal: " <<      result      << "±" <<        error       << std::endl;
	std::cout << "Bkgd  : " << rooNBkg.getVal() << "±" << rooNBkg.getError() << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	return result;
}

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
		//std::cout << "Loading '" << fName << "'..." << std::endl;

		chain->AddFile(fName.c_str());
	}

	/**/

	stream.close();

	return true;
}

/*-------------------------------------------------------------------------*/

static void __do(const char *fileName1, const char *fileName2, const char *fileName3, int theCut, const char *fName1, const char *fName2)
{
	TChain *chain1 = new TChain("Z1");
	TChain *chain2 = new TChain("Z1");

	if(localLoader(chain1, fName1) == false
	   ||
	   localLoader(chain2, fName2) == false
	 ) {
		std::cout << "Oula !!!" << std::endl;

		return;
	}

	ZStudy alg1(chain1);
	ZStudy alg2(chain2);

	std::cout << "MC:" << std::endl;
	output = fileName1;
	truth = false;
	isMC = true;
	cut = theCut;
	alg1.Loop();

	std::cout << "TRUTH:" << std::endl;
	output = fileName2;
	truth = true;
	isMC = true;
	cut = theCut;
	alg1.Loop();

	std::cout << "DATA:" << std::endl;
	output = fileName3;
	truth = false;
	isMC = false;
	cut = theCut;
	alg2.Loop();

	delete chain1;
	delete chain2;
}

/*-------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		std::cerr << argv[0] << " mc.txt data.txt window" << std::endl;

		return 1;
	}

	window = atof(argv[3]);

	__do("eff_mc1.root", "eff_truth1.root", "eff_data1.root", 1, argv[1], argv[2]);
	__do("eff_mc2.root", "eff_truth2.root", "eff_data2.root", 2, argv[1], argv[2]);
	__do("eff_mc3.root", "eff_truth3.root", "eff_data3.root", 3, argv[1], argv[2]);
	__do("eff_mc4.root", "eff_truth4.root", "eff_data4.root", 4, argv[1], argv[2]);

	return 0;
}

/*-------------------------------------------------------------------------*/

#define __SET1(hist, eta, mass, theWeight) \
		hist[0]->Fill(mass, theWeight);			\
								\
		/**/ if(eta >= -2.47 && eta < -2.01) {		\
			hist[1]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= -2.01 && eta < -1.52) {		\
			hist[2]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= -1.52 && eta < -1.37) {		\
			hist[3]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= -1.37 && eta < -0.8) {		\
			hist[4]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= -0.8 && eta < 0.0) {		\
			hist[5]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= 0.0 && eta < +0.8) {		\
			hist[6]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= +0.8 && eta < +1.37) {		\
			hist[7]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= +1.37 && eta < +1.52) {		\
			hist[8]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= +1.52 && eta < +2.01) {		\
			hist[9]->Fill(mass, theWeight);		\
		}						\
		else if(eta >= +2.01 && eta < +2.47) {		\
			hist[10]->Fill(mass, theWeight);	\
		}						\

/*-------------------------------------------------------------------------*/

#define __SET2(hist, pt, mass, theWeight) \
		hist[0]->Fill(mass, theWeight);			\
								\
		/**/ if(pt >= 10.0 && pt < 15.0) {		\
			hist[1]->Fill(mass, theWeight);		\
		}						\
		else if(pt >= 15.0 && pt < 20.0) {		\
			hist[2]->Fill(mass, theWeight);		\
		}						\
		else if(pt >= 20.0 && pt < 25.0) {		\
			hist[3]->Fill(mass, theWeight);		\
		}						\
		else if(pt >= 25.0 && pt < 30.0) {		\
			hist[4]->Fill(mass, theWeight);		\
		}						\
		else if(pt >= 30.0 && pt < 35.0) {		\
			hist[5]->Fill(mass, theWeight);		\
		}						\
		else if(pt >= 35.0 && pt < 40.0) {		\
			hist[6]->Fill(mass, theWeight);		\
		}						\
		else if(pt >= 40.0 && pt < 45.0) {		\
			hist[7]->Fill(mass, theWeight);		\
		}						\
		else if(pt >= 45.0 && pt < 50.0) {		\
			hist[8]->Fill(mass, theWeight);		\
		}						\

/*-------------------------------------------------------------------------*/

#define __SET3(hist, nPV2, mass, theWeight) \
		hist[0]->Fill(mass, theWeight);			\
								\
		/**/ if(nPV2 >= 0.0 && nPV2 < 1.0) {		\
			hist[1]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 1.0 && nPV2 < 2.0) {		\
			hist[2]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 2.0 && nPV2 < 3.0) {		\
			hist[3]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 3.0 && nPV2 < 4.0) {		\
			hist[4]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 4.0 && nPV2 < 5.0) {		\
			hist[5]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 5.0 && nPV2 < 6.0) {		\
			hist[6]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 6.0 && nPV2 < 7.0) {		\
			hist[7]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 7.0 && nPV2 < 8.0) {		\
			hist[8]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 8.0 && nPV2 < 9.0) {		\
			hist[9]->Fill(mass, theWeight);		\
		}						\
		else if(nPV2 >= 9.0 && nPV2 < 10.0) {		\
			hist[10]->Fill(mass, theWeight);	\
		}						\
		else if(nPV2 >= 10.0 && nPV2 < 11.0) {		\
			hist[11]->Fill(mass, theWeight);	\
		}						\
		else if(nPV2 >= 11.0 && nPV2 < 12.0) {		\
			hist[12]->Fill(mass, theWeight);	\
		}						\
		else if(nPV2 >= 12.0 && nPV2 < 13.0) {		\
			hist[13]->Fill(mass, theWeight);	\
		}						\
		else if(nPV2 >= 13.0 && nPV2 < 14.0) {		\
			hist[14]->Fill(mass, theWeight);	\
		}						\
		else if(nPV2 >= 14.0 && nPV2 < 15.0) {		\
			hist[15]->Fill(mass, theWeight);	\
		}						\
		else if(nPV2 >= 15.0 && nPV2 < 16.0) {		\
			hist[16]->Fill(mass, theWeight);	\
		}						\
		else if(nPV2 >= 16.0 && nPV2 < 17.0) {		\
			hist[17]->Fill(mass, theWeight);	\
		}						\

/*-------------------------------------------------------------------------*/

struct __TandP_s
{
	Float_t cut_p[32];		// # prob e+ passing cuts
	Float_t all_p[32];		// # prob e+
	TH1F *cut_p_hist[32];
	TH1F *all_p_hist[32];

	Float_t cut_e[32];		// # prob e- passing cuts
	Float_t all_e[32];		// # prob e-
	TH1F *cut_e_hist[32];
	TH1F *all_e_hist[32];

	TH1F *cut_hist[32];
	TH1F *all_hist[32];
};

/*-------------------------------------------------------------------------*/

void __initialize(struct __TandP_s *v)
{
	static int r = 0;

	memset(v, 0x00, sizeof(struct __TandP_s));

	for(int i = 0; i < 32; i++, r++)
	{
		std::ostringstream oss1;
		oss1 << "cut_p_hist" << r;
		std::ostringstream oss2;
		oss2 << "all_p_hist" << r;
		std::ostringstream oss3;
		oss3 << "cut_e_hist" << r;
		std::ostringstream oss4;
		oss4 << "all_e_hist" << r;
		std::ostringstream oss5;
		oss5 << "cut_hist" << r;
		std::ostringstream oss6;
		oss6 << "all_hist" << r;

		v->cut_p_hist[i] = new TH1F(oss1.str().c_str(), "", (int) (FIT_UP - FIT_LW), FIT_LW, FIT_UP);
		v->all_p_hist[i] = new TH1F(oss2.str().c_str(), "", (int) (FIT_UP - FIT_LW), FIT_LW, FIT_UP);
		v->cut_e_hist[i] = new TH1F(oss3.str().c_str(), "", (int) (FIT_UP - FIT_LW), FIT_LW, FIT_UP);
		v->all_e_hist[i] = new TH1F(oss4.str().c_str(), "", (int) (FIT_UP - FIT_LW), FIT_LW, FIT_UP);
		v->cut_hist[i] = new TH1F(oss5.str().c_str(), "", (int) (FIT_UP - FIT_LW), FIT_LW, FIT_UP);
		v->all_hist[i] = new TH1F(oss6.str().c_str(), "", (int) (FIT_UP - FIT_LW), FIT_LW, FIT_UP);
	}
}

/*-------------------------------------------------------------------------*/

void __finalize(struct __TandP_s *v)
{
	for(int i = 0; i < 32; i++)
	{
		v->cut_hist[i]->Add(v->cut_p_hist[i]);
		v->cut_hist[i]->Add(v->cut_e_hist[i]);
		v->all_hist[i]->Add(v->all_p_hist[i]);
		v->all_hist[i]->Add(v->all_e_hist[i]);
	}
}

/*-------------------------------------------------------------------------*/

void ZStudy::Loop(void)
{
	if(fChain == 0)
	{
		return;
	}

	/**/

	struct __TandP_s v1;
	struct __TandP_s v2;
	struct __TandP_s v3;

	__initialize(&v1);
	__initialize(&v2);
	__initialize(&v3);	

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
			Bool_t isOk = false;

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

			Float_t theWeight = weight1[i] * weight2[i] * weight3[i];

			Bool_t q = (truth == false || (l1_truthMatch[i] != false && l2_truthMatch[i] != false));

			if(l1_tight[i] != 0 && l1_pt[i] > 20.0f && l1_tkIso20[i] < 0.15f && q)
			{
				bool isOk = false;

				switch(cut)
				{
					case 1:
						isOk = l2_clIso20[i] < 0.3f;
						break;

					case 2:
						isOk = l2_tkIso20[i] < 0.15f;
						break;

					case 3:
						isOk = l2_d0sigma[i] < 6.0f;
						break;

					case 4:
						isOk = l2_clIso20[i] < 0.3f && l2_tkIso20[i] < 0.15f && l2_d0sigma[i] < 6.0f;
						break;
				}

				if(isOk)
				{
					__SET1(v1.cut_e_hist, l2_eta[i], Z_m[i], theWeight);
					__SET2(v2.cut_e_hist, l2_pt[i], Z_m[i], theWeight);
					__SET3(v3.cut_e_hist, nPV2, Z_m[i], theWeight);
				}

				__SET1(v1.all_e_hist, l2_eta[i], Z_m[i], theWeight);
				__SET2(v2.all_e_hist, l2_pt[i], Z_m[i], theWeight);
				__SET3(v3.all_e_hist, nPV2, Z_m[i], theWeight);
			}

			if(l2_tight[i] != 0 && l2_pt[i] > 20.0f && l2_tkIso20[i] < 0.15f && q)
			{
				bool isOk = false;

				switch(cut)
				{
					case 1:
						isOk = l1_clIso20[i] < 0.3f;
						break;

					case 2:
						isOk = l1_tkIso20[i] < 0.15f;
						break;

					case 3:
						isOk = l1_d0sigma[i] < 6.0f;
						break;

					case 4:
						isOk = l1_clIso20[i] < 0.3f && l1_tkIso20[i] < 0.15f && l1_d0sigma[i] < 6.0f;
						break;
				}

				if(isOk)
				{
					__SET1(v1.cut_p_hist, l1_eta[i], Z_m[i], theWeight);
					__SET2(v2.cut_p_hist, l1_pt[i], Z_m[i], theWeight);
					__SET3(v3.cut_p_hist, nPV2, Z_m[i], theWeight);
				}

				__SET1(v1.all_p_hist, l1_eta[i], Z_m[i], theWeight);
				__SET2(v2.all_p_hist, l1_pt[i], Z_m[i], theWeight);
				__SET3(v3.all_p_hist, nPV2, Z_m[i], theWeight);
			}
		}
	}

	__finalize(&v1);
	__finalize(&v2);
	__finalize(&v3);

	Float_t error_cut;
	Float_t error_all;

	Float_t cut = mySignalEvent(v1.cut_hist[0], error_cut);
	Float_t all = mySignalEvent(v1.all_hist[0], error_all);

	printf("Efficiency: %.3f±%.3f\n", 100.0 * cut / all, 100.0 * myBinomialError(cut, all, error_cut, error_all));

	const Float_t bin_array1[] = {
		-2.47, -2.01, -1.52, -1.37, -0.8, 0.0, +0.8, +1.37, +1.52, +2.01, +2.47
	};

	const Float_t bin_array2[] = {
		10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0
	};

	TH1F h1("h1", "Efficiency", 10, bin_array1);
	TH1F h2("h2", "Efficiency", 8, bin_array2);
	TH1F h3("h3", "Efficiency", 17, 0.0, 17.0);

	for(int i = 1; i <= h1.GetNbinsX(); i++)
	{
		Float_t error_cut;
		Float_t error_all;
		Float_t error_cut_p = 0.0f;
		Float_t error_all_p = 0.0f;
		Float_t error_cut_e = 0.0f;
		Float_t error_all_e = 0.0f;

		Float_t cut = mySignalEvent(v1.cut_hist[i], error_cut);
		Float_t all = mySignalEvent(v1.all_hist[i], error_all);
		Float_t cut_p = 1.0f;//mySignalEvent(v1.cut_p_hist[i], error_cut_p);
		Float_t all_p = 1.0f;//mySignalEvent(v1.all_p_hist[i], error_all_p);
		Float_t cut_e = 1.0f;//mySignalEvent(v1.cut_e_hist[i], error_cut_e);
		Float_t all_e = 1.0f;//mySignalEvent(v1.all_e_hist[i], error_all_e);

		if(cut == 0.0
		   ||
		   all == 0.0
		 ) {
			printf("eff (eta): -\n");

			continue;
		}

		Float_t eff   = (cut  ) / (all  );
		Float_t eff_p = (cut_p) / (all_p);
		Float_t eff_e = (cut_e) / (all_e);

		Float_t err   = myBinomialError(cut  , all  , error_cut  , error_all  );
		Float_t err_p = myBinomialError(cut_p, all_p, error_cut_p, error_all_p);
		Float_t err_e = myBinomialError(cut_e, all_e, error_cut_e, error_all_e);

		h1.SetBinContent(i, eff);
		h1.SetBinError(i, err);

		printf("eff (pt): %.3f±%.3f, (%.3f±%.3f, %.3f±%.3f), cut: %.0f±%.0f, all: %.0f±%.0f\n",
			100.0 * eff  , 100.0 * err  ,
			100.0 * eff_p, 100.0 * err_p,
			100.0 * eff_e, 100.0 * err_e,
			cut, error_cut, all, error_all
		);
	}

	for(int i = 1; i <= h2.GetNbinsX(); i++)
	{
		Float_t error_cut;
		Float_t error_all;
		Float_t error_cut_p = 0.0f;
		Float_t error_all_p = 0.0f;
		Float_t error_cut_e = 0.0f;
		Float_t error_all_e = 0.0f;

		Float_t cut = mySignalEvent(v2.cut_hist[i], error_cut);
		Float_t all = mySignalEvent(v2.all_hist[i], error_all);
		Float_t cut_p = 1.0f;//mySignalEvent(v2.cut_p_hist[i], error_cut_p);
		Float_t all_p = 1.0f;//mySignalEvent(v2.all_p_hist[i], error_all_p);
		Float_t cut_e = 1.0f;//mySignalEvent(v2.cut_e_hist[i], error_cut_e);
		Float_t all_e = 1.0f;//mySignalEvent(v2.all_e_hist[i], error_all_e);

		if(cut == 0.0
		   ||
		   all == 0.0
		 ) {
			printf("eff (pt): -\n");

			continue;
		}

		Float_t eff   = (cut  ) / (all  );
		Float_t eff_p = (cut_p) / (all_p);
		Float_t eff_e = (cut_e) / (all_e);

		Float_t err   = myBinomialError(cut  , all  , error_cut  , error_all  );
		Float_t err_p = myBinomialError(cut_p, all_p, error_cut_p, error_all_p);
		Float_t err_e = myBinomialError(cut_e, all_e, error_cut_e, error_all_e);

		h2.SetBinContent(i, eff);
		h2.SetBinError(i, err);

		printf("eff (pt): %.3f±%.3f, (%.3f±%.3f, %.3f±%.3f), cut: %.0f±%.0f, all: %.0f±%.0f\n",
			100.0 * eff  , 100.0 * err  ,
			100.0 * eff_p, 100.0 * err_p,
			100.0 * eff_e, 100.0 * err_e,
			cut, error_cut, all, error_all
		);
	}

	for(int i = 1; i <= h3.GetNbinsX(); i++)
	{
		Float_t error_cut;
		Float_t error_all;
		Float_t error_cut_p = 0.0f;
		Float_t error_all_p = 0.0f;
		Float_t error_cut_e = 0.0f;
		Float_t error_all_e = 0.0f;

		Float_t cut = mySignalEvent(v3.cut_hist[i], error_cut);
		Float_t all = mySignalEvent(v3.all_hist[i], error_all);
		Float_t cut_p = 1.0f;//mySignalEvent(v3.cut_p_hist[i], error_cut_p);
		Float_t all_p = 1.0f;//mySignalEvent(v3.all_p_hist[i], error_all_p);
		Float_t cut_e = 1.0f;//mySignalEvent(v3.cut_e_hist[i], error_cut_e);
		Float_t all_e = 1.0f;//mySignalEvent(v3.all_e_hist[i], error_all_e);

		if(cut == 0.0
		   ||
		   all == 0.0
		 ) {
			printf("eff (PV2): -\n");

			continue;
		}

		Float_t eff   = (cut  ) / (all  );
		Float_t eff_p = (cut_p) / (all_p);
		Float_t eff_e = (cut_e) / (all_e);

		Float_t err   = myBinomialError(cut  , all  , error_cut  , error_all  );
		Float_t err_p = myBinomialError(cut_p, all_p, error_cut_p, error_all_p);
		Float_t err_e = myBinomialError(cut_e, all_e, error_cut_e, error_all_e);

		h3.SetBinContent(i, eff);
		h3.SetBinError(i, err);

		printf("eff (PV2): %.3f±%.3f, (%.3f±%.3f, %.3f±%.3f), cut: %.0f±%.0f, all: %.0f±%.0f\n",
			100.0 * eff  , 100.0 * err  ,
			100.0 * eff_p, 100.0 * err_p,
			100.0 * eff_e, 100.0 * err_e,
			cut, error_cut, all, error_all
		);
	}

	/**/

	std::cout << "output: " << output << std::endl;

	TFile file(output, "recreate");

	file.cd();

	h1.Write();
	h2.Write();
	h3.Write();

	v1.cut_hist[0]->Write();
	v1.all_hist[0]->Write();

	file.Close();
}

/*-------------------------------------------------------------------------*/

