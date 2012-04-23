/////////////////////////////////////////////////////////////////////////////////////
//  Trigger Scale Factor (SF) Tool for multilepton (muons and electrons) analyses  //
/////////////////////////////////////////////////////////////////////////////////////
//  Marilyn Marx (marx@cern.ch)                                                    //
//  Junjie Zhu (junjie@umich.edu)                                                  //
/////////////////////////////////////////////////////////////////////////////////////
// How to use:
//
// pair<double, double> GetTriggerSF(int runnumber, bool useGeV, vector<TLorentzVector> muons, muon_quality q, vector<TLorentzVector> electrons, electron_quality p, int var)
//
// where runnumber is an int associating to a real data runnumber in mc,                                
// useGeV is a bool you set depending on whether quantities are in MeV (useGeV=false) or GeV (useGeV=true) in your code,
// vector<TLorentzVector> should be filled (separately for muons and electrons) with all good leptons passing your object selection cuts,
// (N.B. make sure CLUSTER eta is used in the electron TLorentzVector)
// muon_quality is an enum, for q enter either loose or combined,
// electron_quality is an enum, for p enter either loosepp, mediumpp or tightpp.
// var is an int for systematic studies, leave out or set to 0 for central SF, set to 1 or 2 for +1 or -1 sigma variation on the SF
//
// GetTriggerSF().first returns the event SF
// GetTriggerSF().second returns the uncertainty (stat and syst) on the event SF
//
// Note for analyses that use different lepton qualities for different leptons, use:
// pair<double, double> GetTriggerSF(int runnumber, bool useGeV, vector<TLorentzVector> muons, vector<muon_quality> vecq, vector<TLorentzVector> electrons, vector<electron_quality> vecp, int var)
/////////////////////////////////////////////////////////////////////////////////////

// STL include(s):
#include <stdexcept>

// ROOT include(s):
#include "TFile.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TError.h"
#include "TDirectory.h"
#include "TH2.h"

// RootCore include(s):
#include "egammaAnalysisUtils/egammaSFclass.h"

// Local include(s):
#include "TrigMuonEfficiency/LeptonTriggerSF.h"

//
// Constant declaration(s):
//
static const Double_t commonSystMTSG = 0.01;

/// Helper macro for printing nice error messages
/**
 * This macro is used to print some pretty error messages that specify
 * the file name and line number. This can be very useful when debugging
 * problems.
 *
 * It can be placed into a ROOT print function like this:
 *
 * <code>
 *  ::Error( "ThisFunction", ERROR_MESSAGE( "My message with an int %i" ), myInt );
 * </code>
 *
 * @param MESSAGE The message to "make pretty"
 */
#define ERROR_MESSAGE( MESSAGE )                \
   "%s:%i " MESSAGE, __FILE__, __LINE__

/**
 * The constructor expects the directory name under which the efficiency file(s) can
 * be found, when running in stand-alone ROOT mode. When running in an Athena job it
 * can try to guess the correct location, but it may need some help even in that case.
 *
 * The path can be any path that ROOT understands, so you can point the tool to a
 * DCAP, XRootD or even a web server if you want to.
 *
 * @param path Path to the efficiency file(s)
 */
LeptonTriggerSF::LeptonTriggerSF( const TString& path )
   : fEfficiencyMap(), fPhiBoundaryBarrel( 0.0 ), fPhiBoundaryEndcap( 0.0 ),
     fEgammaSF( new egammaSFclass() ) {

   //
   // Try to find the correct path to use:
   //
   TString filePath = path;
   if( filePath == "" ) { // default to InstallArea/share for the files if running in Athena
      const char *tmparea = gSystem->Getenv( "TestArea" );
      if( tmparea ) {
         filePath = TString( tmparea ) + "/InstallArea/share/";
         ::Info( "LeptonTriggerSF::LeptonTriggerSF",
                 "Using default directory: %s", filePath.Data() );
      } else {
         ::Warning( "LeptonTriggerSF::LeptonTriggerSF",
                    "You are not running in Athena but also did not set a path to the root file." );
      }
   } else {
      ::Info( "LeptonTriggerSF::LeptonTriggerSF",
              "Using user defined path: %s", filePath.Data() );
   }

   // Initialize the tool with this path:
   Initialize( filePath );
}

