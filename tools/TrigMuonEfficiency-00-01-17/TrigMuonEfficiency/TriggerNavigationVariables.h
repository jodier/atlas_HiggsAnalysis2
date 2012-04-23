#ifndef __TriggerNavigationVariables_h__
#define __TriggerNavigationVariables_h__

#include <vector>
#include <limits>



class TriggerNavigationVariables
{
  public:
    TriggerNavigationVariables() :
      hasSetVariables(false),
      trig_DB_SMK(0),
      trig_Nav_n(0),
      trig_Nav_chain_ChainId(0),
      trig_Nav_chain_RoIType(0),
      trig_Nav_chain_RoIIndex(0),
      /* electron */
      trig_RoI_EF_e_egammaContainer_egamma_Electrons(0),
      trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus(0),
      trig_EF_el_n(0),
      trig_EF_el_eta(0),
      trig_EF_el_phi(0),
      /* muon */
      trig_RoI_EF_mu_Muon_ROI(0),
      trig_RoI_EF_mu_TrigMuonEFInfoContainer(0),
      trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(0),
      trig_RoI_L2_mu_CombinedMuonFeature(0),
      trig_RoI_L2_mu_CombinedMuonFeatureStatus(0),
      trig_RoI_L2_mu_MuonFeature(0),
      trig_RoI_L2_mu_Muon_ROI(0),
      trig_EF_trigmuonef_track_CB_pt(0),
      trig_EF_trigmuonef_track_CB_eta(0),
      trig_EF_trigmuonef_track_CB_phi(0),
      trig_EF_trigmuonef_track_SA_pt(0),
      trig_EF_trigmuonef_track_SA_eta(0),
      trig_EF_trigmuonef_track_SA_phi(0),
      trig_EF_trigmugirl_track_CB_pt(0),
      trig_EF_trigmugirl_track_CB_eta(0),
      trig_EF_trigmugirl_track_CB_phi(0),
      trig_L2_combmuonfeature_eta(0),
      trig_L2_combmuonfeature_phi(0),
      trig_L2_muonfeature_eta(0),
      trig_L2_muonfeature_phi(0),
      trig_L1_mu_eta(0),
      trig_L1_mu_phi(0),
      trig_L1_mu_thrName(0) {}

