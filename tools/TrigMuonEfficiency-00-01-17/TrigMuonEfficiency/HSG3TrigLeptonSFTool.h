// Dear emacs, this is -*- c++ -*-
// $Id: HSG3TrigLeptonSFTool.h 497073 2012-04-21 17:20:58Z krasznaa $
#ifndef TRIGMUONEFFICIENCY_HSG3TrigLeptonSFTool_H
#define TRIGMUONEFFICIENCY_HSG3TrigLeptonSFTool_H

// STL include(s):
#include <utility>

// ROOT include(s):
#include "Rtypes.h"

// Forward declaration(s):
class TString;
class TLorentzVector;
class LeptonTriggerSF;

/**
 *  @short Short description for the class
 *
 *         Longer description for the class...
 *
 * $Revision: 497073 $
 * $Date: 2012-04-21 19:20:58 +0200 (Sat, 21 Apr 2012) $
 */
class HSG3TrigLeptonSFTool {

public:
   HSG3TrigLeptonSFTool( const TString& dir, Double_t intLumiJ, Double_t intLumiK,
                         Double_t intLumiL, Double_t intLumiM );
   ~HSG3TrigLeptonSFTool();

   Double_t MuEff_CB_HSG3( const TString& period, Bool_t isData, const TLorentzVector& muon ) const;
   std::pair< Double_t, Double_t >
   MuEffErr_CB_HSG3( const TString& period, Bool_t isData, const TLorentzVector& muon ) const;

private:
   LeptonTriggerSF* fLeptonTriggerSF;

   Double_t fIntLumiJ;
   Double_t fIntLumiK;
   Double_t fIntLumiL;
   Double_t fIntLumiM;

}; // class HSG3TrigLeptonSFTool

#endif // TRIGMUONEFFICIENCY_HSG3TrigLeptonSFTool_H
