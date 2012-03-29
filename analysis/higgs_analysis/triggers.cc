/*-------------------------------------------------------------------------*/

#include <TRandom3.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

char getlumiPeriod(int RunNumber)
{
	char result;

	/**/ if(RunNumber >= 177986 && RunNumber <= 178109) {
		result = 'B';
	}
	else if(RunNumber >= 178163 && RunNumber <= 178264) {
		result = 'C';
	}
	else if(RunNumber >= 179710 && RunNumber <= 180481) {
		result = 'D';
	}
	else if(RunNumber >= 180614 && RunNumber <= 180776) {
		result = 'E';
	}
	else if(RunNumber >= 182013 && RunNumber <= 182519) {
		result = 'F';
	}
	else if(RunNumber >= 182726 && RunNumber <= 183462) {
		result = 'G';
	}
	else if(RunNumber >= 183544 && RunNumber <= 184169) {
		result = 'H';
	}
	else if(RunNumber >= 185353 && RunNumber <= 186493) {
		result = 'I';
	}
	else if(RunNumber >= 186516 && RunNumber <= 186755) {
		result = 'J';
	}
	else if(RunNumber >= 186873 && RunNumber <= 187815) {
		result = 'K';
	}
	else if(RunNumber >= 188902 && RunNumber <= 190343) {
		result = 'L';
	}
	else if(RunNumber >= 190503 && RunNumber <= 191933) {
		result = 'M';
	}
	else
	{
		result = 0x0;
	}

	return result;
}

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::getElTrigger(void)
{
	if(core::OF == false)
	{
		elTrigger = 0x00;
#ifdef __IS_MC
		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {
			if(EF_e20_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;

			random3.SetSeed(mc_channel_number * EventNumber);

			const Float_t fracEl = (lumiPeriodI + lumiPeriodJ) / (lumiPeriodI + lumiPeriodJ + lumiPeriodK);

			if(random3.Uniform() < fracEl)
			{
				if(EF_e20_medium) {
					elTrigger |= (1 << 0);
				}
				if(EF_2e12_medium) {
					elTrigger |= (1 << 1);
				}
			}
			else
			{
				if(EF_e22_medium) {
					elTrigger |= (1 << 0);
				}
				if(EF_2e12T_medium) {
					elTrigger |= (1 << 1);
				}
			}
		}
		else if(RunNumber == 189751) // L-M
		{
			if(EF_e22vh_medium1) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12Tvh_medium) {
				elTrigger |= (1 << 1);
			}
		}
#else
		char lumiPeriod = getlumiPeriod(RunNumber);

		/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'J')
		{
			if(EF_e20_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'K' && lumiPeriod <= 'K')
		{
			if(EF_e22_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12T_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'L' && lumiPeriod <= 'M')
		{
			if(EF_e22vh_medium1) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12Tvh_medium) {
				elTrigger |= (1 << 1);
			}
		}
#endif
	}
	else
	{
		elTrigger = 0x03;
	}

	return elTrigger;
}

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::getMuTrigger(void)
{
	if(core::OF == false)
	{
		muTrigger = 0x00;
#ifdef __IS_MC
		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {
			if(EF_mu18_MG) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;

			random3.SetSeed(mc_channel_number * EventNumber);

			const Float_t fracMu = (lumiPeriodI) / (lumiPeriodI + lumiPeriodJ + lumiPeriodK);

			if(random3.Uniform() < fracMu)
			{
				if(EF_mu18_MG) {
					muTrigger |= (1 << 0);
				}
				if(EF_2mu10_loose) {
					muTrigger |= (1 << 1);
				}
			}
			else
			{
				if(EF_mu18_MG_medium) {
					muTrigger |= (1 << 0);
				}
				if(EF_2mu10_loose) {
					muTrigger |= (1 << 1);
				}
			}
		}
		else if(RunNumber == 189751) // L-M
		{
			if(EF_mu18_MG_medium) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
#else
		char lumiPeriod = getlumiPeriod(RunNumber);

		/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'I')
		{
			if(EF_mu18_MG) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'J' && lumiPeriod <= 'M')
		{
			if(EF_mu18_MG_medium) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
#endif
	}
	else
	{
		muTrigger = 0x03;
	}

	return muTrigger;
}

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::triggerMatch(
	Int_t index,
	TLeptonType type
) {
	UInt_t result = 0x00;

	std::string chain1 = "";
	std::string chain2 = "";

	bool res1;
	bool res2;

	std::pair<bool, bool> Res1;
	std::pair<bool, bool> Res2;

	TLorentzVector tlv1;
	TLorentzVector tlv2;

	switch(type)
	{
		/*---------------------------------------------------------*/

		case TYPE_ELECTRON:
#ifdef __IS_MC
			/**/ if(RunNumber == 180164 // B-D
				||
				RunNumber == 183003 // E-H
			 ) {
				chain1 = "EF_e20_medium";
				chain2 = "EF_2e12_medium";
			}
			else if(RunNumber == 186169) // I-K
			{
				TRandom3 random3;

				random3.SetSeed(mc_channel_number * EventNumber);

				const Float_t fracEl = (lumiPeriodI + lumiPeriodJ) / (lumiPeriodI + lumiPeriodJ + lumiPeriodK);

				if(random3.Uniform() < fracEl)
				{
					chain1 = "EF_e20_medium";
					chain2 = "EF_2e12_medium";
				}
				else
				{
					chain1 = "EF_e22_medium";
					chain2 = "EF_2e12T_medium";
				}
			}
			else if(RunNumber == 189751) // L-M
			{
				chain1 = "EF_e22vh_medium1";
				chain2 = "EF_2e12Tvh_medium";
			}
#else
			char lumiPeriod = getlumiPeriod(RunNumber);

			/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'J')
			{
				chain1 = "EF_e20_medium";
				chain2 = "EF_2e12_medium";
			}
			else if(lumiPeriod >= 'K' && lumiPeriod <= 'K')
			{
				chain1 = "EF_e22_medium";
				chain2 = "EF_2e12T_medium";
			}
			else if(lumiPeriod >= 'L' && lumiPeriod <= 'M')
			{
				chain1 = "EF_e22vh_medium1";
				chain2 = "EF_2e12Tvh_medium";
			}
#endif
			if(m_elTriggerMatching->match(el_tracketa->at(index), el_trackphi->at(index), chain1) != false)
			{
				result |= (1 << 0);
			}

			tlv1.SetPtEtaPhiE(
				el_cl_E->at(index) / coshf(el_tracketa->at(index)),
				el_tracketa->at(index),
				el_trackphi->at(index),
				el_cl_E->at(index)
			);

			for(Int_t xedni = 0; xedni < el_n; xedni++)
			{
				if(index != xedni)
				{
					tlv2.SetPtEtaPhiE(
						el_cl_E->at(xedni) / coshf(el_tracketa->at(xedni)),
						el_tracketa->at(xedni),
						el_trackphi->at(xedni),
						el_cl_E->at(xedni)
					);

					m_elTriggerMatching->matchDielectron(tlv1, tlv2, chain2, res1, res2);

					if(res1 != false
					   &&
					   res2 != false
					 ) {
						result |= (1 << 1);

						break;
					}
				}
			}

			break;

		/*---------------------------------------------------------*/

		case TYPE_MUON_STACO:
#ifdef __IS_MC
			/**/ if(RunNumber == 180164 // B-D
				||
				RunNumber == 183003 // E-H
			 ) {
				chain1 = "EF_mu18_MG";
				chain2 = "EF_2mu10";
			}
			else if(RunNumber == 186169) // I-K
			{
				TRandom3 random3;

				random3.SetSeed(mc_channel_number * EventNumber);

				const Float_t fracMu = (lumiPeriodI) / (lumiPeriodI + lumiPeriodJ + lumiPeriodK);

				if(random3.Uniform() < fracMu)
				{
					chain1 = "EF_mu18_MG";
					chain2 = "EF_2mu10";
				}
				else
				{
					chain1 = "EF_mu18_MG_medium";
					chain2 = "EF_2mu10";
				}
			}
			else if(RunNumber == 189751) // L-M
			{
				chain1 = "EF_mu18_MG_medium";
				chain2 = "EF_2mu10";
			}
#else
			char lumiPeriod = getlumiPeriod(RunNumber);

			/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'I')
			{
				chain1 = "EF_mu18_MG";
				chain2 = "EF_2mu10";
			}
			else if(lumiPeriod >= 'J' && lumiPeriod <= 'M')
			{
				chain1 = "EF_mu18_MG_medium";
				chain2 = "EF_2mu10";
			}
#endif
			if(m_muTriggerMatching->match(mu_staco_eta->at(index), mu_staco_phi->at(index), chain1) != false)
			{
				result |= (1 << 0);
			}

			tlv1.SetPtEtaPhiE(
				mu_staco_pt->at(index),
				mu_staco_eta->at(index),
				mu_staco_phi->at(index),
				mu_staco_E->at(index)
			);

			for(Int_t xedni = 0; xedni < mu_staco_n; xedni++)
			{
				if(index != xedni)
				{
					tlv2.SetPtEtaPhiE(
						mu_staco_pt->at(xedni),
						mu_staco_eta->at(xedni),
						mu_staco_phi->at(xedni),
						mu_staco_E->at(xedni)
					);

					m_muTriggerMatching->matchDimuon(tlv1, tlv2, chain2, Res1, Res2);

					if(Res1.first != false
					   &&
					   Res2.first != false
					 ) {
						result |= (1 << 1);

						break;
					}
				}
			}

			break;

		/*---------------------------------------------------------*/

		default:
			result = 0x03;
			break;

		/*---------------------------------------------------------*/
	}

	return result;
}

/*-------------------------------------------------------------------------*/

Int_t TLeptonAnalysis::triggerTrace(UInt_t result[])
{
	Int_t nr = 0;

	if(core::OF != false)
	{
		if(EF_e20_medium != 0) {
			result[nr++] = 0xD4CD729C;
		}

		if(EF_e22_medium != 0) {
			result[nr++] = 0xB784EC93;
		}

		if(EF_e22_medium1 != 0) {
			result[nr++] = 0xADCD942C;
		}

		if(EF_e22vh_medium1 != 0) {
			result[nr++] = 0x69EA9F52;
		}

		if(EF_2e12_medium != 0) {
			result[nr++] = 0xF48A09FA;
		}

		if(EF_2e12T_medium != 0) {
			result[nr++] = 0x80D5CCB8;
		}

		if(EF_2e12Tvh_medium != 0) {
			result[nr++] = 0xD84960ED;
		}

		if(EF_mu18_MG != 0) {
			result[nr++] = 0x0803E760;
		}

		if(EF_mu18_MG_medium != 0) {
			result[nr++] = 0x869B9356;
		}

		if(EF_2mu10_loose != 0) {
			result[nr++] = 0xD92F4787;
		}
	}

	return nr;
}

/*-------------------------------------------------------------------------*/

