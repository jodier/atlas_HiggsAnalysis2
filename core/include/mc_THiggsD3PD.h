//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 29 13:02:16 2012 by ROOT version 5.28/00b
// from TTree physics/physics
// found on file: result.root
//////////////////////////////////////////////////////////

#ifndef THiggsD3PD_h
#define THiggsD3PD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#define __IS_MC

class THiggsD3PD {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Bool_t          EF_2e12T_medium;
   Bool_t          EF_2e12_medium;
   Bool_t          EF_2e15_medium;
   Bool_t          EF_2mu10_loose;
   Bool_t          EF_e10_medium_mu10;
   Bool_t          EF_e10_medium_mu6;
   Bool_t          EF_e20_medium;
   Bool_t          EF_e22_medium;
   Bool_t          EF_e22_medium1;
   Bool_t          EF_mu10;
   Bool_t          EF_mu15_mu10_EFFS;
   Bool_t          EF_mu15_mu10_EFFS_medium;
   Bool_t          EF_mu18;
   Bool_t          EF_mu18_MG;
   Bool_t          EF_mu18_MG_medium;
   Bool_t          EF_mu20;
   Bool_t          EF_mu20_MG;
   Bool_t          EF_mu20_MG_medium;
   Bool_t          EF_mu22;
   Bool_t          EF_mu22_MG;
   Bool_t          EF_mu22_MG_medium;
   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          lbn;
   Float_t         actualIntPerXing;
   Float_t         averageIntPerXing;
   UInt_t          mc_channel_number;
   UInt_t          larError;
   Int_t           el_n;
   std::vector<float>   *el_charge;
   std::vector<int>     *el_author;
   std::vector<unsigned int> *el_OQ;
   std::vector<int>     *el_medium;
   std::vector<int>     *el_tight;
   std::vector<int>     *el_loosePP;
   std::vector<float>   *el_Ethad;
   std::vector<float>   *el_Ethad1;
   std::vector<float>   *el_f1;
   std::vector<float>   *el_Emax2;
   std::vector<float>   *el_wstot;
   std::vector<float>   *el_emaxs1;
   std::vector<float>   *el_weta2;
   std::vector<float>   *el_Etcone20;
   std::vector<float>   *el_Etcone30;
   std::vector<float>   *el_ptcone20;
   std::vector<float>   *el_ptcone30;
   std::vector<float>   *el_deltaeta1;
   std::vector<float>   *el_reta;
   std::vector<float>   *el_rphi;
   std::vector<float>   *el_etap;
   std::vector<float>   *el_etas2;
   std::vector<float>   *el_cl_E;
   std::vector<float>   *el_cl_pt;
   std::vector<float>   *el_cl_eta;
   std::vector<float>   *el_cl_phi;
   std::vector<float>   *el_trackd0;
   std::vector<float>   *el_trackz0;
   std::vector<float>   *el_trackphi;
   std::vector<float>   *el_tracktheta;
   std::vector<float>   *el_trackqoverp;
   std::vector<float>   *el_trackpt;
   std::vector<float>   *el_tracketa;
   std::vector<int>     *el_nBLHits;
   std::vector<int>     *el_nPixHits;
   std::vector<int>     *el_nSCTHits;
   std::vector<int>     *el_nTRTHits;
   std::vector<int>     *el_nTRTHighTHits;
   std::vector<int>     *el_nBLayerOutliers;
   std::vector<int>     *el_nPixelOutliers;
   std::vector<int>     *el_nSCTOutliers;
   std::vector<int>     *el_nTRTOutliers;
   std::vector<int>     *el_nTRTHighTOutliers;
   std::vector<int>     *el_nSiHits;
   std::vector<float>   *el_trackd0pvunbiased;
   std::vector<float>   *el_trackz0pvunbiased;
   std::vector<float>   *el_tracksigd0pvunbiased;
   std::vector<int>     *el_EF_index;
   std::vector<int>     *el_type;
   std::vector<int>     *el_origin;
   std::vector<int>     *el_typebkg;
   std::vector<int>     *el_originbkg;
   std::vector<int>     *el_truth_type;
   std::vector<int>     *el_truth_mothertype;
   Int_t           mu_muid_n;
   std::vector<float>   *mu_muid_E;
   std::vector<float>   *mu_muid_pt;
   std::vector<float>   *mu_muid_eta;
   std::vector<float>   *mu_muid_phi;
   std::vector<float>   *mu_muid_charge;
   std::vector<int>     *mu_muid_author;
   std::vector<float>   *mu_muid_etcone20;
   std::vector<float>   *mu_muid_etcone30;
   std::vector<float>   *mu_muid_ptcone20;
   std::vector<float>   *mu_muid_ptcone30;
   std::vector<int>     *mu_muid_isStandAloneMuon;
   std::vector<int>     *mu_muid_isCombinedMuon;
   std::vector<int>     *mu_muid_isSegmentTaggedMuon;
   std::vector<int>     *mu_muid_tight;
   std::vector<float>   *mu_muid_d0_exPV;
   std::vector<float>   *mu_muid_z0_exPV;
   std::vector<float>   *mu_muid_id_theta_exPV;
   std::vector<float>   *mu_muid_id_qoverp_exPV;
   std::vector<float>   *mu_muid_me_theta_exPV;
   std::vector<float>   *mu_muid_me_qoverp_exPV;
   std::vector<float>   *mu_muid_id_d0;
   std::vector<float>   *mu_muid_id_z0;
   std::vector<float>   *mu_muid_id_phi;
   std::vector<float>   *mu_muid_id_theta;
   std::vector<float>   *mu_muid_id_qoverp;
   std::vector<int>     *mu_muid_nBLHits;
   std::vector<int>     *mu_muid_nPixHits;
   std::vector<int>     *mu_muid_nSCTHits;
   std::vector<int>     *mu_muid_nTRTHits;
   std::vector<int>     *mu_muid_nPixHoles;
   std::vector<int>     *mu_muid_nSCTHoles;
   std::vector<int>     *mu_muid_nTRTOutliers;
   std::vector<int>     *mu_muid_nPixelDeadSensors;
   std::vector<int>     *mu_muid_nSCTDeadSensors;
   std::vector<int>     *mu_muid_expectBLayerHit;
   std::vector<int>     *mu_muid_nCSCEtaHits;
   std::vector<int>     *mu_muid_nCSCPhiHits;
   std::vector<int>     *mu_muid_nMDTEMHits;
   std::vector<int>     *mu_muid_nMDTEOHits;
   std::vector<float>   *mu_muid_trackIPEstimate_d0_unbiasedpvunbiased;
   std::vector<float>   *mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased;
   std::vector<int>     *mu_muid_truth_type;
   std::vector<int>     *mu_muid_truth_mothertype;
   std::vector<int>     *mu_muid_EFCB_index;
   Int_t           mu_staco_n;
   std::vector<float>   *mu_staco_E;
   std::vector<float>   *mu_staco_pt;
   std::vector<float>   *mu_staco_eta;
   std::vector<float>   *mu_staco_phi;
   std::vector<float>   *mu_staco_charge;
   std::vector<int>     *mu_staco_author;
   std::vector<float>   *mu_staco_etcone20;
   std::vector<float>   *mu_staco_etcone30;
   std::vector<float>   *mu_staco_ptcone20;
   std::vector<float>   *mu_staco_ptcone30;
   std::vector<int>     *mu_staco_isStandAloneMuon;
   std::vector<int>     *mu_staco_isCombinedMuon;
   std::vector<int>     *mu_staco_isSegmentTaggedMuon;
   std::vector<int>     *mu_staco_tight;
   std::vector<float>   *mu_staco_d0_exPV;
   std::vector<float>   *mu_staco_z0_exPV;
   std::vector<float>   *mu_staco_id_theta_exPV;
   std::vector<float>   *mu_staco_id_qoverp_exPV;
   std::vector<float>   *mu_staco_me_theta_exPV;
   std::vector<float>   *mu_staco_me_qoverp_exPV;
   std::vector<float>   *mu_staco_id_d0;
   std::vector<float>   *mu_staco_id_z0;
   std::vector<float>   *mu_staco_id_phi;
   std::vector<float>   *mu_staco_id_theta;
   std::vector<float>   *mu_staco_id_qoverp;
   std::vector<int>     *mu_staco_nBLHits;
   std::vector<int>     *mu_staco_nPixHits;
   std::vector<int>     *mu_staco_nSCTHits;
   std::vector<int>     *mu_staco_nTRTHits;
   std::vector<int>     *mu_staco_nPixHoles;
   std::vector<int>     *mu_staco_nSCTHoles;
   std::vector<int>     *mu_staco_nTRTOutliers;
   std::vector<int>     *mu_staco_nPixelDeadSensors;
   std::vector<int>     *mu_staco_nSCTDeadSensors;
   std::vector<int>     *mu_staco_expectBLayerHit;
   std::vector<int>     *mu_staco_nCSCEtaHits;
   std::vector<int>     *mu_staco_nCSCPhiHits;
   std::vector<int>     *mu_staco_nMDTEMHits;
   std::vector<int>     *mu_staco_nMDTEOHits;
   std::vector<float>   *mu_staco_trackIPEstimate_d0_unbiasedpvunbiased;
   std::vector<float>   *mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased;
   std::vector<int>     *mu_staco_truth_type;
   std::vector<int>     *mu_staco_truth_mothertype;
   std::vector<int>     *mu_staco_EFCB_index;
   Int_t           mu_calo_n;
   std::vector<float>   *mu_calo_E;
   std::vector<float>   *mu_calo_pt;
   std::vector<float>   *mu_calo_eta;
   std::vector<float>   *mu_calo_phi;
   std::vector<float>   *mu_calo_charge;
   std::vector<int>     *mu_calo_author;
   std::vector<float>   *mu_calo_etcone20;
   std::vector<float>   *mu_calo_etcone30;
   std::vector<float>   *mu_calo_ptcone20;
   std::vector<float>   *mu_calo_ptcone30;
   std::vector<unsigned short> *mu_calo_caloMuonIdTag;
   std::vector<double>  *mu_calo_caloLRLikelihood;
   std::vector<int>     *mu_calo_isStandAloneMuon;
   std::vector<int>     *mu_calo_isCombinedMuon;
   std::vector<int>     *mu_calo_isSegmentTaggedMuon;
   std::vector<float>   *mu_calo_d0_exPV;
   std::vector<float>   *mu_calo_z0_exPV;
   std::vector<float>   *mu_calo_id_theta_exPV;
   std::vector<float>   *mu_calo_id_qoverp_exPV;
   std::vector<float>   *mu_calo_me_theta_exPV;
   std::vector<float>   *mu_calo_me_qoverp_exPV;
   std::vector<float>   *mu_calo_id_d0;
   std::vector<float>   *mu_calo_id_z0;
   std::vector<float>   *mu_calo_id_phi;
   std::vector<float>   *mu_calo_id_theta;
   std::vector<float>   *mu_calo_id_qoverp;
   std::vector<int>     *mu_calo_nBLHits;
   std::vector<int>     *mu_calo_nPixHits;
   std::vector<int>     *mu_calo_nSCTHits;
   std::vector<int>     *mu_calo_nTRTHits;
   std::vector<int>     *mu_calo_nPixHoles;
   std::vector<int>     *mu_calo_nSCTHoles;
   std::vector<int>     *mu_calo_nTRTOutliers;
   std::vector<int>     *mu_calo_nPixelDeadSensors;
   std::vector<int>     *mu_calo_nSCTDeadSensors;
   std::vector<int>     *mu_calo_expectBLayerHit;
   std::vector<int>     *mu_calo_nCSCEtaHits;
   std::vector<int>     *mu_calo_nCSCPhiHits;
   std::vector<int>     *mu_calo_nMDTEMHits;
   std::vector<int>     *mu_calo_nMDTEOHits;
   std::vector<float>   *mu_calo_trackIPEstimate_d0_unbiasedpvunbiased;
   std::vector<float>   *mu_calo_trackIPEstimate_sigd0_unbiasedpvunbiased;
   std::vector<int>     *mu_calo_truth_type;
   std::vector<int>     *mu_calo_truth_mothertype;
   Int_t           vxp_n;
   std::vector<int>     *vxp_nTracks;
   std::vector<std::vector<double> > *mcevt_weight;
   Int_t           mc_n;
   std::vector<std::vector<int> > *mc_children;
   std::vector<int>     *mc_pdgId;
   std::vector<std::vector<int> > *mc_child_index;
   UInt_t          trig_DB_SMK;
   std::vector<float>   *trig_L1_mu_eta;
   std::vector<float>   *trig_L1_mu_phi;
   std::vector<std::string>  *trig_L1_mu_thrName;
   std::vector<float>   *trig_L2_muonfeature_eta;
   std::vector<float>   *trig_L2_muonfeature_phi;
   std::vector<float>   *trig_L2_combmuonfeature_eta;
   std::vector<float>   *trig_L2_combmuonfeature_phi;
   std::vector<std::vector<float> > *trig_EF_trigmuonef_track_SA_pt;
   std::vector<std::vector<float> > *trig_EF_trigmuonef_track_SA_eta;
   std::vector<std::vector<float> > *trig_EF_trigmuonef_track_SA_phi;
   std::vector<std::vector<float> > *trig_EF_trigmuonef_track_CB_pt;
   std::vector<std::vector<float> > *trig_EF_trigmuonef_track_CB_eta;
   std::vector<std::vector<float> > *trig_EF_trigmuonef_track_CB_phi;
   std::vector<std::vector<float> > *trig_EF_trigmugirl_track_CB_pt;
   std::vector<std::vector<float> > *trig_EF_trigmugirl_track_CB_eta;
   std::vector<std::vector<float> > *trig_EF_trigmugirl_track_CB_phi;
   Int_t           trig_Nav_n;
   std::vector<short>   *trig_Nav_chain_ChainId;
   std::vector<std::vector<int> > *trig_Nav_chain_RoIType;
   std::vector<std::vector<int> > *trig_Nav_chain_RoIIndex;
   std::vector<int>     *trig_RoI_L2_mu_MuonFeature;
   std::vector<int>     *trig_RoI_L2_mu_CombinedMuonFeature;
   std::vector<int>     *trig_RoI_L2_mu_CombinedMuonFeatureStatus;
   std::vector<int>     *trig_RoI_L2_mu_Muon_ROI;
   std::vector<int>     *trig_RoI_EF_mu_Muon_ROI;
   std::vector<std::vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainer;
   std::vector<std::vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus;
   Int_t           trig_EF_el_n;
   std::vector<float>   *trig_EF_el_eta;
   std::vector<float>   *trig_EF_el_phi;
   std::vector<std::vector<int> > *trig_RoI_EF_e_egammaContainer_egamma_Electrons;
   std::vector<std::vector<int> > *trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus;
   Bool_t          EF_2e12Tvh_medium;
   Bool_t          EF_e22vh_medium1;