    TriggerNavigationVariables(
      unsigned int &trig_DB_SMK_,
      int &trig_Nav_n_,
      std::vector<short> *&trig_Nav_chain_ChainId_,
      std::vector<std::vector<int> > *&trig_Nav_chain_RoIType_,
      std::vector<std::vector<int> > *&trig_Nav_chain_RoIIndex_,
      /* electron */
      std::vector<std::vector<int> > *&trig_RoI_EF_e_egammaContainer_egamma_Electrons_,
      std::vector<std::vector<int> > *&trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus_,
      int &trig_EF_el_n_,
      std::vector<float> *&trig_EF_el_eta_,
      std::vector<float> *&trig_EF_el_phi_,
      /* muon */
      std::vector<int> *&trig_RoI_EF_mu_Muon_ROI_,
      std::vector<std::vector<int> > *&trig_RoI_EF_mu_TrigMuonEFInfoContainer_,
      std::vector<std::vector<int> > *&trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus_,
      std::vector<int> *&trig_RoI_L2_mu_CombinedMuonFeature_,
      std::vector<int> *&trig_RoI_L2_mu_CombinedMuonFeatureStatus_,
      std::vector<int> *&trig_RoI_L2_mu_MuonFeature_,
      std::vector<int> *&trig_RoI_L2_mu_Muon_ROI_,
      std::vector<std::vector<float> > *&trig_EF_trigmuonef_track_CB_pt_,
      std::vector<std::vector<float> > *&trig_EF_trigmuonef_track_CB_eta_,
      std::vector<std::vector<float> > *&trig_EF_trigmuonef_track_CB_phi_,
      std::vector<std::vector<float> > *&trig_EF_trigmuonef_track_SA_pt_,
      std::vector<std::vector<float> > *&trig_EF_trigmuonef_track_SA_eta_,
      std::vector<std::vector<float> > *&trig_EF_trigmuonef_track_SA_phi_,
      std::vector<std::vector<float> > *&trig_EF_trigmugirl_track_CB_pt_,
      std::vector<std::vector<float> > *&trig_EF_trigmugirl_track_CB_eta_,
      std::vector<std::vector<float> > *&trig_EF_trigmugirl_track_CB_phi_,
      std::vector<float> *&trig_L2_combmuonfeature_eta_,
      std::vector<float> *&trig_L2_combmuonfeature_phi_,
      std::vector<float> *&trig_L2_muonfeature_eta_,
      std::vector<float> *&trig_L2_muonfeature_phi_,
      std::vector<float> *&trig_L1_mu_eta_,
      std::vector<float> *&trig_L1_mu_phi_,
      std::vector<std::string> *&trig_L1_mu_thrName_
    ) :
      hasSetVariables(true),
      trig_DB_SMK(&trig_DB_SMK_),
      trig_Nav_n(&trig_Nav_n_),
      trig_Nav_chain_ChainId(trig_Nav_chain_ChainId_),
      trig_Nav_chain_RoIType(trig_Nav_chain_RoIType_),
      trig_Nav_chain_RoIIndex(trig_Nav_chain_RoIIndex_),
      /* electron */
      trig_RoI_EF_e_egammaContainer_egamma_Electrons(trig_RoI_EF_e_egammaContainer_egamma_Electrons_),
      trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus(trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus_),
      trig_EF_el_n(&trig_EF_el_n_),
      trig_EF_el_eta(trig_EF_el_eta_),
      trig_EF_el_phi(trig_EF_el_phi_),
      /* muon */
      trig_RoI_EF_mu_Muon_ROI(trig_RoI_EF_mu_Muon_ROI_),
      trig_RoI_EF_mu_TrigMuonEFInfoContainer(trig_RoI_EF_mu_TrigMuonEFInfoContainer_),
      trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus_),
      trig_RoI_L2_mu_CombinedMuonFeature(trig_RoI_L2_mu_CombinedMuonFeature_),
      trig_RoI_L2_mu_CombinedMuonFeatureStatus(trig_RoI_L2_mu_CombinedMuonFeatureStatus_),
      trig_RoI_L2_mu_MuonFeature(trig_RoI_L2_mu_MuonFeature_),
      trig_RoI_L2_mu_Muon_ROI(trig_RoI_L2_mu_Muon_ROI_),
      trig_EF_trigmuonef_track_CB_pt(trig_EF_trigmuonef_track_CB_pt_),
      trig_EF_trigmuonef_track_CB_eta(trig_EF_trigmuonef_track_CB_eta_),
      trig_EF_trigmuonef_track_CB_phi(trig_EF_trigmuonef_track_CB_phi_),
      trig_EF_trigmuonef_track_SA_pt(trig_EF_trigmuonef_track_SA_pt_),
      trig_EF_trigmuonef_track_SA_eta(trig_EF_trigmuonef_track_SA_eta_),
      trig_EF_trigmuonef_track_SA_phi(trig_EF_trigmuonef_track_SA_phi_),
      trig_EF_trigmugirl_track_CB_pt(trig_EF_trigmugirl_track_CB_pt_),
      trig_EF_trigmugirl_track_CB_eta(trig_EF_trigmugirl_track_CB_eta_),
      trig_EF_trigmugirl_track_CB_phi(trig_EF_trigmugirl_track_CB_phi_),
      trig_L2_combmuonfeature_eta(trig_L2_combmuonfeature_eta_),
      trig_L2_combmuonfeature_phi(trig_L2_combmuonfeature_phi_),
      trig_L2_muonfeature_eta(trig_L2_muonfeature_eta_),
      trig_L2_muonfeature_phi(trig_L2_muonfeature_phi_),
      trig_L1_mu_eta(trig_L1_mu_eta_),
      trig_L1_mu_phi(trig_L1_mu_phi_),
      trig_L1_mu_thrName(trig_L1_mu_thrName_) {}

    ~TriggerNavigationVariables() {}
 

    void set_trig_DB_SMK(unsigned int &x) {trig_DB_SMK = &x;}
    void set_trig_Nav_n(int &x) {trig_Nav_n = &x;}
    void set_trig_Nav_chain_ChainId(std::vector<short> *&x) {trig_Nav_chain_ChainId = x;}
    void set_trig_Nav_chain_RoIType(std::vector<std::vector<int> > *&x) {trig_Nav_chain_RoIType = x;}
    void set_trig_Nav_chain_RoIIndex(std::vector<std::vector<int> > *&x) {trig_Nav_chain_RoIIndex = x;}

    /* electron */
    void set_trig_RoI_EF_e_egammaContainer_egamma_Electrons(std::vector<std::vector<int> > *&x) {trig_RoI_EF_e_egammaContainer_egamma_Electrons = x;}
    void set_trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus(std::vector<std::vector<int> > *&x) {trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus = x;}
    void set_trig_EF_el_n(int &x) {trig_EF_el_n = &x;}
    void set_trig_EF_el_eta(std::vector<float> *&x) {trig_EF_el_eta = x;}
    void set_trig_EF_el_phi(std::vector<float> *&x) {trig_EF_el_phi = x;}

    /* muon */
    void set_trig_RoI_EF_mu_Muon_ROI(std::vector<int> *&x) {trig_RoI_EF_mu_Muon_ROI = x;}
    void set_trig_RoI_EF_mu_TrigMuonEFInfoContainer(std::vector<std::vector<int> > *&x) {trig_RoI_EF_mu_TrigMuonEFInfoContainer = x;}
    void set_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(std::vector<std::vector<int> > *&x) {trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus = x;}
    void set_trig_RoI_L2_mu_CombinedMuonFeature(std::vector<int> *&x) {trig_RoI_L2_mu_CombinedMuonFeature = x;}
    void set_trig_RoI_L2_mu_CombinedMuonFeatureStatus(std::vector<int> *&x) {trig_RoI_L2_mu_CombinedMuonFeatureStatus = x;}
    void set_trig_RoI_L2_mu_MuonFeature(std::vector<int> *&x) {trig_RoI_L2_mu_MuonFeature = x;}
    void set_trig_RoI_L2_mu_Muon_ROI(std::vector<int> *&x) {trig_RoI_L2_mu_Muon_ROI = x;}
    void set_trig_EF_trigmuonef_track_CB_pt(std::vector<std::vector<float> > *&x) {trig_EF_trigmuonef_track_CB_pt = x;}
    void set_trig_EF_trigmuonef_track_CB_eta(std::vector<std::vector<float> > *&x) {trig_EF_trigmuonef_track_CB_eta = x;}
    void set_trig_EF_trigmuonef_track_CB_phi(std::vector<std::vector<float> > *&x) {trig_EF_trigmuonef_track_CB_phi = x;}
    void set_trig_EF_trigmuonef_track_SA_pt(std::vector<std::vector<float> > *&x) {trig_EF_trigmuonef_track_SA_pt = x;}
    void set_trig_EF_trigmuonef_track_SA_eta(std::vector<std::vector<float> > *&x) {trig_EF_trigmuonef_track_SA_eta = x;}
    void set_trig_EF_trigmuonef_track_SA_phi(std::vector<std::vector<float> > *&x) {trig_EF_trigmuonef_track_SA_phi = x;}
    void set_trig_EF_trigmugirl_track_CB_pt(std::vector<std::vector<float> > *&x) {trig_EF_trigmugirl_track_CB_pt = x;}
    void set_trig_EF_trigmugirl_track_CB_eta(std::vector<std::vector<float> > *&x) {trig_EF_trigmugirl_track_CB_eta = x;}
    void set_trig_EF_trigmugirl_track_CB_phi(std::vector<std::vector<float> > *&x) {trig_EF_trigmugirl_track_CB_phi = x;}
    void set_trig_L2_combmuonfeature_eta(std::vector<float> *&x) {trig_L2_combmuonfeature_eta = x;}
    void set_trig_L2_combmuonfeature_phi(std::vector<float> *&x) {trig_L2_combmuonfeature_phi = x;}
    void set_trig_L2_muonfeature_eta(std::vector<float> *&x) {trig_L2_muonfeature_eta = x;}
    void set_trig_L2_muonfeature_phi(std::vector<float> *&x) {trig_L2_muonfeature_phi = x;}
    void set_trig_L1_mu_eta(std::vector<float> *&x) {trig_L1_mu_eta = x;}
    void set_trig_L1_mu_phi(std::vector<float> *&x) {trig_L1_mu_phi = x;}
    void set_trig_L1_mu_thrName(std::vector<std::string> *&x) {trig_L1_mu_thrName = x;}
    
    bool isValid() {
      if (hasSetVariables) return true;

      if (trig_DB_SMK == 0) return false;
      if (trig_Nav_n == 0) return false;
      if (trig_Nav_chain_ChainId == 0) return false;
      if (trig_Nav_chain_RoIType == 0) return false;
      if (trig_Nav_chain_RoIIndex == 0) return false;
      /* electron */
      if (trig_RoI_EF_e_egammaContainer_egamma_Electrons == 0) return false;
      if (trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus == 0) return false;
      if (trig_EF_el_n == 0) return false;
      if (trig_EF_el_eta == 0) return false;
      if (trig_EF_el_phi == 0) return false;
      /* muon */
      if (trig_RoI_EF_mu_Muon_ROI == 0) return false;
      if (trig_RoI_EF_mu_TrigMuonEFInfoContainer == 0) return false;
      if (trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus == 0) return false;
      if (trig_RoI_L2_mu_CombinedMuonFeature == 0) return false;
      if (trig_RoI_L2_mu_CombinedMuonFeatureStatus == 0) return false;
      if (trig_RoI_L2_mu_MuonFeature == 0) return false;
      if (trig_RoI_L2_mu_Muon_ROI == 0) return false;
      if (trig_EF_trigmuonef_track_CB_pt == 0) return false;
      if (trig_EF_trigmuonef_track_CB_eta == 0) return false;
      if (trig_EF_trigmuonef_track_CB_phi == 0) return false;
      if (trig_EF_trigmuonef_track_SA_pt == 0) return false;
      if (trig_EF_trigmuonef_track_SA_eta == 0) return false;
      if (trig_EF_trigmuonef_track_SA_phi == 0) return false;
      if (trig_EF_trigmugirl_track_CB_pt == 0) return false;
      if (trig_EF_trigmugirl_track_CB_eta == 0) return false;
      if (trig_EF_trigmugirl_track_CB_phi == 0) return false;
      if (trig_L2_combmuonfeature_eta == 0) return false;
      if (trig_L2_combmuonfeature_phi == 0) return false;
      if (trig_L2_muonfeature_eta == 0) return false;
      if (trig_L2_muonfeature_phi == 0) return false;
      if (trig_L1_mu_eta == 0) return false;
      if (trig_L1_mu_phi == 0) return false;
      if (trig_L1_mu_thrName == 0) return false;

      hasSetVariables = true;
      return true;
    };

  private:
    bool hasSetVariables;

  public:
    unsigned int *trig_DB_SMK;
    int *trig_Nav_n;
    std::vector<short> *trig_Nav_chain_ChainId;
    std::vector<std::vector<int> > *trig_Nav_chain_RoIType;
    std::vector<std::vector<int> > *trig_Nav_chain_RoIIndex;

    /* electron */
    std::vector<std::vector<int> > *trig_RoI_EF_e_egammaContainer_egamma_Electrons;
    std::vector<std::vector<int> > *trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus;
    int *trig_EF_el_n;
    std::vector<float> *trig_EF_el_eta;
    std::vector<float> *trig_EF_el_phi;

    /* muon */
    std::vector<int> *trig_RoI_EF_mu_Muon_ROI;
    std::vector<std::vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainer;
    std::vector<std::vector<int> > *trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus;
    std::vector<int> *trig_RoI_L2_mu_CombinedMuonFeature;
    std::vector<int> *trig_RoI_L2_mu_CombinedMuonFeatureStatus;
    std::vector<int> *trig_RoI_L2_mu_MuonFeature;
    std::vector<int> *trig_RoI_L2_mu_Muon_ROI;
    std::vector<std::vector<float> > *trig_EF_trigmuonef_track_CB_pt;
    std::vector<std::vector<float> > *trig_EF_trigmuonef_track_CB_eta;
    std::vector<std::vector<float> > *trig_EF_trigmuonef_track_CB_phi;
    std::vector<std::vector<float> > *trig_EF_trigmuonef_track_SA_pt;
    std::vector<std::vector<float> > *trig_EF_trigmuonef_track_SA_eta;
    std::vector<std::vector<float> > *trig_EF_trigmuonef_track_SA_phi;
    std::vector<std::vector<float> > *trig_EF_trigmugirl_track_CB_pt;
    std::vector<std::vector<float> > *trig_EF_trigmugirl_track_CB_eta;
    std::vector<std::vector<float> > *trig_EF_trigmugirl_track_CB_phi;
    std::vector<float> *trig_L2_combmuonfeature_eta;
    std::vector<float> *trig_L2_combmuonfeature_phi;
    std::vector<float> *trig_L2_muonfeature_eta;
    std::vector<float> *trig_L2_muonfeature_phi;
    std::vector<float> *trig_L1_mu_eta;
    std::vector<float> *trig_L1_mu_phi;
    std::vector<std::string> *trig_L1_mu_thrName;
};
#endif // __TriggerNavigationVariables_h__
