void D3PDSkimmer_GSF(void)
{
	TChain *chain = new TChain("physics");

	chain->Add("/quark1/tiouchi/data11_7TeV.00191715.physics_Muons.merge.NTUP_HSG2.f414_m1025_p761_p762_tid577625_00/NTUP_HSG2.577625._000040.root");

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("*", 0);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("RunNumber", 1);
	chain->SetBranchStatus("EventNumber", 1);
	chain->SetBranchStatus("lbn", 1);
	chain->SetBranchStatus("larError", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("actualIntPerXing", 1);
	chain->SetBranchStatus("averageIntPerXing", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("vxp_n", 1);
	chain->SetBranchStatus("vxp_nTracks", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mc_n", 1);
	chain->SetBranchStatus("mc_pdgId", 1);
	chain->SetBranchStatus("mc_children", 1);
	chain->SetBranchStatus("mc_child_index", 1);
	chain->SetBranchStatus("mc_channel_number", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mcevt_weight", 1);

	/*-----------------------------------------------------------------*/
	/* ELECTRONS GSF						   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("el_GSF_author", 1);
	chain->SetBranchStatus("el_GSF_charge", 1);
	chain->SetBranchStatus("el_GSF_cl_E", 1);
	chain->SetBranchStatus("el_GSF_cl_eta", 1);
	chain->SetBranchStatus("el_GSF_cl_phi", 1);
	chain->SetBranchStatus("el_GSF_cl_pt", 1);
	chain->SetBranchStatus("el_GSF_EF_index", 1);
	chain->SetBranchStatus("el_GSF_etap", 1);
	chain->SetBranchStatus("el_GSF_etas2", 1);
	chain->SetBranchStatus("el_GSF_Etcone20", 1);
	chain->SetBranchStatus("el_GSF_Etcone30", 1);
	chain->SetBranchStatus("el_GSF_loosePP", 1);
	chain->SetBranchStatus("el_GSF_medium", 1);
	chain->SetBranchStatus("el_GSF_n", 1);
	chain->SetBranchStatus("el_GSF_nPixHits", 1);
	chain->SetBranchStatus("el_GSF_nSCTHits", 1);
	chain->SetBranchStatus("el_GSF_OQ", 1);
	chain->SetBranchStatus("el_GSF_type", 1);
	chain->SetBranchStatus("el_GSF_typebkg", 1);
	chain->SetBranchStatus("el_GSF_origin", 1);
	chain->SetBranchStatus("el_GSF_originbkg", 1);
	chain->SetBranchStatus("el_GSF_ptcone20", 1);
	chain->SetBranchStatus("el_GSF_ptcone30", 1);
	chain->SetBranchStatus("el_GSF_tight", 1);
	chain->SetBranchStatus("el_GSF_trackd0", 1);
	chain->SetBranchStatus("el_GSF_trackd0pvunbiased", 1);
	chain->SetBranchStatus("el_GSF_tracketa", 1);
	chain->SetBranchStatus("el_GSF_trackphi", 1);
	chain->SetBranchStatus("el_GSF_trackpt", 1);
	chain->SetBranchStatus("el_GSF_trackqoverp", 1);
	chain->SetBranchStatus("el_GSF_tracksigd0pvunbiased", 1);
	chain->SetBranchStatus("el_GSF_tracktheta", 1);
	chain->SetBranchStatus("el_GSF_trackz0", 1);
	chain->SetBranchStatus("el_GSF_trackz0pvunbiased", 1);
	chain->SetBranchStatus("el_GSF_Ethad", 1);
	chain->SetBranchStatus("el_GSF_Ethad1", 1);
	chain->SetBranchStatus("el_GSF_reta", 1);
	chain->SetBranchStatus("el_GSF_rphi", 1);
	chain->SetBranchStatus("el_GSF_weta2", 1);
	chain->SetBranchStatus("el_GSF_f1", 1);
	chain->SetBranchStatus("el_GSF_wstot", 1);
	chain->SetBranchStatus("el_GSF_emaxs1", 1);
	chain->SetBranchStatus("el_GSF_Emax2", 1);
	chain->SetBranchStatus("el_GSF_deltaeta1", 1);
	chain->SetBranchStatus("el_GSF_nBLHits", 1);
	chain->SetBranchStatus("el_GSF_nBLayerOutliers", 1);
	chain->SetBranchStatus("el_GSF_nSiHits", 1);
	chain->SetBranchStatus("el_GSF_nPixelOutliers", 1);
	chain->SetBranchStatus("el_GSF_nSCTOutliers", 1);
	chain->SetBranchStatus("el_GSF_nTRTHits", 1);
	chain->SetBranchStatus("el_GSF_nTRTOutliers", 1);
	chain->SetBranchStatus("el_GSF_nTRTHighTHits", 1);
	chain->SetBranchStatus("el_GSF_nTRTHighTOutliers", 1);
	chain->SetBranchStatus("el_GSF_truth_mothertype", 1);
	chain->SetBranchStatus("el_GSF_truth_type", 1);

	/*-----------------------------------------------------------------*/
	/* MUONS STACO							   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mu_staco_author", 1);
	chain->SetBranchStatus("mu_staco_charge", 1);
	chain->SetBranchStatus("mu_staco_E", 1);
	chain->SetBranchStatus("mu_staco_EFCB_index", 1);
	chain->SetBranchStatus("mu_staco_eta", 1);
	chain->SetBranchStatus("mu_staco_etcone20", 1);
	chain->SetBranchStatus("mu_staco_etcone30", 1);
	chain->SetBranchStatus("mu_staco_expectBLayerHit", 1);
	chain->SetBranchStatus("mu_staco_id_d0", 1);
	chain->SetBranchStatus("mu_staco_id_phi", 1);
	chain->SetBranchStatus("mu_staco_id_qoverp", 1);
	chain->SetBranchStatus("mu_staco_id_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_staco_id_theta", 1);
	chain->SetBranchStatus("mu_staco_id_theta_exPV", 1);
	chain->SetBranchStatus("mu_staco_id_z0", 1);
	chain->SetBranchStatus("mu_staco_isStandAloneMuon", 1);
	chain->SetBranchStatus("mu_staco_isCombinedMuon", 1);
	chain->SetBranchStatus("mu_staco_isSegmentTaggedMuon", 1);
	chain->SetBranchStatus("mu_staco_me_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_staco_me_theta_exPV", 1);
	chain->SetBranchStatus("mu_staco_n", 1);
	chain->SetBranchStatus("mu_staco_nBLHits", 1);
	chain->SetBranchStatus("mu_staco_nPixelDeadSensors", 1);
	chain->SetBranchStatus("mu_staco_nPixHits", 1);
	chain->SetBranchStatus("mu_staco_nPixHoles", 1);
	chain->SetBranchStatus("mu_staco_nSCTDeadSensors", 1);
	chain->SetBranchStatus("mu_staco_nSCTHits", 1);
	chain->SetBranchStatus("mu_staco_nSCTHoles", 1);
	chain->SetBranchStatus("mu_staco_nTRTHits", 1);
	chain->SetBranchStatus("mu_staco_nTRTOutliers", 1);
	chain->SetBranchStatus("mu_staco_nCSCEtaHits", 1);
	chain->SetBranchStatus("mu_staco_nCSCPhiHits", 1);
	chain->SetBranchStatus("mu_staco_nMDTEMHits", 1);
	chain->SetBranchStatus("mu_staco_nMDTEOHits", 1);
	chain->SetBranchStatus("mu_staco_phi", 1);
	chain->SetBranchStatus("mu_staco_pt", 1);
	chain->SetBranchStatus("mu_staco_ptcone20", 1);
	chain->SetBranchStatus("mu_staco_ptcone30", 1);
	chain->SetBranchStatus("mu_staco_tight", 1);
	chain->SetBranchStatus("mu_staco_d0_exPV", 1);
	chain->SetBranchStatus("mu_staco_z0_exPV", 1);
	chain->SetBranchStatus("mu_staco_trackIPEstimate_d0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_staco_truth_mothertype", 1);
	chain->SetBranchStatus("mu_staco_truth_type", 1);

	/*-----------------------------------------------------------------*/
	/* MUONS muid							   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mu_muid_author", 1);
	chain->SetBranchStatus("mu_muid_charge", 1);
	chain->SetBranchStatus("mu_muid_E", 1);
	chain->SetBranchStatus("mu_muid_EFCB_index", 1);
	chain->SetBranchStatus("mu_muid_eta", 1);
	chain->SetBranchStatus("mu_muid_etcone20", 1);
	chain->SetBranchStatus("mu_muid_etcone30", 1);
	chain->SetBranchStatus("mu_muid_expectBLayerHit", 1);
	chain->SetBranchStatus("mu_muid_id_d0", 1);
	chain->SetBranchStatus("mu_muid_id_phi", 1);
	chain->SetBranchStatus("mu_muid_id_qoverp", 1);
	chain->SetBranchStatus("mu_muid_id_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_muid_id_theta", 1);
	chain->SetBranchStatus("mu_muid_id_theta_exPV", 1);
	chain->SetBranchStatus("mu_muid_id_z0", 1);
	chain->SetBranchStatus("mu_muid_isStandAloneMuon", 1);
	chain->SetBranchStatus("mu_muid_isCombinedMuon", 1);
	chain->SetBranchStatus("mu_muid_isSegmentTaggedMuon", 1);
	chain->SetBranchStatus("mu_muid_me_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_muid_me_theta_exPV", 1);
	chain->SetBranchStatus("mu_muid_n", 1);
	chain->SetBranchStatus("mu_muid_nBLHits", 1);
	chain->SetBranchStatus("mu_muid_nPixelDeadSensors", 1);
	chain->SetBranchStatus("mu_muid_nPixHits", 1);
	chain->SetBranchStatus("mu_muid_nPixHoles", 1);
	chain->SetBranchStatus("mu_muid_nSCTDeadSensors", 1);
	chain->SetBranchStatus("mu_muid_nSCTHits", 1);
	chain->SetBranchStatus("mu_muid_nSCTHoles", 1);
	chain->SetBranchStatus("mu_muid_nTRTHits", 1);
	chain->SetBranchStatus("mu_muid_nTRTOutliers", 1);
	chain->SetBranchStatus("mu_muid_nCSCEtaHits", 1);
	chain->SetBranchStatus("mu_muid_nCSCPhiHits", 1);
	chain->SetBranchStatus("mu_muid_nMDTEMHits", 1);
	chain->SetBranchStatus("mu_muid_nMDTEOHits", 1);
	chain->SetBranchStatus("mu_muid_phi", 1);
	chain->SetBranchStatus("mu_muid_pt", 1);
	chain->SetBranchStatus("mu_muid_ptcone20", 1);
	chain->SetBranchStatus("mu_muid_ptcone30", 1);
	chain->SetBranchStatus("mu_muid_tight", 1);
	chain->SetBranchStatus("mu_muid_d0_exPV", 1);
	chain->SetBranchStatus("mu_muid_z0_exPV", 1);
	chain->SetBranchStatus("mu_muid_trackIPEstimate_d0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_muid_truth_mothertype", 1);
	chain->SetBranchStatus("mu_muid_truth_type", 1);

	/*-----------------------------------------------------------------*/
	/* MUONS calo							   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mu_calo_author", 1);
	chain->SetBranchStatus("mu_calo_caloMuonIdTag", 1);
	chain->SetBranchStatus("mu_calo_caloLRLikelihood", 1);
	chain->SetBranchStatus("mu_calo_charge", 1);
	chain->SetBranchStatus("mu_calo_E", 1);
	chain->SetBranchStatus("mu_calo_eta", 1);
	chain->SetBranchStatus("mu_calo_etcone20", 1);
	chain->SetBranchStatus("mu_calo_etcone30", 1);
	chain->SetBranchStatus("mu_calo_expectBLayerHit", 1);
	chain->SetBranchStatus("mu_calo_id_d0", 1);
	chain->SetBranchStatus("mu_calo_id_phi", 1);
	chain->SetBranchStatus("mu_calo_id_qoverp", 1);
	chain->SetBranchStatus("mu_calo_id_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_calo_id_theta", 1);
	chain->SetBranchStatus("mu_calo_id_theta_exPV", 1);
	chain->SetBranchStatus("mu_calo_id_z0", 1);
	chain->SetBranchStatus("mu_calo_isStandAloneMuon", 1);
	chain->SetBranchStatus("mu_calo_isCombinedMuon", 1);
	chain->SetBranchStatus("mu_calo_isSegmentTaggedMuon", 1);
	chain->SetBranchStatus("mu_calo_me_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_calo_me_theta_exPV", 1);
	chain->SetBranchStatus("mu_calo_n", 1);
	chain->SetBranchStatus("mu_calo_nBLHits", 1);
	chain->SetBranchStatus("mu_calo_nPixelDeadSensors", 1);
	chain->SetBranchStatus("mu_calo_nPixHits", 1);
	chain->SetBranchStatus("mu_calo_nPixHoles", 1);
	chain->SetBranchStatus("mu_calo_nSCTDeadSensors", 1);
	chain->SetBranchStatus("mu_calo_nSCTHits", 1);
	chain->SetBranchStatus("mu_calo_nSCTHoles", 1);
	chain->SetBranchStatus("mu_calo_nTRTHits", 1);
	chain->SetBranchStatus("mu_calo_nTRTOutliers", 1);
	chain->SetBranchStatus("mu_calo_nCSCEtaHits", 1);
	chain->SetBranchStatus("mu_calo_nCSCPhiHits", 1);
	chain->SetBranchStatus("mu_calo_nMDTEMHits", 1);
	chain->SetBranchStatus("mu_calo_nMDTEOHits", 1);
	chain->SetBranchStatus("mu_calo_phi", 1);
	chain->SetBranchStatus("mu_calo_pt", 1);
	chain->SetBranchStatus("mu_calo_ptcone20", 1);
	chain->SetBranchStatus("mu_calo_ptcone30", 1);
	chain->SetBranchStatus("mu_calo_d0_exPV", 1);
	chain->SetBranchStatus("mu_calo_z0_exPV", 1);
	chain->SetBranchStatus("mu_calo_trackIPEstimate_d0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_calo_trackIPEstimate_sigd0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_calo_truth_mothertype", 1);
	chain->SetBranchStatus("mu_calo_truth_type", 1);

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("EF_2e12_medium", 1);
	chain->SetBranchStatus("EF_2e12T_medium", 1);
	chain->SetBranchStatus("EF_2e12Tvh_medium", 1);
	chain->SetBranchStatus("EF_2e15_medium", 1);
	chain->SetBranchStatus("EF_2mu10_loose", 1);
	chain->SetBranchStatus("EF_e10_medium_mu10", 1);
	chain->SetBranchStatus("EF_e10_medium_mu6", 1);
	chain->SetBranchStatus("EF_e20_medium", 1);
	chain->SetBranchStatus("EF_e22_medium", 1);
	chain->SetBranchStatus("EF_e22_medium1", 1);
	chain->SetBranchStatus("EF_e22vh_medium1", 1);
	chain->SetBranchStatus("EF_mu10", 1);
	chain->SetBranchStatus("EF_mu15_mu10_EFFS", 1);
	chain->SetBranchStatus("EF_mu15_mu10_EFFS_medium", 1);
	chain->SetBranchStatus("EF_mu18", 1);
	chain->SetBranchStatus("EF_mu18_MG", 1);
	chain->SetBranchStatus("EF_mu18_MG_medium", 1);
	chain->SetBranchStatus("EF_mu20", 1);
	chain->SetBranchStatus("EF_mu20_MG", 1);
	chain->SetBranchStatus("EF_mu20_MG_medium", 1);
	chain->SetBranchStatus("EF_mu22", 1);
	chain->SetBranchStatus("EF_mu22_MG", 1);
	chain->SetBranchStatus("EF_mu22_MG_medium", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("trig_DB_SMK");
	chain->SetBranchStatus("trig_Nav_n");
	chain->SetBranchStatus("trig_Nav_chain_ChainId");
	chain->SetBranchStatus("trig_Nav_chain_RoIType");
	chain->SetBranchStatus("trig_Nav_chain_RoIIndex");

	chain->SetBranchStatus("trig_RoI_EF_e_egammaContainer_egamma_Electrons");
	chain->SetBranchStatus("trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus");
	chain->SetBranchStatus("trig_EF_el_n");
	chain->SetBranchStatus("trig_EF_el_eta");
	chain->SetBranchStatus("trig_EF_el_phi");

	chain->SetBranchStatus("trig_RoI_EF_mu_Muon_ROI");
	chain->SetBranchStatus("trig_RoI_EF_mu_TrigMuonEFInfoContainer");
	chain->SetBranchStatus("trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus");
	chain->SetBranchStatus("trig_RoI_L2_mu_CombinedMuonFeature");
	chain->SetBranchStatus("trig_RoI_L2_mu_CombinedMuonFeatureStatus");
	chain->SetBranchStatus("trig_RoI_L2_mu_MuonFeature");
	chain->SetBranchStatus("trig_RoI_L2_mu_Muon_ROI");
	chain->SetBranchStatus("trig_EF_trigmuonef_track_CB_pt");
	chain->SetBranchStatus("trig_EF_trigmuonef_track_CB_eta");
	chain->SetBranchStatus("trig_EF_trigmuonef_track_CB_phi");
	chain->SetBranchStatus("trig_EF_trigmuonef_track_SA_pt");
	chain->SetBranchStatus("trig_EF_trigmuonef_track_SA_eta");
	chain->SetBranchStatus("trig_EF_trigmuonef_track_SA_phi");
	chain->SetBranchStatus("trig_EF_trigmugirl_track_CB_pt");
	chain->SetBranchStatus("trig_EF_trigmugirl_track_CB_eta");
	chain->SetBranchStatus("trig_EF_trigmugirl_track_CB_phi");
	chain->SetBranchStatus("trig_L2_combmuonfeature_eta");
	chain->SetBranchStatus("trig_L2_combmuonfeature_phi");
	chain->SetBranchStatus("trig_L2_muonfeature_eta");
	chain->SetBranchStatus("trig_L2_muonfeature_phi");
	chain->SetBranchStatus("trig_L1_mu_eta");
	chain->SetBranchStatus("trig_L1_mu_phi");
	chain->SetBranchStatus("trig_L1_mu_thrName");

	/*-----------------------------------------------------------------*/

	TFile *f = new TFile("result.root", "recreate");

	TTree *t = chain->CopyTree("", "", 10);

	t->Write();

	delete t;
	delete f;

	/*-----------------------------------------------------------------*/

	TFile *f = TFile::Open("result.root");

	((TTree *) f->Get("physics"))->MakeClass("THiggsD3PD");

	delete f;

	/*-----------------------------------------------------------------*/

	system("sed -i -e \"s/vector/std::vector/g\" THiggsD3PD.h");
	system("sed -i -e \"s/string/std::string/g\" THiggsD3PD.h");

	system("sed -i -e \"s/*el_GSF/*el/g\" THiggsD3PD.h");
	system("sed -i -e \"s/\\&el_GSF/\\&el/g\" THiggsD3PD.h");

	system("sed -i -e \"s/*b_el_GSF/*b_el/g\" THiggsD3PD.h");
	system("sed -i -e \"s/\\&b_el_GSF/\\&b_el/g\" THiggsD3PD.h");

	system("sed -i -e \"s/   el_GSF/   el/g\" THiggsD3PD.h");

	system("sed -i -e \"s/#include <TFile.h>/&\\n\\n#define __IS_DATA/g\" THiggsD3PD.h");

	/*-----------------------------------------------------------------*/

	remove("THiggsD3PD.C");
//	remove("THiggsD3PD.root");

	/*-----------------------------------------------------------------*/
}