   // List of branches
   TBranch        *b_EF_2e12T_medium;   //!
   TBranch        *b_EF_2e12_medium;   //!
   TBranch        *b_EF_2e15_medium;   //!
   TBranch        *b_EF_2mu10_loose;   //!
   TBranch        *b_EF_e10_medium_mu10;   //!
   TBranch        *b_EF_e10_medium_mu6;   //!
   TBranch        *b_EF_e20_medium;   //!
   TBranch        *b_EF_e22_medium;   //!
   TBranch        *b_EF_e22_medium1;   //!
   TBranch        *b_EF_mu10;   //!
   TBranch        *b_EF_mu15_mu10_EFFS;   //!
   TBranch        *b_EF_mu15_mu10_EFFS_medium;   //!
   TBranch        *b_EF_mu18;   //!
   TBranch        *b_EF_mu18_MG;   //!
   TBranch        *b_EF_mu18_MG_medium;   //!
   TBranch        *b_EF_mu20;   //!
   TBranch        *b_EF_mu20_MG;   //!
   TBranch        *b_EF_mu20_MG_medium;   //!
   TBranch        *b_EF_mu22;   //!
   TBranch        *b_EF_mu22_MG;   //!
   TBranch        *b_EF_mu22_MG_medium;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_actualIntPerXing;   //!
   TBranch        *b_averageIntPerXing;   //!
   TBranch        *b_mc_channel_number;   //!
   TBranch        *b_larError;   //!
   TBranch        *b_el_n;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_author;   //!
   TBranch        *b_el_OQ;   //!
   TBranch        *b_el_medium;   //!
   TBranch        *b_el_tight;   //!
   TBranch        *b_el_loosePP;   //!
   TBranch        *b_el_Ethad;   //!
   TBranch        *b_el_Ethad1;   //!
   TBranch        *b_el_f1;   //!
   TBranch        *b_el_Emax2;   //!
   TBranch        *b_el_wstot;   //!
   TBranch        *b_el_emaxs1;   //!
   TBranch        *b_el_weta2;   //!
   TBranch        *b_el_Etcone20;   //!
   TBranch        *b_el_Etcone30;   //!
   TBranch        *b_el_ptcone20;   //!
   TBranch        *b_el_ptcone30;   //!
   TBranch        *b_el_deltaeta1;   //!
   TBranch        *b_el_reta;   //!
   TBranch        *b_el_rphi;   //!
   TBranch        *b_el_etap;   //!
   TBranch        *b_el_etas2;   //!
   TBranch        *b_el_cl_E;   //!
   TBranch        *b_el_cl_pt;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_el_cl_phi;   //!
   TBranch        *b_el_trackd0;   //!
   TBranch        *b_el_trackz0;   //!
   TBranch        *b_el_trackphi;   //!
   TBranch        *b_el_tracktheta;   //!
   TBranch        *b_el_trackqoverp;   //!
   TBranch        *b_el_trackpt;   //!
   TBranch        *b_el_tracketa;   //!
   TBranch        *b_el_nBLHits;   //!
   TBranch        *b_el_nPixHits;   //!
   TBranch        *b_el_nSCTHits;   //!
   TBranch        *b_el_nTRTHits;   //!
   TBranch        *b_el_nTRTHighTHits;   //!
   TBranch        *b_el_nBLayerOutliers;   //!
   TBranch        *b_el_nPixelOutliers;   //!
   TBranch        *b_el_nSCTOutliers;   //!
   TBranch        *b_el_nTRTOutliers;   //!
   TBranch        *b_el_nTRTHighTOutliers;   //!
   TBranch        *b_el_nSiHits;   //!
   TBranch        *b_el_trackd0pvunbiased;   //!
   TBranch        *b_el_trackz0pvunbiased;   //!
   TBranch        *b_el_tracksigd0pvunbiased;   //!
   TBranch        *b_el_EF_index;   //!
   TBranch        *b_el_type;   //!
   TBranch        *b_el_origin;   //!
   TBranch        *b_el_typebkg;   //!
   TBranch        *b_el_originbkg;   //!
   TBranch        *b_el_truth_type;   //!
   TBranch        *b_el_truth_mothertype;   //!
   TBranch        *b_mu_muid_n;   //!
   TBranch        *b_mu_muid_E;   //!
   TBranch        *b_mu_muid_pt;   //!
   TBranch        *b_mu_muid_eta;   //!
   TBranch        *b_mu_muid_phi;   //!
   TBranch        *b_mu_muid_charge;   //!
   TBranch        *b_mu_muid_author;   //!
   TBranch        *b_mu_muid_etcone20;   //!
   TBranch        *b_mu_muid_etcone30;   //!
   TBranch        *b_mu_muid_ptcone20;   //!
   TBranch        *b_mu_muid_ptcone30;   //!
   TBranch        *b_mu_muid_isStandAloneMuon;   //!
   TBranch        *b_mu_muid_isCombinedMuon;   //!
   TBranch        *b_mu_muid_isSegmentTaggedMuon;   //!
   TBranch        *b_mu_muid_tight;   //!
   TBranch        *b_mu_muid_d0_exPV;   //!
   TBranch        *b_mu_muid_z0_exPV;   //!
   TBranch        *b_mu_muid_id_theta_exPV;   //!
   TBranch        *b_mu_muid_id_qoverp_exPV;   //!
   TBranch        *b_mu_muid_me_theta_exPV;   //!
   TBranch        *b_mu_muid_me_qoverp_exPV;   //!
   TBranch        *b_mu_muid_id_d0;   //!
   TBranch        *b_mu_muid_id_z0;   //!
   TBranch        *b_mu_muid_id_phi;   //!
   TBranch        *b_mu_muid_id_theta;   //!
   TBranch        *b_mu_muid_id_qoverp;   //!
   TBranch        *b_mu_muid_nBLHits;   //!
   TBranch        *b_mu_muid_nPixHits;   //!
   TBranch        *b_mu_muid_nSCTHits;   //!
   TBranch        *b_mu_muid_nTRTHits;   //!
   TBranch        *b_mu_muid_nPixHoles;   //!
   TBranch        *b_mu_muid_nSCTHoles;   //!
   TBranch        *b_mu_muid_nTRTOutliers;   //!
   TBranch        *b_mu_muid_nPixelDeadSensors;   //!
   TBranch        *b_mu_muid_nSCTDeadSensors;   //!
   TBranch        *b_mu_muid_expectBLayerHit;   //!
   TBranch        *b_mu_muid_nCSCEtaHits;   //!
   TBranch        *b_mu_muid_nCSCPhiHits;   //!
   TBranch        *b_mu_muid_nMDTEMHits;   //!
   TBranch        *b_mu_muid_nMDTEOHits;   //!
   TBranch        *b_mu_muid_trackIPEstimate_d0_unbiasedpvunbiased;   //!
   TBranch        *b_mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased;   //!
   TBranch        *b_mu_muid_truth_type;   //!
   TBranch        *b_mu_muid_truth_mothertype;   //!
   TBranch        *b_mu_muid_EFCB_index;   //!
   TBranch        *b_mu_staco_n;   //!
   TBranch        *b_mu_staco_E;   //!
   TBranch        *b_mu_staco_pt;   //!
   TBranch        *b_mu_staco_eta;   //!
   TBranch        *b_mu_staco_phi;   //!
   TBranch        *b_mu_staco_charge;   //!
   TBranch        *b_mu_staco_author;   //!
   TBranch        *b_mu_staco_etcone20;   //!
   TBranch        *b_mu_staco_etcone30;   //!
   TBranch        *b_mu_staco_ptcone20;   //!
   TBranch        *b_mu_staco_ptcone30;   //!
   TBranch        *b_mu_staco_isStandAloneMuon;   //!
   TBranch        *b_mu_staco_isCombinedMuon;   //!
   TBranch        *b_mu_staco_isSegmentTaggedMuon;   //!
   TBranch        *b_mu_staco_tight;   //!
   TBranch        *b_mu_staco_d0_exPV;   //!
   TBranch        *b_mu_staco_z0_exPV;   //!
   TBranch        *b_mu_staco_id_theta_exPV;   //!
   TBranch        *b_mu_staco_id_qoverp_exPV;   //!
   TBranch        *b_mu_staco_me_theta_exPV;   //!
   TBranch        *b_mu_staco_me_qoverp_exPV;   //!
   TBranch        *b_mu_staco_id_d0;   //!
   TBranch        *b_mu_staco_id_z0;   //!
   TBranch        *b_mu_staco_id_phi;   //!
   TBranch        *b_mu_staco_id_theta;   //!
   TBranch        *b_mu_staco_id_qoverp;   //!
   TBranch        *b_mu_staco_nBLHits;   //!
   TBranch        *b_mu_staco_nPixHits;   //!
   TBranch        *b_mu_staco_nSCTHits;   //!
   TBranch        *b_mu_staco_nTRTHits;   //!
   TBranch        *b_mu_staco_nPixHoles;   //!
   TBranch        *b_mu_staco_nSCTHoles;   //!
   TBranch        *b_mu_staco_nTRTOutliers;   //!
   TBranch        *b_mu_staco_nPixelDeadSensors;   //!
   TBranch        *b_mu_staco_nSCTDeadSensors;   //!
   TBranch        *b_mu_staco_expectBLayerHit;   //!
   TBranch        *b_mu_staco_nCSCEtaHits;   //!
   TBranch        *b_mu_staco_nCSCPhiHits;   //!
   TBranch        *b_mu_staco_nMDTEMHits;   //!
   TBranch        *b_mu_staco_nMDTEOHits;   //!
   TBranch        *b_mu_staco_trackIPEstimate_d0_unbiasedpvunbiased;   //!
   TBranch        *b_mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased;   //!
   TBranch        *b_mu_staco_truth_type;   //!
   TBranch        *b_mu_staco_truth_mothertype;   //!
   TBranch        *b_mu_staco_EFCB_index;   //!
   TBranch        *b_mu_calo_n;   //!
   TBranch        *b_mu_calo_E;   //!
   TBranch        *b_mu_calo_pt;   //!
   TBranch        *b_mu_calo_eta;   //!
   TBranch        *b_mu_calo_phi;   //!
   TBranch        *b_mu_calo_charge;   //!
   TBranch        *b_mu_calo_author;   //!
   TBranch        *b_mu_calo_etcone20;   //!
   TBranch        *b_mu_calo_etcone30;   //!
   TBranch        *b_mu_calo_ptcone20;   //!
   TBranch        *b_mu_calo_ptcone30;   //!
   TBranch        *b_mu_calo_caloMuonIdTag;   //!
   TBranch        *b_mu_calo_caloLRLikelihood;   //!
   TBranch        *b_mu_calo_isStandAloneMuon;   //!
   TBranch        *b_mu_calo_isCombinedMuon;   //!
   TBranch        *b_mu_calo_isSegmentTaggedMuon;   //!
   TBranch        *b_mu_calo_d0_exPV;   //!
   TBranch        *b_mu_calo_z0_exPV;   //!
   TBranch        *b_mu_calo_id_theta_exPV;   //!
   TBranch        *b_mu_calo_id_qoverp_exPV;   //!
   TBranch        *b_mu_calo_me_theta_exPV;   //!
   TBranch        *b_mu_calo_me_qoverp_exPV;   //!
   TBranch        *b_mu_calo_id_d0;   //!
   TBranch        *b_mu_calo_id_z0;   //!
   TBranch        *b_mu_calo_id_phi;   //!
   TBranch        *b_mu_calo_id_theta;   //!
   TBranch        *b_mu_calo_id_qoverp;   //!
   TBranch        *b_mu_calo_nBLHits;   //!
   TBranch        *b_mu_calo_nPixHits;   //!
   TBranch        *b_mu_calo_nSCTHits;   //!
   TBranch        *b_mu_calo_nTRTHits;   //!
   TBranch        *b_mu_calo_nPixHoles;   //!
   TBranch        *b_mu_calo_nSCTHoles;   //!
   TBranch        *b_mu_calo_nTRTOutliers;   //!
   TBranch        *b_mu_calo_nPixelDeadSensors;   //!
   TBranch        *b_mu_calo_nSCTDeadSensors;   //!
   TBranch        *b_mu_calo_expectBLayerHit;   //!
   TBranch        *b_mu_calo_nCSCEtaHits;   //!
   TBranch        *b_mu_calo_nCSCPhiHits;   //!
   TBranch        *b_mu_calo_nMDTEMHits;   //!
   TBranch        *b_mu_calo_nMDTEOHits;   //!
   TBranch        *b_mu_calo_trackIPEstimate_d0_unbiasedpvunbiased;   //!
   TBranch        *b_mu_calo_trackIPEstimate_sigd0_unbiasedpvunbiased;   //!
   TBranch        *b_mu_calo_truth_type;   //!
   TBranch        *b_mu_calo_truth_mothertype;   //!
   TBranch        *b_vxp_n;   //!
   TBranch        *b_vxp_nTracks;   //!
   TBranch        *b_mcevt_weight;   //!
   TBranch        *b_mc_n;   //!
   TBranch        *b_mc_children;   //!
   TBranch        *b_mc_pdgId;   //!
   TBranch        *b_mc_child_index;   //!
   TBranch        *b_trig_DB_SMK;   //!
   TBranch        *b_trig_L1_mu_eta;   //!
   TBranch        *b_trig_L1_mu_phi;   //!
   TBranch        *b_trig_L1_mu_thrName;   //!
   TBranch        *b_trig_L2_muonfeature_eta;   //!
   TBranch        *b_trig_L2_muonfeature_phi;   //!
   TBranch        *b_trig_L2_combmuonfeature_eta;   //!
   TBranch        *b_trig_L2_combmuonfeature_phi;   //!
   TBranch        *b_trig_EF_trigmuonef_track_SA_pt;   //!
   TBranch        *b_trig_EF_trigmuonef_track_SA_eta;   //!
   TBranch        *b_trig_EF_trigmuonef_track_SA_phi;   //!
   TBranch        *b_trig_EF_trigmuonef_track_CB_pt;   //!
   TBranch        *b_trig_EF_trigmuonef_track_CB_eta;   //!
   TBranch        *b_trig_EF_trigmuonef_track_CB_phi;   //!
   TBranch        *b_trig_EF_trigmugirl_track_CB_pt;   //!
   TBranch        *b_trig_EF_trigmugirl_track_CB_eta;   //!
   TBranch        *b_trig_EF_trigmugirl_track_CB_phi;   //!
   TBranch        *b_trig_Nav_n;   //!
   TBranch        *b_trig_Nav_chain_ChainId;   //!
   TBranch        *b_trig_Nav_chain_RoIType;   //!
   TBranch        *b_trig_Nav_chain_RoIIndex;   //!
   TBranch        *b_trig_RoI_L2_mu_MuonFeature;   //!
   TBranch        *b_trig_RoI_L2_mu_CombinedMuonFeature;   //!
   TBranch        *b_trig_RoI_L2_mu_CombinedMuonFeatureStatus;   //!
   TBranch        *b_trig_RoI_L2_mu_Muon_ROI;   //!
   TBranch        *b_trig_RoI_EF_mu_Muon_ROI;   //!
   TBranch        *b_trig_RoI_EF_mu_TrigMuonEFInfoContainer;   //!
   TBranch        *b_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus;   //!
   TBranch        *b_trig_EF_el_n;   //!
   TBranch        *b_trig_EF_el_eta;   //!
   TBranch        *b_trig_EF_el_phi;   //!
   TBranch        *b_trig_RoI_EF_e_egammaContainer_egamma_Electrons;   //!
   TBranch        *b_trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus;   //!
   TBranch        *b_EF_2e12Tvh_medium;   //!
   TBranch        *b_EF_e22vh_medium1;   //!