/**
 * The destructor needs to remove the histograms from memory, that we put there
 * in the initialization.
 */
LeptonTriggerSF::~LeptonTriggerSF() {

   // Delete all the histograms from memory:
   std::map< TString, TH2* >::iterator itr = fEfficiencyMap.begin();
   std::map< TString, TH2* >::iterator end = fEfficiencyMap.end();
   for( ; itr != end; ++itr ) {
      delete itr->second;
   }

   // Delete the egamma tool:
   delete fEgammaSF;
}

/// Function that returns per event trigger SF
std::pair< Double_t, Double_t >
LeptonTriggerSF::GetTriggerSF( Int_t runnumber, Bool_t useGeV,
                               const std::vector< TLorentzVector >& muons, muon_quality q,
                               const std::vector< TLorentzVector >& electrons, electron_quality p,
                               Int_t var ) const {

   // Create lepton quality vectors of the size of the TLV vectors:
   std::vector< muon_quality > muonq( muons.size(), q );
   std::vector< electron_quality > eleq( electrons.size(), p );

   // Call the other, more general function:
   return GetTriggerSF( runnumber, useGeV, muons, muonq, electrons, eleq, var );
}

/// Function that returns per event trigger SF when different lepton qualities per event are needed
std::pair< Double_t, Double_t >
LeptonTriggerSF::GetTriggerSF( Int_t runnumber, Bool_t useGeV,
                               const std::vector< TLorentzVector >& muons,
                               const std::vector< muon_quality >& muonq,
                               const std::vector< TLorentzVector >& electrons,
                               const std::vector< electron_quality >& eleq,
                               Int_t var ) const {

   // Get the period corresponding to the specified run number:
   const TrigMuonEff::SFDataPeriod period = GetDataPeriod( runnumber );
   if( period == TrigMuonEff::perUnDefined ) {
      ::Error( "LeptonTriggerSF::GetTriggerSF",
               ERROR_MESSAGE( "RunNumber is not in 2011 dataset. No scale factors calculated. "
                              "Please use RunNumber between 178044-191933" ) );
      return make_pair( 0., 0. );
   }

   // Get the offline muon and electron thresholds:
   const std::pair< Double_t, Double_t > thr = GetThresholds( useGeV, runnumber );

   Double_t rate_not_fired_data = 1.;
   Double_t rate_not_fired_mc   = 1.;

   // needed for uncertainty calculation
   Double_t sq_err_eff_data    = 0.;
   Double_t sq_err_eff_mc      = 0.;
   Double_t sq_err_eff_data_el = 0.;
   Double_t sq_err_eff_mc_el   = 0.;
   Double_t sq_err_eff_data_mu = 0.;
   Double_t sq_err_eff_mc_mu   = 0.;
   Double_t inv_sq_eff_data    = 0.;
   Double_t inv_sq_eff_mc      = 0.;

   for( size_t ielec = 0; ielec < electrons.size(); ++ielec ) {

      const Int_t set_data = GetElQuality( runnumber, eleq[ ielec ], kTRUE );
      const Int_t set_mc   = GetElQuality( runnumber, eleq[ ielec ], kFALSE );

      Double_t eff_data = 0., eff_mc = 0.;    
      Double_t err_data = 0., err_mc = 0.;    

      if( ( electrons[ ielec ].Pt() < thr.second ) ||
          ( TMath::Abs( electrons[ ielec ].Eta() ) >= 2.47 ) ) {

         eff_data = 0.;
         eff_mc   = 0.;
         err_data = 0.;
         err_mc   = 0.;

      } else {

         // get efficiency from data
         eff_data = ElEff_Data( electrons[ ielec ], set_mc, set_data, useGeV ).first;
         err_data = ElEff_Data( electrons[ ielec ], set_mc, set_data, useGeV ).second;
         // get efficiency from MC
         eff_mc = ElEff_MC( electrons[ ielec ], set_mc, useGeV ).first;
         err_mc = ElEff_MC( electrons[ ielec ], set_mc, useGeV ).second;

      }
    
      rate_not_fired_data *= ( 1 - eff_data );
      rate_not_fired_mc   *= ( 1 - eff_mc );

      // needed for uncertainty calculation
      sq_err_eff_data += TMath::Power( err_data, 2 );
      sq_err_eff_mc   += TMath::Power( err_mc, 2 );
      if( eff_data ) {
         inv_sq_eff_data += TMath::Power( ( 1 - eff_data ), -2 );
      }
      if( eff_mc ) {
         inv_sq_eff_mc += TMath::Power( ( 1 - eff_mc ), -2 );
      }
      // contribution only due to electron trigger
      sq_err_eff_data_el += TMath::Power( err_data, 2 );
      sq_err_eff_mc_el   += TMath::Power( err_mc, 2 );
   }

   for( size_t imuon = 0; imuon < muons.size(); ++imuon ) {

      Double_t eff_data = 0., eff_mc = 0.;
      Double_t err_data = 0., err_mc = 0.;

      if( muons[ imuon ].Pt() < thr.first ) {

         eff_data = 0.;
         eff_mc   = 0.;
         err_data = 0.;
         err_mc   = 0.;

      } else {

         // get efficiency from data
         eff_data = MuEff( period, kTRUE, muons[ imuon ], muonq[ imuon ] ).first;
         err_data = MuEff( period, kTRUE, muons[ imuon ], muonq[ imuon ] ).second;
         // get efficiency from MC
         eff_mc = MuEff( period, kFALSE, muons[ imuon ], muonq[ imuon ] ).first;
         err_mc = MuEff( period, kFALSE, muons[ imuon ], muonq[ imuon ] ).second;

      }

      rate_not_fired_data *= ( 1 - eff_data );
      rate_not_fired_mc   *= ( 1 - eff_mc );

      // needed for uncertainty calculation
      sq_err_eff_data += TMath::Power( err_data, 2 );
      sq_err_eff_mc   += TMath::Power( err_mc, 2 );
      if( eff_data ) {
         inv_sq_eff_data += TMath::Power( ( 1 - eff_data ), -2 );
      }
      if( eff_mc ) {
         inv_sq_eff_mc += TMath::Power( ( 1 - eff_mc ), -2 );
      }
      // contribution only due to muon trigger
      sq_err_eff_data_mu += TMath::Power( err_data, 2 );
      sq_err_eff_mc_mu   += TMath::Power( err_mc, 2 );
   }

   Double_t event_SF = 1.;
   Double_t event_SF_err = 0.;
   Double_t event_SF_err_el = 0.;
   Double_t event_SF_err_mu = 0.;

   // prevent events with no triggered electrons or muons
   if( ( electrons.size() || muons.size() ) && ( TMath::Abs( 1 - rate_not_fired_mc ) > 0.0001 ) ) {

      event_SF        = ( 1 - rate_not_fired_data ) / ( 1 - rate_not_fired_mc );
      event_SF_err    = GetSFError( rate_not_fired_data, rate_not_fired_mc, sq_err_eff_data,
                                    sq_err_eff_mc, inv_sq_eff_data, inv_sq_eff_mc );
      event_SF_err_el = GetSFError( rate_not_fired_data, rate_not_fired_mc, sq_err_eff_data_el,
                                    sq_err_eff_mc_el, inv_sq_eff_data, inv_sq_eff_mc );
      event_SF_err_mu = GetSFError( rate_not_fired_data, rate_not_fired_mc, sq_err_eff_data_mu,
                                    sq_err_eff_mc_mu, inv_sq_eff_data, inv_sq_eff_mc );
   }
  
   if( var == 1 ) {
      return std::make_pair( event_SF + event_SF_err, event_SF_err );
   } else if( var == 2 ) {
      return std::make_pair( event_SF - event_SF_err, event_SF_err ); 
   } else if( var == 3 ) {
      return std::make_pair( event_SF + event_SF_err_el, event_SF_err ); 
   } else if( var == 4 ) {
      return std::make_pair( event_SF - event_SF_err_el, event_SF_err); 
   } else if( var == 5 ) {
      return std::make_pair( event_SF + event_SF_err_mu, event_SF_err); 
   } else if( var == 6 ) {
      return std::make_pair( event_SF - event_SF_err_mu, event_SF_err); 
   } else {
      return std::make_pair( event_SF, event_SF_err ); 
   }
}

