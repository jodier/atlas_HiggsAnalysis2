// Dear emacs, this is -*- c++ -*-
// $Id: LeptonTriggerSF.h 497071 2012-04-21 16:19:48Z krasznaa $
#ifndef TRIGMUONEFFICIENCY_LEPTONTRIGGERSF_H
#define TRIGMUONEFFICIENCY_LEPTONTRIGGERSF_H

// STL include(s):
#include <vector>
#include <map>

// ROOT include(s):
#include "TString.h"
#include "TLorentzVector.h"

// Forward declaration(s):
class egammaSFclass;
class TH2;

namespace TrigMuonEff {
   /// Helper enumeration defining the data periods understood by the tool
   enum SFDataPeriod {
      perUnDefined      = -1,
      per2011B_I        = 0, 
      per2011J_MwoL3_L4 = 1, 
      per2011L3_L4      = 2,

      //for HSG3 specific use
      per2011J   = 3,
      per2011K   = 4,
      per2011J_K = 5,
      per2011J_M = 6,
      per2011L_M = 7
   };
}

/// Helper enumeration defining the muon quality types
enum muon_quality {
   loose    = 0,
   combined = 1
};

/// Helper enumeration defining the electron quality types
enum electron_quality {
   loosepp  = 0,
   mediumpp = 1,
   tightpp  = 2
};

/**
 *  @short Class providing trigger scale factors for analyses using electrons and muons
 *
 *         This tool can be used to get the scale factors and their uncertainties in
 *         events with multiple electrons/muons.
 *
 * @author Marilyn Marx <marx@cern.ch>
 * @author Junjie Zhu   <junjie@umich.edu>
 *
 * $Revision: 497071 $
 * $Date: 2012-04-21 18:19:48 +0200 (Sat, 21 Apr 2012) $
 */
class LeptonTriggerSF {

public:
   /// Constructor, taking a possible path for the ROOT file location
   LeptonTriggerSF( const TString& path = "" );
   /// Destructor
   ~LeptonTriggerSF();

   /// Function getting the scale factor for leptons of uniform quality
   std::pair< Double_t, Double_t >
   GetTriggerSF( Int_t runnumber, Bool_t useGeV, const std::vector< TLorentzVector >& muons, muon_quality q,
                 const std::vector< TLorentzVector >& electrons, electron_quality p, Int_t var = 0 ) const;
   /// Function getting the scale factor for leptons of varying quality
   std::pair< Double_t, Double_t >
   GetTriggerSF( Int_t runnumber, Bool_t useGeV,
                 const std::vector< TLorentzVector >& muons, const std::vector< muon_quality >& vecq,
                 const std::vector< TLorentzVector >& electrons, const std::vector< electron_quality >& vecp,
                 Int_t var = 0 ) const;

   /// Function returning the trigger efficiency for a single muon
   std::pair< Double_t, Double_t >
   MuEff( TrigMuonEff::SFDataPeriod period, Bool_t isData, const TLorentzVector& muon,
          muon_quality mu_quality ) const;
   /// Function returning the trigger efficiency for a single electron, on Monte Carlo
   std::pair< Double_t, Double_t >
   ElEff_MC( const TLorentzVector& electron, Int_t set_mc, Bool_t useGeV = kFALSE ) const;
   /// Function returning the trigger efficiency for a single electron, on data
   std::pair< Double_t, Double_t >
   ElEff_Data( const TLorentzVector& electron, Int_t set_mc, Int_t set_data,
               Bool_t useGeV = kFALSE ) const;

private:
   /// Function initializing the tool on construction
   void Initialize( const TString& path );

   /// Translate the muon quality enumeration into a value used internally by the tool
   static TString GetMuQuality( muon_quality mu_q );
   /// Translate the electron quality enumeration into a value used internally by the tool
   static Int_t GetElQuality( Int_t runnumber, electron_quality el_quality, Bool_t isSF );
   /// Get the minimum offline electron and muon pT thresholds for a given run
   static std::pair< Double_t, Double_t >
   GetThresholds( Bool_t useGeV, Int_t runnumber );
   /// Translate a run number to a data period
   static TrigMuonEff::SFDataPeriod GetDataPeriod( Int_t runNumber );
   /// Translate a phi value into the ATLAS [-pi,pi] frame
   static Double_t CheckPhiRange( Double_t phi );
   /// Function to calculate the uncertainty on the SF
   static Double_t GetSFError( Double_t a, Double_t b, Double_t c, Double_t d, Double_t e,
                               Double_t f );

   std::map< TString, TH2* > fEfficiencyMap; ///< The main efficiency storage location

   Double_t fPhiBoundaryBarrel; ///< Muon phi boundary in the barrel region
   Double_t fPhiBoundaryEndcap; ///< Muon phi boundary in the endcap region

   mutable egammaSFclass* fEgammaSF; ///< Helper class providing the electron scale factors

}; // class LeptonTriggerSF

#endif // TRIGMUONEFFICIENCY_LEPTONTRIGGERSF_H