   THiggsD3PD(TTree *tree=0);
   virtual ~THiggsD3PD();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef THiggsD3PD_cxx
THiggsD3PD::THiggsD3PD(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("result.root");
      if (!f) {
         f = new TFile("result.root");
      }
      tree = (TTree*)gDirectory->Get("physics");

   }
   Init(tree);
}

THiggsD3PD::~THiggsD3PD()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t THiggsD3PD::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t THiggsD3PD::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void THiggsD3PD::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   el_charge = 0;
   el_author = 0;
   el_OQ = 0;
   el_medium = 0;
   el_tight = 0;
   el_loosePP = 0;
   el_Ethad = 0;
   el_Ethad1 = 0;
   el_f1 = 0;
   el_Emax2 = 0;
   el_wstot = 0;
   el_emaxs1 = 0;
   el_weta2 = 0;
   el_Etcone20 = 0;
   el_Etcone30 = 0;
   el_ptcone20 = 0;
   el_ptcone30 = 0;
   el_deltaeta1 = 0;
   el_reta = 0;
   el_rphi = 0;
   el_etap = 0;
   el_etas2 = 0;
   el_cl_E = 0;
   el_cl_pt = 0;
   el_cl_eta = 0;
   el_cl_phi = 0;
   el_trackd0 = 0;
   el_trackz0 = 0;
   el_trackphi = 0;
   el_tracktheta = 0;
   el_trackqoverp = 0;
   el_trackpt = 0;
   el_tracketa = 0;
   el_nBLHits = 0;
   el_nPixHits = 0;
   el_nSCTHits = 0;
   el_nTRTHits = 0;
   el_nTRTHighTHits = 0;
   el_nBLayerOutliers = 0;
   el_nPixelOutliers = 0;
   el_nSCTOutliers = 0;
   el_nTRTOutliers = 0;
   el_nTRTHighTOutliers = 0;
   el_nSiHits = 0;
   el_trackd0pvunbiased = 0;
   el_trackz0pvunbiased = 0;
   el_tracksigd0pvunbiased = 0;
   el_EF_index = 0;
   el_type = 0;
   el_origin = 0;
   el_typebkg = 0;
   el_originbkg = 0;
   el_truth_type = 0;
   el_truth_mothertype = 0;
   mu_muid_E = 0;
   mu_muid_pt = 0;
   mu_muid_eta = 0;
   mu_muid_phi = 0;
   mu_muid_charge = 0;
   mu_muid_author = 0;
   mu_muid_etcone20 = 0;
   mu_muid_etcone30 = 0;
   mu_muid_ptcone20 = 0;
   mu_muid_ptcone30 = 0;
   mu_muid_isStandAloneMuon = 0;
   mu_muid_isCombinedMuon = 0;
   mu_muid_isSegmentTaggedMuon = 0;
   mu_muid_tight = 0;
   mu_muid_d0_exPV = 0;
   mu_muid_z0_exPV = 0;
   mu_muid_id_theta_exPV = 0;
   mu_muid_id_qoverp_exPV = 0;
   mu_muid_me_theta_exPV = 0;
   mu_muid_me_qoverp_exPV = 0;
   mu_muid_id_d0 = 0;
   mu_muid_id_z0 = 0;
   mu_muid_id_phi = 0;
   mu_muid_id_theta = 0;
   mu_muid_id_qoverp = 0;
   mu_muid_nBLHits = 0;
   mu_muid_nPixHits = 0;
   mu_muid_nSCTHits = 0;
   mu_muid_nTRTHits = 0;
   mu_muid_nPixHoles = 0;
   mu_muid_nSCTHoles = 0;
   mu_muid_nTRTOutliers = 0;
   mu_muid_nPixelDeadSensors = 0;
   mu_muid_nSCTDeadSensors = 0;
   mu_muid_expectBLayerHit = 0;
   mu_muid_nCSCEtaHits = 0;
   mu_muid_nCSCPhiHits = 0;
   mu_muid_nMDTEMHits = 0;
   mu_muid_nMDTEOHits = 0;
   mu_muid_trackIPEstimate_d0_unbiasedpvunbiased = 0;
   mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased = 0;
   mu_muid_truth_type = 0;
   mu_muid_truth_mothertype = 0;
   mu_muid_EFCB_index = 0;
   mu_staco_E = 0;
   mu_staco_pt = 0;
   mu_staco_eta = 0;
   mu_staco_phi = 0;
   mu_staco_charge = 0;
   mu_staco_author = 0;
   mu_staco_etcone20 = 0;
   mu_staco_etcone30 = 0;
   mu_staco_ptcone20 = 0;
   mu_staco_ptcone30 = 0;
   mu_staco_isStandAloneMuon = 0;
   mu_staco_isCombinedMuon = 0;
   mu_staco_isSegmentTaggedMuon = 0;
   mu_staco_tight = 0;
   mu_staco_d0_exPV = 0;
   mu_staco_z0_exPV = 0;
   mu_staco_id_theta_exPV = 0;
   mu_staco_id_qoverp_exPV = 0;
   mu_staco_me_theta_exPV = 0;
   mu_staco_me_qoverp_exPV = 0;
   mu_staco_id_d0 = 0;
   mu_staco_id_z0 = 0;
   mu_staco_id_phi = 0;
   mu_staco_id_theta = 0;
   mu_staco_id_qoverp = 0;
   mu_staco_nBLHits = 0;
   mu_staco_nPixHits = 0;
   mu_staco_nSCTHits = 0;
   mu_staco_nTRTHits = 0;
   mu_staco_nPixHoles = 0;
   mu_staco_nSCTHoles = 0;
   mu_staco_nTRTOutliers = 0;
   mu_staco_nPixelDeadSensors = 0;
   mu_staco_nSCTDeadSensors = 0;
   mu_staco_expectBLayerHit = 0;
   mu_staco_nCSCEtaHits = 0;
   mu_staco_nCSCPhiHits = 0;
   mu_staco_nMDTEMHits = 0;
   mu_staco_nMDTEOHits = 0;
   mu_staco_trackIPEstimate_d0_unbiasedpvunbiased = 0;
   mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased = 0;
   mu_staco_truth_type = 0;
   mu_staco_truth_mothertype = 0;
   mu_staco_EFCB_index = 0;
   mu_calo_E = 0;
   mu_calo_pt = 0;
   mu_calo_eta = 0;
   mu_calo_phi = 0;
   mu_calo_charge = 0;
   mu_calo_author = 0;
   mu_calo_etcone20 = 0;
   mu_calo_etcone30 = 0;
   mu_calo_ptcone20 = 0;
   mu_calo_ptcone30 = 0;
   mu_calo_caloMuonIdTag = 0;
   mu_calo_caloLRLikelihood = 0;
   mu_calo_isStandAloneMuon = 0;
   mu_calo_isCombinedMuon = 0;
   mu_calo_isSegmentTaggedMuon = 0;
   mu_calo_d0_exPV = 0;
   mu_calo_z0_exPV = 0;
   mu_calo_id_theta_exPV = 0;
   mu_calo_id_qoverp_exPV = 0;
   mu_calo_me_theta_exPV = 0;
   mu_calo_me_qoverp_exPV = 0;
   mu_calo_id_d0 = 0;
   mu_calo_id_z0 = 0;
   mu_calo_id_phi = 0;
   mu_calo_id_theta = 0;
   mu_calo_id_qoverp = 0;
   mu_calo_nBLHits = 0;
   mu_calo_nPixHits = 0;
   mu_calo_nSCTHits = 0;
   mu_calo_nTRTHits = 0;
   mu_calo_nPixHoles = 0;
   mu_calo_nSCTHoles = 0;
   mu_calo_nTRTOutliers = 0;
   mu_calo_nPixelDeadSensors = 0;
   mu_calo_nSCTDeadSensors = 0;
   mu_calo_expectBLayerHit = 0;
   mu_calo_nCSCEtaHits = 0;
   mu_calo_nCSCPhiHits = 0;
   mu_calo_nMDTEMHits = 0;
   mu_calo_nMDTEOHits = 0;
   mu_calo_trackIPEstimate_d0_unbiasedpvunbiased = 0;
   mu_calo_trackIPEstimate_sigd0_unbiasedpvunbiased = 0;
   mu_calo_truth_type = 0;
   mu_calo_truth_mothertype = 0;
   vxp_nTracks = 0;
   mcevt_weight = 0;
   mc_children = 0;
   mc_pdgId = 0;
   mc_child_index = 0;
   trig_L1_mu_eta = 0;
   trig_L1_mu_phi = 0;
   trig_L1_mu_thrName = 0;
   trig_L2_muonfeature_eta = 0;
   trig_L2_muonfeature_phi = 0;
   trig_L2_combmuonfeature_eta = 0;
   trig_L2_combmuonfeature_phi = 0;
   trig_EF_trigmuonef_track_SA_pt = 0;
   trig_EF_trigmuonef_track_SA_eta = 0;
   trig_EF_trigmuonef_track_SA_phi = 0;
   trig_EF_trigmuonef_track_CB_pt = 0;
   trig_EF_trigmuonef_track_CB_eta = 0;
   trig_EF_trigmuonef_track_CB_phi = 0;
   trig_EF_trigmugirl_track_CB_pt = 0;
   trig_EF_trigmugirl_track_CB_eta = 0;
   trig_EF_trigmugirl_track_CB_phi = 0;
   trig_Nav_chain_ChainId = 0;
   trig_Nav_chain_RoIType = 0;
   trig_Nav_chain_RoIIndex = 0;
   trig_RoI_L2_mu_MuonFeature = 0;
   trig_RoI_L2_mu_CombinedMuonFeature = 0;
   trig_RoI_L2_mu_CombinedMuonFeatureStatus = 0;
   trig_RoI_L2_mu_Muon_ROI = 0;
   trig_RoI_EF_mu_Muon_ROI = 0;
   trig_RoI_EF_mu_TrigMuonEFInfoContainer = 0;
   trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus = 0;
   trig_EF_el_eta = 0;
   trig_EF_el_phi = 0;
   trig_RoI_EF_e_egammaContainer_egamma_Electrons = 0;
   trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EF_2e12T_medium", &EF_2e12T_medium, &b_EF_2e12T_medium);
   fChain->SetBranchAddress("EF_2e12_medium", &EF_2e12_medium, &b_EF_2e12_medium);
   fChain->SetBranchAddress("EF_2e15_medium", &EF_2e15_medium, &b_EF_2e15_medium);
   fChain->SetBranchAddress("EF_2mu10_loose", &EF_2mu10_loose, &b_EF_2mu10_loose);
   fChain->SetBranchAddress("EF_e10_medium_mu10", &EF_e10_medium_mu10, &b_EF_e10_medium_mu10);
   fChain->SetBranchAddress("EF_e10_medium_mu6", &EF_e10_medium_mu6, &b_EF_e10_medium_mu6);
   fChain->SetBranchAddress("EF_e20_medium", &EF_e20_medium, &b_EF_e20_medium);
   fChain->SetBranchAddress("EF_e22_medium", &EF_e22_medium, &b_EF_e22_medium);
   fChain->SetBranchAddress("EF_e22_medium1", &EF_e22_medium1, &b_EF_e22_medium1);
   fChain->SetBranchAddress("EF_mu10", &EF_mu10, &b_EF_mu10);
   fChain->SetBranchAddress("EF_mu15_mu10_EFFS", &EF_mu15_mu10_EFFS, &b_EF_mu15_mu10_EFFS);
   fChain->SetBranchAddress("EF_mu15_mu10_EFFS_medium", &EF_mu15_mu10_EFFS_medium, &b_EF_mu15_mu10_EFFS_medium);
   fChain->SetBranchAddress("EF_mu18", &EF_mu18, &b_EF_mu18);
   fChain->SetBranchAddress("EF_mu18_MG", &EF_mu18_MG, &b_EF_mu18_MG);
   fChain->SetBranchAddress("EF_mu18_MG_medium", &EF_mu18_MG_medium, &b_EF_mu18_MG_medium);
   fChain->SetBranchAddress("EF_mu20", &EF_mu20, &b_EF_mu20);
   fChain->SetBranchAddress("EF_mu20_MG", &EF_mu20_MG, &b_EF_mu20_MG);
   fChain->SetBranchAddress("EF_mu20_MG_medium", &EF_mu20_MG_medium, &b_EF_mu20_MG_medium);
   fChain->SetBranchAddress("EF_mu22", &EF_mu22, &b_EF_mu22);
   fChain->SetBranchAddress("EF_mu22_MG", &EF_mu22_MG, &b_EF_mu22_MG);
   fChain->SetBranchAddress("EF_mu22_MG_medium", &EF_mu22_MG_medium, &b_EF_mu22_MG_medium);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("actualIntPerXing", &actualIntPerXing, &b_actualIntPerXing);
   fChain->SetBranchAddress("averageIntPerXing", &averageIntPerXing, &b_averageIntPerXing);
   fChain->SetBranchAddress("mc_channel_number", &mc_channel_number, &b_mc_channel_number);
   fChain->SetBranchAddress("larError", &larError, &b_larError);
   fChain->SetBranchAddress("el_GSF_n", &el_n, &b_el_n);
   fChain->SetBranchAddress("el_GSF_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_GSF_author", &el_author, &b_el_author);
   fChain->SetBranchAddress("el_GSF_OQ", &el_OQ, &b_el_OQ);
   fChain->SetBranchAddress("el_GSF_medium", &el_medium, &b_el_medium);
   fChain->SetBranchAddress("el_GSF_tight", &el_tight, &b_el_tight);
   fChain->SetBranchAddress("el_GSF_loosePP", &el_loosePP, &b_el_loosePP);
   fChain->SetBranchAddress("el_GSF_Ethad", &el_Ethad, &b_el_Ethad);
   fChain->SetBranchAddress("el_GSF_Ethad1", &el_Ethad1, &b_el_Ethad1);
   fChain->SetBranchAddress("el_GSF_f1", &el_f1, &b_el_f1);
   fChain->SetBranchAddress("el_GSF_Emax2", &el_Emax2, &b_el_Emax2);
   fChain->SetBranchAddress("el_GSF_wstot", &el_wstot, &b_el_wstot);
   fChain->SetBranchAddress("el_GSF_emaxs1", &el_emaxs1, &b_el_emaxs1);
   fChain->SetBranchAddress("el_GSF_weta2", &el_weta2, &b_el_weta2);
   fChain->SetBranchAddress("el_GSF_Etcone20", &el_Etcone20, &b_el_Etcone20);
   fChain->SetBranchAddress("el_GSF_Etcone30", &el_Etcone30, &b_el_Etcone30);
   fChain->SetBranchAddress("el_GSF_ptcone20", &el_ptcone20, &b_el_ptcone20);
   fChain->SetBranchAddress("el_GSF_ptcone30", &el_ptcone30, &b_el_ptcone30);
   fChain->SetBranchAddress("el_GSF_deltaeta1", &el_deltaeta1, &b_el_deltaeta1);
   fChain->SetBranchAddress("el_GSF_reta", &el_reta, &b_el_reta);
   fChain->SetBranchAddress("el_GSF_rphi", &el_rphi, &b_el_rphi);
   fChain->SetBranchAddress("el_GSF_etap", &el_etap, &b_el_etap);
   fChain->SetBranchAddress("el_GSF_etas2", &el_etas2, &b_el_etas2);
   fChain->SetBranchAddress("el_GSF_cl_E", &el_cl_E, &b_el_cl_E);
   fChain->SetBranchAddress("el_GSF_cl_pt", &el_cl_pt, &b_el_cl_pt);
   fChain->SetBranchAddress("el_GSF_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("el_GSF_cl_phi", &el_cl_phi, &b_el_cl_phi);
   fChain->SetBranchAddress("el_GSF_trackd0", &el_trackd0, &b_el_trackd0);
   fChain->SetBranchAddress("el_GSF_trackz0", &el_trackz0, &b_el_trackz0);
   fChain->SetBranchAddress("el_GSF_trackphi", &el_trackphi, &b_el_trackphi);
   fChain->SetBranchAddress("el_GSF_tracktheta", &el_tracktheta, &b_el_tracktheta);
   fChain->SetBranchAddress("el_GSF_trackqoverp", &el_trackqoverp, &b_el_trackqoverp);
   fChain->SetBranchAddress("el_GSF_trackpt", &el_trackpt, &b_el_trackpt);
   fChain->SetBranchAddress("el_GSF_tracketa", &el_tracketa, &b_el_tracketa);
   fChain->SetBranchAddress("el_GSF_nBLHits", &el_nBLHits, &b_el_nBLHits);
   fChain->SetBranchAddress("el_GSF_nPixHits", &el_nPixHits, &b_el_nPixHits);
   fChain->SetBranchAddress("el_GSF_nSCTHits", &el_nSCTHits, &b_el_nSCTHits);
   fChain->SetBranchAddress("el_GSF_nTRTHits", &el_nTRTHits, &b_el_nTRTHits);
   fChain->SetBranchAddress("el_GSF_nTRTHighTHits", &el_nTRTHighTHits, &b_el_nTRTHighTHits);
   fChain->SetBranchAddress("el_GSF_nBLayerOutliers", &el_nBLayerOutliers, &b_el_nBLayerOutliers);
   fChain->SetBranchAddress("el_GSF_nPixelOutliers", &el_nPixelOutliers, &b_el_nPixelOutliers);
   fChain->SetBranchAddress("el_GSF_nSCTOutliers", &el_nSCTOutliers, &b_el_nSCTOutliers);
   fChain->SetBranchAddress("el_GSF_nTRTOutliers", &el_nTRTOutliers, &b_el_nTRTOutliers);
   fChain->SetBranchAddress("el_GSF_nTRTHighTOutliers", &el_nTRTHighTOutliers, &b_el_nTRTHighTOutliers);
   fChain->SetBranchAddress("el_GSF_nSiHits", &el_nSiHits, &b_el_nSiHits);
   fChain->SetBranchAddress("el_GSF_trackd0pvunbiased", &el_trackd0pvunbiased, &b_el_trackd0pvunbiased);
   fChain->SetBranchAddress("el_GSF_trackz0pvunbiased", &el_trackz0pvunbiased, &b_el_trackz0pvunbiased);
   fChain->SetBranchAddress("el_GSF_tracksigd0pvunbiased", &el_tracksigd0pvunbiased, &b_el_tracksigd0pvunbiased);
   fChain->SetBranchAddress("el_GSF_EF_index", &el_EF_index, &b_el_EF_index);
   fChain->SetBranchAddress("el_GSF_type", &el_type, &b_el_type);
   fChain->SetBranchAddress("el_GSF_origin", &el_origin, &b_el_origin);
   fChain->SetBranchAddress("el_GSF_typebkg", &el_typebkg, &b_el_typebkg);
   fChain->SetBranchAddress("el_GSF_originbkg", &el_originbkg, &b_el_originbkg);
   fChain->SetBranchAddress("el_GSF_truth_type", &el_truth_type, &b_el_truth_type);
   fChain->SetBranchAddress("el_GSF_truth_mothertype", &el_truth_mothertype, &b_el_truth_mothertype);
   fChain->SetBranchAddress("mu_muid_n", &mu_muid_n, &b_mu_muid_n);
   fChain->SetBranchAddress("mu_muid_E", &mu_muid_E, &b_mu_muid_E);
   fChain->SetBranchAddress("mu_muid_pt", &mu_muid_pt, &b_mu_muid_pt);
   fChain->SetBranchAddress("mu_muid_eta", &mu_muid_eta, &b_mu_muid_eta);
   fChain->SetBranchAddress("mu_muid_phi", &mu_muid_phi, &b_mu_muid_phi);
   fChain->SetBranchAddress("mu_muid_charge", &mu_muid_charge, &b_mu_muid_charge);
   fChain->SetBranchAddress("mu_muid_author", &mu_muid_author, &b_mu_muid_author);
   fChain->SetBranchAddress("mu_muid_etcone20", &mu_muid_etcone20, &b_mu_muid_etcone20);
   fChain->SetBranchAddress("mu_muid_etcone30", &mu_muid_etcone30, &b_mu_muid_etcone30);
   fChain->SetBranchAddress("mu_muid_ptcone20", &mu_muid_ptcone20, &b_mu_muid_ptcone20);
   fChain->SetBranchAddress("mu_muid_ptcone30", &mu_muid_ptcone30, &b_mu_muid_ptcone30);
   fChain->SetBranchAddress("mu_muid_isStandAloneMuon", &mu_muid_isStandAloneMuon, &b_mu_muid_isStandAloneMuon);
   fChain->SetBranchAddress("mu_muid_isCombinedMuon", &mu_muid_isCombinedMuon, &b_mu_muid_isCombinedMuon);
   fChain->SetBranchAddress("mu_muid_isSegmentTaggedMuon", &mu_muid_isSegmentTaggedMuon, &b_mu_muid_isSegmentTaggedMuon);
   fChain->SetBranchAddress("mu_muid_tight", &mu_muid_tight, &b_mu_muid_tight);
   fChain->SetBranchAddress("mu_muid_d0_exPV", &mu_muid_d0_exPV, &b_mu_muid_d0_exPV);
   fChain->SetBranchAddress("mu_muid_z0_exPV", &mu_muid_z0_exPV, &b_mu_muid_z0_exPV);
   fChain->SetBranchAddress("mu_muid_id_theta_exPV", &mu_muid_id_theta_exPV, &b_mu_muid_id_theta_exPV);
   fChain->SetBranchAddress("mu_muid_id_qoverp_exPV", &mu_muid_id_qoverp_exPV, &b_mu_muid_id_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_me_theta_exPV", &mu_muid_me_theta_exPV, &b_mu_muid_me_theta_exPV);
   fChain->SetBranchAddress("mu_muid_me_qoverp_exPV", &mu_muid_me_qoverp_exPV, &b_mu_muid_me_qoverp_exPV);
   fChain->SetBranchAddress("mu_muid_id_d0", &mu_muid_id_d0, &b_mu_muid_id_d0);
   fChain->SetBranchAddress("mu_muid_id_z0", &mu_muid_id_z0, &b_mu_muid_id_z0);
   fChain->SetBranchAddress("mu_muid_id_phi", &mu_muid_id_phi, &b_mu_muid_id_phi);
   fChain->SetBranchAddress("mu_muid_id_theta", &mu_muid_id_theta, &b_mu_muid_id_theta);
   fChain->SetBranchAddress("mu_muid_id_qoverp", &mu_muid_id_qoverp, &b_mu_muid_id_qoverp);
   fChain->SetBranchAddress("mu_muid_nBLHits", &mu_muid_nBLHits, &b_mu_muid_nBLHits);
   fChain->SetBranchAddress("mu_muid_nPixHits", &mu_muid_nPixHits, &b_mu_muid_nPixHits);
   fChain->SetBranchAddress("mu_muid_nSCTHits", &mu_muid_nSCTHits, &b_mu_muid_nSCTHits);
   fChain->SetBranchAddress("mu_muid_nTRTHits", &mu_muid_nTRTHits, &b_mu_muid_nTRTHits);
   fChain->SetBranchAddress("mu_muid_nPixHoles", &mu_muid_nPixHoles, &b_mu_muid_nPixHoles);
   fChain->SetBranchAddress("mu_muid_nSCTHoles", &mu_muid_nSCTHoles, &b_mu_muid_nSCTHoles);
   fChain->SetBranchAddress("mu_muid_nTRTOutliers", &mu_muid_nTRTOutliers, &b_mu_muid_nTRTOutliers);
   fChain->SetBranchAddress("mu_muid_nPixelDeadSensors", &mu_muid_nPixelDeadSensors, &b_mu_muid_nPixelDeadSensors);
   fChain->SetBranchAddress("mu_muid_nSCTDeadSensors", &mu_muid_nSCTDeadSensors, &b_mu_muid_nSCTDeadSensors);
   fChain->SetBranchAddress("mu_muid_expectBLayerHit", &mu_muid_expectBLayerHit, &b_mu_muid_expectBLayerHit);
   fChain->SetBranchAddress("mu_muid_nCSCEtaHits", &mu_muid_nCSCEtaHits, &b_mu_muid_nCSCEtaHits);
   fChain->SetBranchAddress("mu_muid_nCSCPhiHits", &mu_muid_nCSCPhiHits, &b_mu_muid_nCSCPhiHits);
   fChain->SetBranchAddress("mu_muid_nMDTEMHits", &mu_muid_nMDTEMHits, &b_mu_muid_nMDTEMHits);
   fChain->SetBranchAddress("mu_muid_nMDTEOHits", &mu_muid_nMDTEOHits, &b_mu_muid_nMDTEOHits);
   fChain->SetBranchAddress("mu_muid_trackIPEstimate_d0_unbiasedpvunbiased", &mu_muid_trackIPEstimate_d0_unbiasedpvunbiased, &b_mu_muid_trackIPEstimate_d0_unbiasedpvunbiased);
   fChain->SetBranchAddress("mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased", &mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased, &b_mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased);
   fChain->SetBranchAddress("mu_muid_truth_type", &mu_muid_truth_type, &b_mu_muid_truth_type);
   fChain->SetBranchAddress("mu_muid_truth_mothertype", &mu_muid_truth_mothertype, &b_mu_muid_truth_mothertype);
   fChain->SetBranchAddress("mu_muid_EFCB_index", &mu_muid_EFCB_index, &b_mu_muid_EFCB_index);
   fChain->SetBranchAddress("mu_staco_n", &mu_staco_n, &b_mu_staco_n);
   fChain->SetBranchAddress("mu_staco_E", &mu_staco_E, &b_mu_staco_E);
   fChain->SetBranchAddress("mu_staco_pt", &mu_staco_pt, &b_mu_staco_pt);
   fChain->SetBranchAddress("mu_staco_eta", &mu_staco_eta, &b_mu_staco_eta);
   fChain->SetBranchAddress("mu_staco_phi", &mu_staco_phi, &b_mu_staco_phi);
   fChain->SetBranchAddress("mu_staco_charge", &mu_staco_charge, &b_mu_staco_charge);
   fChain->SetBranchAddress("mu_staco_author", &mu_staco_author, &b_mu_staco_author);
   fChain->SetBranchAddress("mu_staco_etcone20", &mu_staco_etcone20, &b_mu_staco_etcone20);
   fChain->SetBranchAddress("mu_staco_etcone30", &mu_staco_etcone30, &b_mu_staco_etcone30);
   fChain->SetBranchAddress("mu_staco_ptcone20", &mu_staco_ptcone20, &b_mu_staco_ptcone20);
   fChain->SetBranchAddress("mu_staco_ptcone30", &mu_staco_ptcone30, &b_mu_staco_ptcone30);
   fChain->SetBranchAddress("mu_staco_isStandAloneMuon", &mu_staco_isStandAloneMuon, &b_mu_staco_isStandAloneMuon);
   fChain->SetBranchAddress("mu_staco_isCombinedMuon", &mu_staco_isCombinedMuon, &b_mu_staco_isCombinedMuon);
   fChain->SetBranchAddress("mu_staco_isSegmentTaggedMuon", &mu_staco_isSegmentTaggedMuon, &b_mu_staco_isSegmentTaggedMuon);
   fChain->SetBranchAddress("mu_staco_tight", &mu_staco_tight, &b_mu_staco_tight);
   fChain->SetBranchAddress("mu_staco_d0_exPV", &mu_staco_d0_exPV, &b_mu_staco_d0_exPV);
   fChain->SetBranchAddress("mu_staco_z0_exPV", &mu_staco_z0_exPV, &b_mu_staco_z0_exPV);
   fChain->SetBranchAddress("mu_staco_id_theta_exPV", &mu_staco_id_theta_exPV, &b_mu_staco_id_theta_exPV);
   fChain->SetBranchAddress("mu_staco_id_qoverp_exPV", &mu_staco_id_qoverp_exPV, &b_mu_staco_id_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_me_theta_exPV", &mu_staco_me_theta_exPV, &b_mu_staco_me_theta_exPV);
   fChain->SetBranchAddress("mu_staco_me_qoverp_exPV", &mu_staco_me_qoverp_exPV, &b_mu_staco_me_qoverp_exPV);
   fChain->SetBranchAddress("mu_staco_id_d0", &mu_staco_id_d0, &b_mu_staco_id_d0);
   fChain->SetBranchAddress("mu_staco_id_z0", &mu_staco_id_z0, &b_mu_staco_id_z0);
   fChain->SetBranchAddress("mu_staco_id_phi", &mu_staco_id_phi, &b_mu_staco_id_phi);
   fChain->SetBranchAddress("mu_staco_id_theta", &mu_staco_id_theta, &b_mu_staco_id_theta);
   fChain->SetBranchAddress("mu_staco_id_qoverp", &mu_staco_id_qoverp, &b_mu_staco_id_qoverp);
   fChain->SetBranchAddress("mu_staco_nBLHits", &mu_staco_nBLHits, &b_mu_staco_nBLHits);
   fChain->SetBranchAddress("mu_staco_nPixHits", &mu_staco_nPixHits, &b_mu_staco_nPixHits);
   fChain->SetBranchAddress("mu_staco_nSCTHits", &mu_staco_nSCTHits, &b_mu_staco_nSCTHits);
   fChain->SetBranchAddress("mu_staco_nTRTHits", &mu_staco_nTRTHits, &b_mu_staco_nTRTHits);
   fChain->SetBranchAddress("mu_staco_nPixHoles", &mu_staco_nPixHoles, &b_mu_staco_nPixHoles);
   fChain->SetBranchAddress("mu_staco_nSCTHoles", &mu_staco_nSCTHoles, &b_mu_staco_nSCTHoles);
   fChain->SetBranchAddress("mu_staco_nTRTOutliers", &mu_staco_nTRTOutliers, &b_mu_staco_nTRTOutliers);
   fChain->SetBranchAddress("mu_staco_nPixelDeadSensors", &mu_staco_nPixelDeadSensors, &b_mu_staco_nPixelDeadSensors);
   fChain->SetBranchAddress("mu_staco_nSCTDeadSensors", &mu_staco_nSCTDeadSensors, &b_mu_staco_nSCTDeadSensors);
   fChain->SetBranchAddress("mu_staco_expectBLayerHit", &mu_staco_expectBLayerHit, &b_mu_staco_expectBLayerHit);
   fChain->SetBranchAddress("mu_staco_nCSCEtaHits", &mu_staco_nCSCEtaHits, &b_mu_staco_nCSCEtaHits);
   fChain->SetBranchAddress("mu_staco_nCSCPhiHits", &mu_staco_nCSCPhiHits, &b_mu_staco_nCSCPhiHits);
   fChain->SetBranchAddress("mu_staco_nMDTEMHits", &mu_staco_nMDTEMHits, &b_mu_staco_nMDTEMHits);
   fChain->SetBranchAddress("mu_staco_nMDTEOHits", &mu_staco_nMDTEOHits, &b_mu_staco_nMDTEOHits);
   fChain->SetBranchAddress("mu_staco_trackIPEstimate_d0_unbiasedpvunbiased", &mu_staco_trackIPEstimate_d0_unbiasedpvunbiased, &b_mu_staco_trackIPEstimate_d0_unbiasedpvunbiased);
   fChain->SetBranchAddress("mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased", &mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased, &b_mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased);
   fChain->SetBranchAddress("mu_staco_truth_type", &mu_staco_truth_type, &b_mu_staco_truth_type);
   fChain->SetBranchAddress("mu_staco_truth_mothertype", &mu_staco_truth_mothertype, &b_mu_staco_truth_mothertype);
   fChain->SetBranchAddress("mu_staco_EFCB_index", &mu_staco_EFCB_index, &b_mu_staco_EFCB_index);
   fChain->SetBranchAddress("mu_calo_n", &mu_calo_n, &b_mu_calo_n);
   fChain->SetBranchAddress("mu_calo_E", &mu_calo_E, &b_mu_calo_E);
   fChain->SetBranchAddress("mu_calo_pt", &mu_calo_pt, &b_mu_calo_pt);
   fChain->SetBranchAddress("mu_calo_eta", &mu_calo_eta, &b_mu_calo_eta);
   fChain->SetBranchAddress("mu_calo_phi", &mu_calo_phi, &b_mu_calo_phi);
   fChain->SetBranchAddress("mu_calo_charge", &mu_calo_charge, &b_mu_calo_charge);
   fChain->SetBranchAddress("mu_calo_author", &mu_calo_author, &b_mu_calo_author);
   fChain->SetBranchAddress("mu_calo_etcone20", &mu_calo_etcone20, &b_mu_calo_etcone20);
   fChain->SetBranchAddress("mu_calo_etcone30", &mu_calo_etcone30, &b_mu_calo_etcone30);
   fChain->SetBranchAddress("mu_calo_ptcone20", &mu_calo_ptcone20, &b_mu_calo_ptcone20);
   fChain->SetBranchAddress("mu_calo_ptcone30", &mu_calo_ptcone30, &b_mu_calo_ptcone30);
   fChain->SetBranchAddress("mu_calo_caloMuonIdTag", &mu_calo_caloMuonIdTag, &b_mu_calo_caloMuonIdTag);
   fChain->SetBranchAddress("mu_calo_caloLRLikelihood", &mu_calo_caloLRLikelihood, &b_mu_calo_caloLRLikelihood);
   fChain->SetBranchAddress("mu_calo_isStandAloneMuon", &mu_calo_isStandAloneMuon, &b_mu_calo_isStandAloneMuon);
   fChain->SetBranchAddress("mu_calo_isCombinedMuon", &mu_calo_isCombinedMuon, &b_mu_calo_isCombinedMuon);
   fChain->SetBranchAddress("mu_calo_isSegmentTaggedMuon", &mu_calo_isSegmentTaggedMuon, &b_mu_calo_isSegmentTaggedMuon);
   fChain->SetBranchAddress("mu_calo_d0_exPV", &mu_calo_d0_exPV, &b_mu_calo_d0_exPV);
   fChain->SetBranchAddress("mu_calo_z0_exPV", &mu_calo_z0_exPV, &b_mu_calo_z0_exPV);
   fChain->SetBranchAddress("mu_calo_id_theta_exPV", &mu_calo_id_theta_exPV, &b_mu_calo_id_theta_exPV);
   fChain->SetBranchAddress("mu_calo_id_qoverp_exPV", &mu_calo_id_qoverp_exPV, &b_mu_calo_id_qoverp_exPV);
   fChain->SetBranchAddress("mu_calo_me_theta_exPV", &mu_calo_me_theta_exPV, &b_mu_calo_me_theta_exPV);
   fChain->SetBranchAddress("mu_calo_me_qoverp_exPV", &mu_calo_me_qoverp_exPV, &b_mu_calo_me_qoverp_exPV);
   fChain->SetBranchAddress("mu_calo_id_d0", &mu_calo_id_d0, &b_mu_calo_id_d0);
   fChain->SetBranchAddress("mu_calo_id_z0", &mu_calo_id_z0, &b_mu_calo_id_z0);
   fChain->SetBranchAddress("mu_calo_id_phi", &mu_calo_id_phi, &b_mu_calo_id_phi);
   fChain->SetBranchAddress("mu_calo_id_theta", &mu_calo_id_theta, &b_mu_calo_id_theta);
   fChain->SetBranchAddress("mu_calo_id_qoverp", &mu_calo_id_qoverp, &b_mu_calo_id_qoverp);
   fChain->SetBranchAddress("mu_calo_nBLHits", &mu_calo_nBLHits, &b_mu_calo_nBLHits);
   fChain->SetBranchAddress("mu_calo_nPixHits", &mu_calo_nPixHits, &b_mu_calo_nPixHits);
   fChain->SetBranchAddress("mu_calo_nSCTHits", &mu_calo_nSCTHits, &b_mu_calo_nSCTHits);
   fChain->SetBranchAddress("mu_calo_nTRTHits", &mu_calo_nTRTHits, &b_mu_calo_nTRTHits);
   fChain->SetBranchAddress("mu_calo_nPixHoles", &mu_calo_nPixHoles, &b_mu_calo_nPixHoles);
   fChain->SetBranchAddress("mu_calo_nSCTHoles", &mu_calo_nSCTHoles, &b_mu_calo_nSCTHoles);
   fChain->SetBranchAddress("mu_calo_nTRTOutliers", &mu_calo_nTRTOutliers, &b_mu_calo_nTRTOutliers);
   fChain->SetBranchAddress("mu_calo_nPixelDeadSensors", &mu_calo_nPixelDeadSensors, &b_mu_calo_nPixelDeadSensors);
   fChain->SetBranchAddress("mu_calo_nSCTDeadSensors", &mu_calo_nSCTDeadSensors, &b_mu_calo_nSCTDeadSensors);
   fChain->SetBranchAddress("mu_calo_expectBLayerHit", &mu_calo_expectBLayerHit, &b_mu_calo_expectBLayerHit);
   fChain->SetBranchAddress("mu_calo_nCSCEtaHits", &mu_calo_nCSCEtaHits, &b_mu_calo_nCSCEtaHits);
   fChain->SetBranchAddress("mu_calo_nCSCPhiHits", &mu_calo_nCSCPhiHits, &b_mu_calo_nCSCPhiHits);
   fChain->SetBranchAddress("mu_calo_nMDTEMHits", &mu_calo_nMDTEMHits, &b_mu_calo_nMDTEMHits);
   fChain->SetBranchAddress("mu_calo_nMDTEOHits", &mu_calo_nMDTEOHits, &b_mu_calo_nMDTEOHits);
   fChain->SetBranchAddress("mu_calo_trackIPEstimate_d0_unbiasedpvunbiased", &mu_calo_trackIPEstimate_d0_unbiasedpvunbiased, &b_mu_calo_trackIPEstimate_d0_unbiasedpvunbiased);
   fChain->SetBranchAddress("mu_calo_trackIPEstimate_sigd0_unbiasedpvunbiased", &mu_calo_trackIPEstimate_sigd0_unbiasedpvunbiased, &b_mu_calo_trackIPEstimate_sigd0_unbiasedpvunbiased);
   fChain->SetBranchAddress("mu_calo_truth_type", &mu_calo_truth_type, &b_mu_calo_truth_type);
   fChain->SetBranchAddress("mu_calo_truth_mothertype", &mu_calo_truth_mothertype, &b_mu_calo_truth_mothertype);
   fChain->SetBranchAddress("vxp_n", &vxp_n, &b_vxp_n);
   fChain->SetBranchAddress("vxp_nTracks", &vxp_nTracks, &b_vxp_nTracks);
   fChain->SetBranchAddress("mcevt_weight", &mcevt_weight, &b_mcevt_weight);
   fChain->SetBranchAddress("mc_n", &mc_n, &b_mc_n);
   fChain->SetBranchAddress("mc_children", &mc_children, &b_mc_children);
   fChain->SetBranchAddress("mc_pdgId", &mc_pdgId, &b_mc_pdgId);
   fChain->SetBranchAddress("mc_child_index", &mc_child_index, &b_mc_child_index);
   fChain->SetBranchAddress("trig_DB_SMK", &trig_DB_SMK, &b_trig_DB_SMK);
   fChain->SetBranchAddress("trig_L1_mu_eta", &trig_L1_mu_eta, &b_trig_L1_mu_eta);
   fChain->SetBranchAddress("trig_L1_mu_phi", &trig_L1_mu_phi, &b_trig_L1_mu_phi);
   fChain->SetBranchAddress("trig_L1_mu_thrName", &trig_L1_mu_thrName, &b_trig_L1_mu_thrName);
   fChain->SetBranchAddress("trig_L2_muonfeature_eta", &trig_L2_muonfeature_eta, &b_trig_L2_muonfeature_eta);
   fChain->SetBranchAddress("trig_L2_muonfeature_phi", &trig_L2_muonfeature_phi, &b_trig_L2_muonfeature_phi);
   fChain->SetBranchAddress("trig_L2_combmuonfeature_eta", &trig_L2_combmuonfeature_eta, &b_trig_L2_combmuonfeature_eta);
   fChain->SetBranchAddress("trig_L2_combmuonfeature_phi", &trig_L2_combmuonfeature_phi, &b_trig_L2_combmuonfeature_phi);
   fChain->SetBranchAddress("trig_EF_trigmuonef_track_SA_pt", &trig_EF_trigmuonef_track_SA_pt, &b_trig_EF_trigmuonef_track_SA_pt);
   fChain->SetBranchAddress("trig_EF_trigmuonef_track_SA_eta", &trig_EF_trigmuonef_track_SA_eta, &b_trig_EF_trigmuonef_track_SA_eta);
   fChain->SetBranchAddress("trig_EF_trigmuonef_track_SA_phi", &trig_EF_trigmuonef_track_SA_phi, &b_trig_EF_trigmuonef_track_SA_phi);
   fChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_pt", &trig_EF_trigmuonef_track_CB_pt, &b_trig_EF_trigmuonef_track_CB_pt);
   fChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_eta", &trig_EF_trigmuonef_track_CB_eta, &b_trig_EF_trigmuonef_track_CB_eta);
   fChain->SetBranchAddress("trig_EF_trigmuonef_track_CB_phi", &trig_EF_trigmuonef_track_CB_phi, &b_trig_EF_trigmuonef_track_CB_phi);
   fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_pt", &trig_EF_trigmugirl_track_CB_pt, &b_trig_EF_trigmugirl_track_CB_pt);
   fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_eta", &trig_EF_trigmugirl_track_CB_eta, &b_trig_EF_trigmugirl_track_CB_eta);
   fChain->SetBranchAddress("trig_EF_trigmugirl_track_CB_phi", &trig_EF_trigmugirl_track_CB_phi, &b_trig_EF_trigmugirl_track_CB_phi);
   fChain->SetBranchAddress("trig_Nav_n", &trig_Nav_n, &b_trig_Nav_n);
   fChain->SetBranchAddress("trig_Nav_chain_ChainId", &trig_Nav_chain_ChainId, &b_trig_Nav_chain_ChainId);
   fChain->SetBranchAddress("trig_Nav_chain_RoIType", &trig_Nav_chain_RoIType, &b_trig_Nav_chain_RoIType);
   fChain->SetBranchAddress("trig_Nav_chain_RoIIndex", &trig_Nav_chain_RoIIndex, &b_trig_Nav_chain_RoIIndex);
   fChain->SetBranchAddress("trig_RoI_L2_mu_MuonFeature", &trig_RoI_L2_mu_MuonFeature, &b_trig_RoI_L2_mu_MuonFeature);
   fChain->SetBranchAddress("trig_RoI_L2_mu_CombinedMuonFeature", &trig_RoI_L2_mu_CombinedMuonFeature, &b_trig_RoI_L2_mu_CombinedMuonFeature);
   fChain->SetBranchAddress("trig_RoI_L2_mu_CombinedMuonFeatureStatus", &trig_RoI_L2_mu_CombinedMuonFeatureStatus, &b_trig_RoI_L2_mu_CombinedMuonFeatureStatus);
   fChain->SetBranchAddress("trig_RoI_L2_mu_Muon_ROI", &trig_RoI_L2_mu_Muon_ROI, &b_trig_RoI_L2_mu_Muon_ROI);
   fChain->SetBranchAddress("trig_RoI_EF_mu_Muon_ROI", &trig_RoI_EF_mu_Muon_ROI, &b_trig_RoI_EF_mu_Muon_ROI);
   fChain->SetBranchAddress("trig_RoI_EF_mu_TrigMuonEFInfoContainer", &trig_RoI_EF_mu_TrigMuonEFInfoContainer, &b_trig_RoI_EF_mu_TrigMuonEFInfoContainer);
   fChain->SetBranchAddress("trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus", &trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus, &b_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus);
   fChain->SetBranchAddress("trig_EF_el_n", &trig_EF_el_n, &b_trig_EF_el_n);
   fChain->SetBranchAddress("trig_EF_el_eta", &trig_EF_el_eta, &b_trig_EF_el_eta);
   fChain->SetBranchAddress("trig_EF_el_phi", &trig_EF_el_phi, &b_trig_EF_el_phi);
   fChain->SetBranchAddress("trig_RoI_EF_e_egammaContainer_egamma_Electrons", &trig_RoI_EF_e_egammaContainer_egamma_Electrons, &b_trig_RoI_EF_e_egammaContainer_egamma_Electrons);
   fChain->SetBranchAddress("trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus", &trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus, &b_trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus);
   fChain->SetBranchAddress("EF_2e12Tvh_medium", &EF_2e12Tvh_medium, &b_EF_2e12Tvh_medium);
   fChain->SetBranchAddress("EF_e22vh_medium1", &EF_e22vh_medium1, &b_EF_e22vh_medium1);
   Notify();
}

Bool_t THiggsD3PD::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void THiggsD3PD::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t THiggsD3PD::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef THiggsD3PD_cxx