/// Muon efficiencies
std::pair< Double_t, Double_t >
LeptonTriggerSF::MuEff( TrigMuonEff::SFDataPeriod period, Bool_t isData, const TLorentzVector& muon,
                        muon_quality mu_quality ) const {

   const Double_t mu_eta = muon.Eta();
   Double_t mu_phi = CheckPhiRange( muon.Phi() );

   // fix phi range for unusual binning
   if( TMath::Abs( mu_eta ) < 1.05 ) {
      if( fPhiBoundaryBarrel < 0. ) {
         if( mu_phi < fPhiBoundaryBarrel )  mu_phi += 2 * TMath::Pi(); 
      } else {
         if( mu_phi >= fPhiBoundaryBarrel ) mu_phi -= 2 * TMath::Pi(); 
      }
   } else{
      if( fPhiBoundaryEndcap < 0. ) {
         if( mu_phi < fPhiBoundaryEndcap )  mu_phi += 2 * TMath::Pi(); 
      } else {
         if( mu_phi >= fPhiBoundaryEndcap ) mu_phi -= 2 * TMath::Pi(); 
      }
   }

   const TString type = ( isData ? "_data" : "_mc" );
   const TString region = ( ( TMath::Abs( mu_eta ) < 1.05 ) ? "_barrel" : "_endcap" );
   TString dataperiod, bins;
   switch( period ) {
   case TrigMuonEff::per2011B_I:
      dataperiod = "BtoI_";
      bins       = "fine";
      break;
   case TrigMuonEff::per2011J_MwoL3_L4:
      dataperiod = "JtoMwoL3toL4_";
      bins       = "fine";
      break;
   case TrigMuonEff::per2011L3_L4:
      dataperiod = "L3toL4_";
      bins       = "coarse";
      break;
   case TrigMuonEff::per2011J:
      dataperiod = "J_";
      bins       = "coarse";
      break;
   case TrigMuonEff::per2011K:
      dataperiod = "K_";
      bins       = "coarse";
      break;
   case TrigMuonEff::per2011J_K:
      dataperiod = "JtoK_";
      bins       = "coarse";
      break;
   case TrigMuonEff::per2011J_M:
      dataperiod = "JtoM_";
      bins       = "coarse";
      break;
   case TrigMuonEff::per2011L_M:
      dataperiod = "LtoM_";
      bins       = "coarse";
      break;
   default:
      ::Error( "LeptonTriggerSF::MuEff",
               ERROR_MESSAGE( "Unknown data period (%i) requested, using the B-I period" ),
               period );
      dataperiod = "BtoI_";
      bins       = "fine";
      break;
   }
   const TString quality = GetMuQuality( mu_quality );

   const TString histname = "_MuonTrigEff_" + dataperiod + quality + "_EtaPhi_" + bins + region + type;
   std::map< TString, TH2* >::const_iterator mapit = fEfficiencyMap.find( histname );
   if( mapit == fEfficiencyMap.end() ) {
      ::Fatal( "LeptonTriggerSF::MuEff",
               "Could not find what you are looking for in the efficiency map. This is a bug." );
      throw std::runtime_error( "Internal coding error detected" );
   }
   const Int_t bin  = mapit->second->FindBin( mu_eta, mu_phi );
   const Double_t eff  = mapit->second->GetBinContent( bin );
   const Double_t stat = mapit->second->GetBinError( bin );
  
   const Double_t syst = commonSystMTSG * eff;
   const Double_t err  = TMath::Sqrt( TMath::Power( stat, 2 ) + TMath::Power( syst, 2 ) );

   return std::make_pair( eff, err );
}

