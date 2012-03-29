/*-------------------------------------------------------------------------*/

Double_t myBinomialError(Double_t yes_probe, Double_t all_probe)
{
	Double_t eff = yes_probe / all_probe;

	return TMath::Sqrt(eff * (1.0 - eff) / all_probe);
}

/*-------------------------------------------------------------------------*/

bool localLoader(TChain *chain, const char *fname, bool verbose = false)
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
		if(verbose != false)
		{
			std::cout << "Reading: " << fName.c_str() << "..." << std::endl;
		}

		chain->AddFile(fName.c_str());
	}

	/**/

	stream.close();

	return true;
}

/*-------------------------------------------------------------------------*/

void print(const char *name, const char *fname, const char *title, int chanel)
{
	TChain *chain0 = new TChain("Truth");
	TChain *chain1 = new TChain("Event");
	TChain *chain2 = new TChain(  name );

	if(localLoader(chain0, fname, false) == false
	   ||
	   localLoader(chain1, fname, false) == false
	   ||
	   localLoader(chain2, fname, false) == false
	 ) {
		return;
	}

	/*-----------------------------------------------------------------*/

	Int_t eeee_nr;
	Int_t uuuu_nr;
	Int_t eeuu_nr;

	TBranch *b_eeee_nr;
	TBranch *b_uuuu_nr;
	TBranch *b_eeuu_nr;

	chain0->SetBranchAddress("eeee_nr", &eeee_nr, &b_eeee_nr);
	chain0->SetBranchAddress("uuuu_nr", &uuuu_nr, &b_uuuu_nr);
	chain0->SetBranchAddress("eeuu_nr", &eeuu_nr, &b_eeuu_nr);

	chain0->GetEntry(0);

	/*-----------------------------------------------------------------*/

	Short_t cnt0;
	Short_t cnt1;
	Short_t cnt2;
	Short_t cnt3;
	Short_t cnt4;
	Short_t cnt5;
	Short_t cnt6;
	Short_t cnt7;
	Short_t cnt8_eeuu;
	Short_t cnt8_uuee;
	Short_t cnt9_eeuu;
	Short_t cnt9_uuee;
	Short_t cnt10_eeuu;
	Short_t cnt10_uuee;

	TBranch *b_cnt0;
	TBranch *b_cnt1;
	TBranch *b_cnt2;
	TBranch *b_cnt3;
	TBranch *b_cnt4;
	TBranch *b_cnt5;
	TBranch *b_cnt6;
	TBranch *b_cnt7;
	TBranch *b_cnt8_eeuu;
	TBranch *b_cnt8_uuee;
	TBranch *b_cnt9_eeuu;
	TBranch *b_cnt9_uuee;
	TBranch *b_cnt10_eeuu;
	TBranch *b_cnt10_uuee;

	Float_t weight1;
	Float_t weight2;
	Float_t weight3;

	TBranch *b_weight1;
	TBranch *b_weight2;
	TBranch *b_weight3;

	/*-----------------------------------------------------------------*/

	chain2->SetBranchAddress("cnt0", &cnt0, &b_cnt0);
	chain2->SetBranchAddress("cnt1", &cnt1, &b_cnt1);
	chain2->SetBranchAddress("cnt2", &cnt2, &b_cnt2);
	chain2->SetBranchAddress("cnt3", &cnt3, &b_cnt3);
	chain2->SetBranchAddress("cnt4", &cnt4, &b_cnt4);
	chain2->SetBranchAddress("cnt5", &cnt5, &b_cnt5);
	chain2->SetBranchAddress("cnt6", &cnt6, &b_cnt6);
	chain2->SetBranchAddress("cnt7", &cnt7, &b_cnt7);
	chain2->SetBranchAddress("cnt8_eeuu", &cnt8_eeuu, &b_cnt8_eeuu);
	chain2->SetBranchAddress("cnt8_uuee", &cnt8_uuee, &b_cnt8_uuee);
	chain2->SetBranchAddress("cnt9_eeuu", &cnt9_eeuu, &b_cnt9_eeuu);
	chain2->SetBranchAddress("cnt9_uuee", &cnt9_uuee, &b_cnt9_uuee);
	chain2->SetBranchAddress("cnt10_eeuu", &cnt10_eeuu, &b_cnt10_eeuu);
	chain2->SetBranchAddress("cnt10_uuee", &cnt10_uuee, &b_cnt10_uuee);

	chain2->SetBranchAddress("weight1", &weight1, &b_weight1);
	chain2->SetBranchAddress("weight2", &weight2, &b_weight2);
	chain2->SetBranchAddress("weight3", &weight3, &b_weight3);

	/*-----------------------------------------------------------------*/

	Float_t CNT0 = 0;
	Float_t CNT1 = 0;
	Float_t CNT2 = 0;
	Float_t CNT3 = 0;
	Float_t CNT4 = 0;
	Float_t CNT5 = 0;
	Float_t CNT6 = 0;
	Float_t CNT7 = 0;
	Float_t CNT8_eeuu = 0;
	Float_t CNT8_uuee = 0;
	Float_t CNT9_eeuu = 0;
	Float_t CNT9_uuee = 0;
	Float_t CNT10_eeuu = 0;
	Float_t CNT10_uuee = 0;

	const Long64_t eventNr = chain2->GetEntries();

	for(Long64_t event = 0; event < eventNr; event++)
	{
		if(chain2->LoadTree(event) < 0)
		{
			break;
		}

		chain2->GetEntry(event);

		/**/

		if(cnt0 > 0) {
			CNT0 += weight1;
		}
		if(cnt1 > 0) {
			CNT1 += weight1;
		}
		if(cnt2 > 0) {
			CNT2 += weight1;
		}
		if(cnt3 > 0) {
			CNT3 += weight1;
		}
		if(cnt4 > 0) {
			CNT4 += weight1;
		}
		if(cnt5 > 0) {
			CNT5 += weight1;
		}
		if(cnt6 > 0) {
			CNT6 += weight1;
		}
		if(cnt7 > 0) {
			CNT7 += weight1;
		}
		if(cnt8_eeuu > 0) {
			CNT8_eeuu += weight1;
		}
		if(cnt8_uuee > 0) {
			CNT8_uuee += weight1;
		}
		if(cnt9_eeuu > 0) {
			CNT9_eeuu += weight1;
		}
		if(cnt9_uuee > 0) {
			CNT9_uuee += weight1;
		}
		if(cnt10_eeuu > 0) {
			CNT10_eeuu += weight1;
		}
		if(cnt10_uuee > 0) {
			CNT10_uuee += weight1;
		}
	}

	/*-----------------------------------------------------------------*/

	std::cout << "\033[36m";
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << title << std::endl;
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << "\033[0m";

	printf("1 - SFOS\t%.0f - %.2f\% ± %.2f\%\n", CNT1, 100.0f * CNT1 / CNT0, 100.0f * myBinomialError(CNT1, CNT0));
	printf("2 - Kin.\t%.0f - %.2f\% ± %.2f\%\n", CNT2, 100.0f * CNT2 / CNT1, 100.0f * myBinomialError(CNT2, CNT1));
	printf("3 - Trig.\t%.0f - %.2f\% ± %.2f\%\n", CNT3, 100.0f * CNT3 / CNT2, 100.0f * myBinomialError(CNT3, CNT2));
	printf("4 - Z1\t\t%.0f - %.2f\% ± %.2f\%\n", CNT4, 100.0f * CNT4 / CNT3, 100.0f * myBinomialError(CNT4, CNT3));
	printf("5 - Z2\t\t%.0f - %.2f\% ± %.2f\%\n", CNT5, 100.0f * CNT5 / CNT4, 100.0f * myBinomialError(CNT5, CNT4));
	printf("6 - min[ΔR]\t%.0f - %.2f\% ± %.2f\%\n", CNT6, 100.0f * CNT6 / CNT5, 100.0f * myBinomialError(CNT6, CNT5));
	printf("7 - J/ψ veto\t%.0f - %.2f\% ± %.2f\%\n", CNT7, 100.0f * CNT7 / CNT6, 100.0f * myBinomialError(CNT7, CNT6));

	/**/ if(chanel == 1)
	{
		Float_t CNT8 = CNT8_eeuu + CNT8_uuee;
		Float_t CNT9 = CNT9_eeuu + CNT9_uuee;
		Float_t CNT10 = CNT10_eeuu + CNT10_uuee;

		printf("8 - Track iso.\t%.0f - %.2f\% ± %.2f\%\n", CNT8, 100.0f * CNT8 / CNT7, 100.0f * myBinomialError(CNT8, CNT7));
		printf("9 - Calo iso.\t%.0f - %.2f\% ± %.2f\%\n", CNT9, 100.0f * CNT9 / CNT8, 100.0f * myBinomialError(CNT9, CNT8));
		printf("A - d0sigd0\t%.0f - %.2f\% ± %.2f\%\n", CNT10, 100.0f * CNT10 / CNT9, 100.0f * myBinomialError(CNT10, CNT9));

		printf("\033[32mε = %.2f\% ± %.2f\%\033[0m\n", 100.0f * CNT10 / eeee_nr, 100.0f * myBinomialError(CNT10, eeee_nr));
	}
	else if(chanel == 2)
	{
		Float_t CNT8 = CNT8_eeuu + CNT8_uuee;
		Float_t CNT9 = CNT9_eeuu + CNT9_uuee;
		Float_t CNT10 = CNT10_eeuu + CNT10_uuee;

		printf("8 - Track iso.\t%.0f - %.2f\% ± %.2f\%\n", CNT8, 100.0f * CNT8 / CNT7, 100.0f * myBinomialError(CNT8, CNT7));
		printf("9 - Calo iso.\t%.0f - %.2f\% ± %.2f\%\n", CNT9, 100.0f * CNT9 / CNT8, 100.0f * myBinomialError(CNT9, CNT8));
		printf("A - d0sigd0\t%.0f - %.2f\% ± %.2f\%\n", CNT10, 100.0f * CNT10 / CNT9, 100.0f * myBinomialError(CNT10, CNT9));

		printf("\033[32mε = %.2f\% ± %.2f\%\033[0m\n", 100.0f * CNT10 / uuuu_nr, 100.0f * myBinomialError(CNT10, uuuu_nr));
	}
	else if(chanel == 3)
	{
		Float_t CNT8 = CNT8_eeuu + CNT8_uuee;
		Float_t CNT10 = CNT10_eeuu + CNT10_uuee;

		printf("8 - Track iso.\t%.0f|%.0f - %.2f\% ± %.2f\%\n", CNT8_eeuu, CNT8_uuee, 100.0f * CNT8 / CNT7, 100.0f * myBinomialError(CNT8, CNT7));
		printf("9 - Calo iso.\t%.0f|%.0f - %.2f|%.2f\% ± %.2f|%.2f\%\n", CNT9_eeuu, CNT9_uuee, 100.0f * CNT9_eeuu / CNT8_eeuu, 100.0f * CNT9_uuee / CNT8_uuee, 100.0f * myBinomialError(CNT9_eeuu, CNT8_eeuu), 100.0f * myBinomialError(CNT9_uuee, CNT8_uuee));
		printf("A - d0sigd0\t%.0f|%.0f - %.2f|%.2f\% ± %.2f|%.2f\%\n", CNT10_eeuu, CNT10_uuee, 100.0f * CNT10_eeuu / CNT9_eeuu, 100.0f * CNT10_uuee / CNT9_uuee, 100.0f * myBinomialError(CNT10_eeuu, CNT9_eeuu), 100.0f * myBinomialError(CNT10_uuee, CNT9_uuee));

		printf("\033[32mε = %.2f\% ± %.2f\%\033[0m\n", 100.0f * CNT10 / eeuu_nr, 100.0f * myBinomialError(CNT10, eeuu_nr));
	}

	/*-----------------------------------------------------------------*/

	delete chain0;
	delete chain1;
	delete chain2;

	/*-----------------------------------------------------------------*/
}

/*-------------------------------------------------------------------------*/

void cut_flow1(void)
{
	const char fname[4096];
	std::cout << ".txt filename:" << std::endl;
	std::cin >> fname;

	if(strstr(fname, "uon") == NULL)
	{
		print("H1", fname, "H->eeee", 1);
	}

	print("H2", fname, "H->µµµµ", 2);
	print("H3", fname, "H->eeµµ|µµee", 3);
}

/*-------------------------------------------------------------------------*/

