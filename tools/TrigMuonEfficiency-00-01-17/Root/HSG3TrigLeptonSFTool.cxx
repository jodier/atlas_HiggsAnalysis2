// $Id: HSG3TrigLeptonSFTool.cxx 497073 2012-04-21 17:20:58Z krasznaa $

// ROOT include(s):
#include "TString.h"
#include "TError.h"

// Local include(s):
#include "TrigMuonEfficiency/HSG3TrigLeptonSFTool.h"
#include "TrigMuonEfficiency/LeptonTriggerSF.h"

HSG3TrigLeptonSFTool::HSG3TrigLeptonSFTool( const TString& dir,
                                            Double_t intLumiJ = 226.391, 
                                            Double_t intLumiK = 590.36, 
                                            Double_t intLumiL = 1404.79, 
                                            Double_t intLumiM = 1026.94 )
 : fLeptonTriggerSF( new LeptonTriggerSF( dir ) ),
   fIntLumiJ( intLumiJ ), fIntLumiK( intLumiK ),
   fIntLumiL( intLumiL ), fIntLumiM( intLumiM ) {

   ::Info( "HSG3TrigLeptonSFTool::HSG3TrigLeptonSFTool", "Initialized" );
}

HSG3TrigLeptonSFTool::~HSG3TrigLeptonSFTool() {

   delete fLeptonTriggerSF;
}

Double_t HSG3TrigLeptonSFTool::MuEff_CB_HSG3( const TString& /*period*/, Bool_t /*isData*/,
                                              const TLorentzVector& /*muon*/ ) const{

   Double_t efficiency = 0;

  /*  if( period == "per2011B2_I" ) {
    efficiency = fLeptonTriggerSF->MuEff_CB( per2011B2_I, isData, muon);
  }else if( period == "per2011J_M" ) {
    efficiency = fLeptonTriggerSF->MuEff_CB( per2011J_M, isData, muon);
  }else if( period == "per2011J" ) {
    efficiency = fLeptonTriggerSF->MuEff_CB( per2011J, isData, muon);
  }else if( period == "per2011K" ) {
    efficiency = fLeptonTriggerSF->MuEff_CB( per2011K, isData, muon);
  }else if( period == "per2011J_K" ) {
    Double_t eff1 = fLeptonTriggerSF->MuEff_CB( per2011J, isData, muon);
    Double_t eff2 = fLeptonTriggerSF->MuEff_CB( per2011K, isData, muon);
    efficiency = (fIntLumiJ*eff1 + fIntLumiK*eff2)/(fIntLumiJ + fIntLumiK); 
  }else if( period == "per2011L_M" ) {
    Double_t eff1 = fLeptonTriggerSF->MuEff_CB( per2011L, isData, muon);
    Double_t eff2 = fLeptonTriggerSF->MuEff_CB( per2011M, isData, muon);
    efficiency = (fIntLumiL*eff1 + fIntLumiM*eff2)/(fIntLumiL + fIntLumiM); 
    }*/

   return efficiency;
}

std::pair< Double_t, Double_t >
HSG3TrigLeptonSFTool::MuEffErr_CB_HSG3( const TString& period, Bool_t isData,
                                        const TLorentzVector& muon ) const{

   Double_t efficiency = 0;
   Double_t error = 0;

   if( period == "per2011B2_I" ) {
      efficiency = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011B_I, isData, muon, combined ).first;
      error      = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011B_I, isData, muon, combined ).second;
   } else if( period == "per2011J_M" ) {
      efficiency = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011J_M, isData, muon, combined ).first;
      error      = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011J_M, isData, muon, combined ).second;
   } else if( period == "per2011J" ) {
      efficiency = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011J, isData, muon, combined ).first;
      error      = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011J, isData, muon, combined ).second;
   } else if( period == "per2011K" ) {
      efficiency = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011K, isData, muon, combined ).first;
      error      = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011K, isData, muon, combined ).second;
   } else if( period == "per2011J_K" ) {
      efficiency = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011J_K, isData, muon, combined ).first;
      error      = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011J_K, isData, muon, combined ).second;
   } else if( period == "per2011L_M" ) {
      efficiency = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011L_M, isData, muon, combined ).first;
      error      = fLeptonTriggerSF->MuEff( TrigMuonEff::per2011L_M, isData, muon, combined ).second;
   } else {
      ::Error( "HSG3TrigLeptonSFTool::MuEffErr_CB_HSG3",
               "Period name (\"%s\") not recognized", period.Data() );
   }

   return std::make_pair( efficiency, error );
}