/// Electron efficiencies
std::pair< Double_t, Double_t >
LeptonTriggerSF::ElEff_MC( const TLorentzVector& electron, Int_t set_mc, Bool_t useGeV ) const {

   const Double_t el_eta = electron.Eta();
   Double_t el_ET = electron.Pt();
   if( useGeV ) el_ET *= 1000.0;

   const std::pair< float, float > mc_eff_error =
      fEgammaSF->scaleFactor( el_eta, el_ET, set_mc, 0, 6, 1 );

   return std::pair< Double_t, Double_t >( mc_eff_error.first, mc_eff_error.second );
}

std::pair< Double_t, Double_t >
LeptonTriggerSF::ElEff_Data( const TLorentzVector& electron, Int_t set_mc, Int_t set_data,
                             Bool_t useGeV ) const {

   const Double_t el_eta = electron.Eta();
   Double_t el_ET = electron.Pt();
   if( useGeV ) el_ET *= 1000.0;

   const std::pair< float, float > mc_eff_error =
      fEgammaSF->scaleFactor( el_eta, el_ET, set_mc, 0, 6, 1 );
   const std::pair< float, float > sf_error =
      fEgammaSF->scaleFactor( el_eta, el_ET, set_data, 0, 6, 1 );

   const Double_t eff = mc_eff_error.first * sf_error.first;
   const Double_t err = eff * ( TMath::Sqrt( TMath::Power( mc_eff_error.second / mc_eff_error.first, 2 ) +
                                             TMath::Power( sf_error.second / sf_error.first, 2 ) ) );

   return std::make_pair( eff, err );
}

