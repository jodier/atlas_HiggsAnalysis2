/*-------------------------------------------------------------------------*/

#include <TMath.h>

#include "include/core.h"

/*-------------------------------------------------------------------------*/

Double_t core::binomialError(Double_t x, Double_t y)
{
	Double_t error = TMath::Sqrt(
		TMath::Beta(x + 3, y - x + 1)
		/
		TMath::Beta(x + 1, y - x + 1)
		-
		TMath::Power(
			TMath::Beta(x + 2, y - x + 1)
			/
			TMath::Beta(x + 1, y - x + 1)
		, 2.0)
	);

	if(TMath::IsNaN(error) != false)
	{
		Double_t eff = x / y;

		error = TMath::Sqrt(eff * (1.0 - eff) / y);
	}

	return error;
}

/*-------------------------------------------------------------------------*/