/**
 * The initialization takes care of reading in all the efficiency histograms from the ROOT
 * file found in the package. It makes a copy of every histogram in memory, and takes
 * ownership of them. It then needs to delete each one of them in its destructor.
 *
 * @param path The path under which to search for the efficiency file(s)
 */
void LeptonTriggerSF::Initialize( const TString& path ) {

   // Remember which TDirectory the system is in at the beginning of the function:
   TDirectory* origDir = gDirectory;

   // Open the efficiency file:
   TFile* file = TFile::Open( path + "/muon_trigger_sf.root" );
   if( ! file ) {
      ::Fatal( "LeptonTriggerSF::Initialize",
               ERROR_MESSAGE( "Couldn't open file \"%s\"" ),
               ( path + "/muon_trigger_sf.root" ).Data() );
      throw std::runtime_error( ( "Couldn't open file \"" + path +
                                  "/muon_trigger_sf.root\"" ).Data() );
   }
   ::Info( "LeptonTriggerSF::Initialize",
           "File \"%s\" opened", file->GetName() );

   //
   // Constants used in the file reading:
   //
   static const unsigned int nperiods = 8;
   static const TString quality[ 2 ] = { "loose", "combined" };
   static const TString bins[ 2 ]    = { "fine", "coarse" };
   static const TString type[ 2 ]    = { "data", "mc" };
   static const TString region[ 2 ]  = { "barrel", "endcap" };
   static const TString trigger[ 8 ] = { "mu18_MG", "mu18_MG_medium", "mu18_MG_medium",
                                         "mu18_MG_medium", "mu18_MG_medium", "mu18_MG_medium",
                                         "mu18_MG_medium", "mu18_MG_medium" };
   static const TString periods[ 8 ] = { "BtoI", "JtoMwoL3toL4", "L3toL4", "J", "K", "JtoK",
                                         "JtoM", "LtoM" };

   //
   // Create a unique directory in memory to hold the histograms:
   //
   gROOT->cd();
   TDirectory* tempDir = 0;
   Int_t counter = 0;
   while( ! tempDir ) {
      // First, let's find a directory name that doesn't exist yet:
      TString dirname = TString::Format( "LeptonTriggerSFTempDir_%i", counter );
      if( gROOT->GetDirectory( dirname ) ) {
         ++counter;
         continue;
      }
      // Let's try to make this directory:
      tempDir = gROOT->mkdir( dirname );
      if( ! tempDir ) {
         ::Fatal( "LeptonTriggerSF::Initialize",
                  ERROR_MESSAGE( "Temporary directory could not be created" ) );
         throw std::runtime_error( "Temporary directory could not be created" );
      }
   }
   tempDir->cd();

   //
   // Read in the histograms:
   //
   for( unsigned int iqu = 0; iqu < 2; ++iqu ) {
      for( unsigned int ibins = 0; ibins < 2; ++ibins ) {
         for( unsigned int iperiod = 0; iperiod < nperiods; ++iperiod ) {
            for( unsigned int iregion = 0; iregion < 2; ++iregion ) {
               for( unsigned int itype = 0; itype < 2; ++itype ) {

                  // Construct the histogram name:
                  TString histname = ( "_MuonTrigEff_" + periods[ iperiod ] + "_" + quality[ iqu ] +
                                       "_EtaPhi_" + bins[ ibins ] + "_" + region[ iregion ] + "_" +
                                       type[ itype ] );
                  // Try to access the histogram:
                  TH2* hist = dynamic_cast< TH2* >( file->Get( ( quality[ iqu ] + "/" + bins[ ibins ] + "/" +
                                                                 trigger[ iperiod ] + "_" + periods[ iperiod ] +
                                                                 "/etaphi_" + region[ iregion ] + "_eff_" +
                                                                 type[ itype ] + "_period" + periods[ iperiod ] +
                                                                 "_EF_" + trigger[ iperiod ] ).Data() ) );
                  if( ! hist ) {
                     ::Fatal( "LeptonTriggerSF::Initialize",
                              ERROR_MESSAGE( "Couldn't read in histogram with name \"%s\"" ),
                              histname.Data() );
                     throw std::runtime_error( ( "Couldn't read in histogram with name " +
                                                 histname ).Data() );
                  }
                  // Make a copy of the histogram into the in-memory directory:
                  TH2* hcopy = dynamic_cast< TH2* >( hist->Clone() );
                  if( ! hcopy ) {
                     ::Fatal( "LeptonTriggerSF::Initialize",
                              ERROR_MESSAGE( "Couldn't make copy of histogram \"%s\"" ),
                              histname.Data() );
                     throw std::runtime_error( ( "Couldn't make copy of histogram " +
                                                 histname ).Data() );
                  }

                  // Now, remember this histogram:
                  fEfficiencyMap[ histname ] = hcopy;
               }
            }
         }
      }
   }

   // Now we can close the file:
   file->Close();
   delete file;

   // Return to the directory we were in before the function call:
   origDir->cd();

   //
   // Set the phi boundaries:
   //
   fPhiBoundaryBarrel = TMath::Pi();
   fPhiBoundaryEndcap = TMath::Pi();
   std::map< TString, TH2* >::const_iterator itr = fEfficiencyMap.begin();
   std::map< TString, TH2* >::const_iterator end = fEfficiencyMap.end();
   for( ; itr != end; ++itr ){
      if( ! itr->second ) {
         ::Fatal( "LeptonTriggerSF::Initialize",
                  ERROR_MESSAGE( "An internal coding error detected" ) );
         throw std::runtime_error( "An internal coding error detected" );
      }
      // setting lower phi to account for unusual binning
      if( itr->first.Contains( "_MuonTrigEff_JtoMwoL3toL4_loose_EtaPhi_fine_barrel_data" ) ) {
         fPhiBoundaryBarrel = itr->second->GetYaxis()->GetXmin();
      } 
      if( itr->first.Contains( "_MuonTrigEff_JtoMwoL3toL4_loose_EtaPhi_fine_endcap_data" ) ) {
         fPhiBoundaryEndcap = itr->second->GetYaxis()->GetXmin();
      }
      if( fPhiBoundaryBarrel < -TMath::Pi() ) fPhiBoundaryBarrel += 2. * TMath::Pi();
      if( fPhiBoundaryEndcap < -TMath::Pi() ) fPhiBoundaryEndcap += 2. * TMath::Pi();
   }

   ::Info( "LeptonTriggerSF::Initialize",
           "Initialization successful" );

   return;
}

/// Other helper functions
TString LeptonTriggerSF::GetMuQuality( muon_quality mu_quality ) {

   TString mu_q;
   switch( mu_quality ) {
   case loose:
      mu_q = "loose";
      break;
   case combined:
      mu_q = "combined";
      break;
   default:
      ::Error( "LeptonTriggerSF::GetMuQuality",
               ERROR_MESSAGE( "Unknown muon quality (%i) received; Using loose muon as default" ),
               mu_quality );
      mu_q = "loose";
      break;
   }

   return mu_q;
}

Int_t LeptonTriggerSF::GetElQuality( Int_t runnumber, electron_quality el_quality, Bool_t isSF ) {

   Int_t set = 0;

   if( runnumber <= 186755 ) { // e20_medium
      // loose++
      if( el_quality == loosepp ) {
         if( isSF ) set = 27;
         else       set = 20;
      }
      // medium++
      else if( el_quality == mediumpp ) {
         if( isSF ) set = 8;
         else       set = 9;
      }
      // tight++
      else if( el_quality == tightpp ) {
         if( isSF ) set = 10;
         else       set = 11;
      } else {
         ::Error( "LeptonTriggerSF::GetElQuality",
                  ERROR_MESSAGE( "Unknown electron quality (%i) received; Using loose++ electron "
                                 "as default" ),
                  el_quality );
         if( isSF ) set = 27;
         else       set = 20;
      }
   }
   else if( runnumber <= 187815 ) { // e22_medium
      if( el_quality == loosepp ) {
         if( isSF ) set = 28;
         else       set = 21;
      }
      else if( el_quality == mediumpp ) {
         if( isSF ) set = 12;
         else       set = 13;
      }
      else if( el_quality == tightpp ) {
         if( isSF ) set = 14;
         else       set = 15;
      } else {
         ::Error( "LeptonTriggerSF::GetElQuality",
                  ERROR_MESSAGE( "Unknown electron quality (%i) received; Using loose++ electron "
                                 "as default" ),
                  el_quality );
         if( isSF ) set = 28;
         else       set = 21;
      }
   }
   else if( runnumber <= 191933 ) { // e22vh_medium1
      if( el_quality == loosepp ) {
         if( isSF ) set = 29;
         else       set = 22;
      }
      else if( el_quality == mediumpp ) {
         if( isSF ) set = 16;
         else       set = 17;
      }
      else if( el_quality == tightpp ) {
         if( isSF ) set = 18;
         else       set = 19;
      } else {
         ::Error( "LeptonTriggerSF::GetElQuality",
                  ERROR_MESSAGE( "Unknown electron quality (%i) received; Using loose++ electron "
                                 "as default" ),
                  el_quality );
         if( isSF ) set = 29;
         else       set = 22;
      }
   }
   else {
      ::Error( "LeptonTriggerSF::GetElQuality",
               ERROR_MESSAGE( "Bad run number (%i) received" ), runnumber );
   }

   return set;
}

// Function setting trigger thresholds for muons and electrons
std::pair< Double_t, Double_t >
LeptonTriggerSF::GetThresholds( Bool_t useGeV, Int_t runnumber ) {

   std::pair< Double_t, Double_t > result( 20., 21. );
   if( runnumber <= 186755 ) result.second = 21.;
   else if( runnumber <= 191933 ) result.second = 23.;
   else {
      ::Error( "LeptonTriggerSF::SetThresholds",
               ERROR_MESSAGE( "Unknown run number (%i) received" ), runnumber );
      return result;
   }

   if( ! useGeV ) {
      result.first  *= 1000.;
      result.second *= 1000.;
   }

   return result;
}

// Function to decide period from run number
TrigMuonEff::SFDataPeriod LeptonTriggerSF::GetDataPeriod( Int_t runNumber ) {

   if( runNumber < 178044 ) return TrigMuonEff::perUnDefined;
   if( runNumber <= 186493 ) return TrigMuonEff::per2011B_I;
   if( ( runNumber <= 189090 ) ||
       ( runNumber >= 189639 && runNumber <= 191933 ) ) return TrigMuonEff::per2011J_MwoL3_L4;
   if( ( runNumber >= 189184 ) && ( runNumber <= 189610 ) ) return TrigMuonEff::per2011L3_L4;

   ::Error( "LeptonTriggerSF::GetDataPeriod",
            ERROR_MESSAGE( "Can't associate run number (%i) to a period" ), runNumber );
   return TrigMuonEff::perUnDefined;
}

// Function to deal with possible phi ambiguity
Double_t LeptonTriggerSF::CheckPhiRange( Double_t phi ) {

   Double_t newphi = phi;

   if( newphi > TMath::Pi() ) {
      ::Warning( "LeptonTriggerSF::CheckPhiRange",
                 "Muon phi %4.2f > pi! Using (phi-2*pi)", phi );
      newphi -= 2 * TMath::Pi();
   }
   if( newphi < -TMath::Pi() ) {
      ::Warning( "LeptonTriggerSF::CheckPhiRange",
                 "Muon phi %4.2f < -pi! Using (phi+2*pi)", phi );
      newphi += 2 * TMath::Pi();
   }

   return newphi;
}

// Function to calculate uncertainty on SF
Double_t LeptonTriggerSF::GetSFError( Double_t a, Double_t b, Double_t c, Double_t d, Double_t e,
                                      Double_t f ) {

   return TMath::Sqrt( ( TMath::Power( a, 2 ) / TMath::Power( 1 - b, 2 ) ) * c * e +
                       ( ( TMath::Power( b, 2 ) * TMath::Power( 1 - a, 2 ) ) /
                         ( TMath::Power( 1 - b, 4 ) ) ) * d * f );
}
