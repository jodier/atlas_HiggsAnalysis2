#define _CB_BR_(x) m_d3pd->trig_EF_trigmuonef_track_CB_##x
#define _SA_BR_(x) m_d3pd->trig_EF_trigmuonef_track_SA_##x
#define _MG_BR_(x) m_d3pd->trig_EF_trigmugirl_track_CB_##x

/*=================================================================* 
 * Implementation of MuonTriggerMatching
 *=================================================================*/
#include "TrigMuonEfficiency/ChainEntry.h"
#include "TrigMuonEfficiency/MuonTriggerMatching.h"
#include "TrigMuonEfficiency/MuonHypothesis.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <TMath.h>
#include <cmath>

/*=================================================================* 
 * public methods
 *=================================================================*/
bool
MuonTriggerMatching::match(const double eta,
                           const double phi,
                           const std::string& chain,
                           const std::string& l1item)
{
  EFmuon efmuon, dummy;
  matchedTrackDetail(efmuon, dummy, eta, phi, chain, l1item);
  return efmuon.valid;
}


std::pair<int, int>
MuonTriggerMatching::matchedTrack(const double eta,
                                  const double phi,
                                  const std::string& chain,
                                  const std::string& l1item)
{
  EFmuon efmuon, dummy;
  matchedTrackDetail(efmuon, dummy, eta, phi, chain, l1item);
  return efmuon.indicies;
}


bool
MuonTriggerMatching::matchDimuon(const TLorentzVector& muon1,
                                 const TLorentzVector& muon2,
                                 const std::string& chain,
                                 std::pair<bool, bool>& result1,
                                 std::pair<bool, bool>& result2)
{
  DimuonChainInfo chainInfo(chain);
  if (not decodeDimuonChain(chainInfo)) {
    std::cerr << "MuonTriggerMatching\t" << "ERROR\t"
              << "Failed to decode chain(" << chain
              << "matchDimuon can accept only chains named EF_2muXX_YY or EF_muXX_muYY_ZZ." << std::endl;
    return false;
  }

  std::pair<bool, bool> rc12, rc21;
  rc12 = matchDimuon(muon1, muon2, chainInfo);
  if (chainInfo.is2MuXX) {
    rc21.first = rc12.second; rc21.second = rc12.first;
  } else {
    rc21 = matchDimuon(muon2, muon1, chainInfo);
  }

  result1.first = rc12.first; result1.second = rc21.second;
  result2.first = rc21.first; result2.second = rc12.second;
  return true;
}


/*-----------------------------------------------------------------* 
 * for developers
 *-----------------------------------------------------------------*/
void
MuonTriggerMatching::showSMKeys()
{
  std::map<int, std::map<std::string, int> >::const_iterator p;
  std::cout << "MuonTriggerMatching\t" << "INFO\t" << "SMKeys:";
  for (p = m_MapOfChainIdMap.begin(); p != m_MapOfChainIdMap.end(); ++p) {
    std::cout << p->first << ", ";
  }
  std::cout << std::endl;
}


void
MuonTriggerMatching::dumpChainIdMap(const int SMK)
{
  if (m_MapOfChainIdMap.find(SMK) == m_MapOfChainIdMap.end()) {
    std::cerr << "MuonTriggerMatching\t" << "ERROR\t"
              << "ChainIdMap for SMK = " << SMK << " is not stored." << std::endl;
    return;
  }

  std::map<std::string, int> ChainIdMap = m_MapOfChainIdMap[SMK];
  std::map<std::string, int>::const_iterator p;
  std::cout << "MuonTriggerMatching\t" << "INFO\t"
            << "dump ChainIdMap for SMKeys:" << SMK << std::endl;

  for (p = ChainIdMap.begin(); p != ChainIdMap.end(); ++p) {
    std::cout << p->first << "\t" << p->second << std::endl;
  }
}


void
MuonTriggerMatching::createChainIdMapFile(const int SMK)
{
  if (m_MapOfChainIdMap.find(SMK) == m_MapOfChainIdMap.end()) {
    std::cerr << "MuonTriggerMatching\t" << "ERROR\t"
              << "ChainIdMap for SMK = " << SMK << " is not stored." << std::endl;
    return;
  }

  std::map<std::string, int> ChainIdMap = m_MapOfChainIdMap[SMK];
  std::map<std::string, int>::const_iterator p;

  std::ofstream ofs("MuonChainIdMap.h");
  ofs << "void MuonTriggerMatching::createChainIdMapFromFile() {" << "\n";
  ofs << "  " << "std::map<std::string, int> ChainIdMap;" << "\n";
  for (p = ChainIdMap.begin(); p != ChainIdMap.end(); ++p) {
    ofs << "  " << "ChainIdMap.insert(std::pair<std::string, int>(\"" << p->first << "\", " << p->second << "));" << "\n";
  }
  ofs << "  " << "m_MapOfChainIdMap.insert(std::pair<int, std::map<std::string, int> >(-1, ChainIdMap));" << "\n";
  ofs << "}" << std::endl;
}


/*=================================================================* 
 * private methods
 *=================================================================*/
bool
MuonTriggerMatching::checkSeed(const double eta,
                               const double phi,
                               const std::string& chain,
                               double l2dr,
                               double l1dr)
{
  const int chainIndex = getChainIndex(chain);
  if (chainIndex < 0) return false;

  const std::vector<int> RoIIndex = m_d3pd->trig_Nav_chain_RoIIndex->at(chainIndex);
  const std::vector<int> RoIType = m_d3pd->trig_Nav_chain_RoIType->at(chainIndex);

  for (size_t iRoI = 0; iRoI < RoIIndex.size(); ++iRoI) {
    if (RoIType[iRoI] != ChainEntry::kRoIType_L2_mu) continue;
    if (not m_d3pd->trig_RoI_L2_mu_CombinedMuonFeatureStatus->at(RoIIndex[iRoI])) continue;

    double minDr = l2dr;
    const int muComb = m_d3pd->trig_RoI_L2_mu_CombinedMuonFeature->at(RoIIndex[iRoI]);
    double trigEta = m_d3pd->trig_L2_combmuonfeature_eta->at(muComb);
    double trigPhi = m_d3pd->trig_L2_combmuonfeature_phi->at(muComb);

    // L2 ID tracks can be truncated after trigger decision,
    // as a consequence (eta,phi) of CombinedMuonFeature become (0,0)
    // We use MuonFeature in this case.
    if (isEqual(trigEta, 0.) and isEqual(trigPhi, 0.)) {
      const int muFast = m_d3pd->trig_RoI_L2_mu_MuonFeature->at(RoIIndex[iRoI]);
      trigEta = m_d3pd->trig_L2_muonfeature_eta->at(muFast);
      trigPhi = m_d3pd->trig_L2_muonfeature_phi->at(muFast);
    }

    // pathlogical case, use L1 for matching
    if (isEqual(trigEta, 0.) and isEqual(trigPhi, 0.)) {
      const int muRoI = m_d3pd->trig_RoI_L2_mu_Muon_ROI->at(RoIIndex[iRoI]);
      trigEta = m_d3pd->trig_L1_mu_eta->at(muRoI);
      trigPhi = m_d3pd->trig_L1_mu_phi->at(muRoI);
      minDr = l1dr;
    }

    if (not (dR(eta, phi, trigEta, trigPhi) < minDr)) continue;
    return true;
  }

  return false;
}


double
MuonTriggerMatching::matchedTrackDetail(EFmuon& efMuonId,
                                        const EFmuon& usedEfMuonId,
                                        const double eta,
                                        const double phi,
                                        const std::string& chainForThisMuon,
                                        const std::string& l1item,
                                        const std::string& chainForEventTrigger)
{
  efMuonId.indicies.first = -1;
  efMuonId.indicies.second = -1;
  efMuonId.valid = false;
  double dR_min = m_matchingDr;

  const std::string eventTrigger = chainForEventTrigger.empty() ? chainForThisMuon : chainForEventTrigger;
  const int chainIndex = getChainIndex(eventTrigger);
  if (chainIndex < 0) return -1;
  const std::vector<int> RoIIndex = m_d3pd->trig_Nav_chain_RoIIndex->at(chainIndex);
  const std::vector<int> RoIType = m_d3pd->trig_Nav_chain_RoIType->at(chainIndex);
  
  unsigned int chain_type = CB;
  if (chainForThisMuon.find("_MSonly") != std::string::npos) chain_type = SA;
  if (chainForThisMuon.find("_MG") != std::string::npos) chain_type = MG;

  for (size_t iRoI = 0; iRoI < RoIIndex.size(); ++iRoI) {
    if (RoIType[iRoI] != ChainEntry::kRoIType_EF_mu) continue;

    if (not l1item.empty()) {
      if (not L1_isPassed(m_d3pd->trig_RoI_EF_mu_Muon_ROI->at(RoIIndex[iRoI]), l1item)) continue;
    }

    const std::vector<int> EFmuonCont = m_d3pd->trig_RoI_EF_mu_TrigMuonEFInfoContainer->at(RoIIndex[iRoI]);
    const std::vector<int> status = m_d3pd->trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus->at(RoIIndex[iRoI]);
    for (size_t iCont = 0; iCont < EFmuonCont.size(); ++iCont) {
      if (not status.at(iCont)) continue;
      const std::vector<float> v_pt = (chain_type == MG) ? _MG_BR_(pt)->at(EFmuonCont[iCont]) :
        ((chain_type == SA) ? _SA_BR_(pt)->at(EFmuonCont[iCont]) : _CB_BR_(pt)->at(EFmuonCont[iCont]));
      const std::vector<float> v_eta = (chain_type == MG) ? _MG_BR_(eta)->at(EFmuonCont[iCont]) :
        ((chain_type == SA) ? _SA_BR_(eta)->at(EFmuonCont[iCont]) : _CB_BR_(eta)->at(EFmuonCont[iCont]));
      const std::vector<float> v_phi = (chain_type == MG) ? _MG_BR_(phi)->at(EFmuonCont[iCont]) :
        ((chain_type == SA) ? _SA_BR_(phi)->at(EFmuonCont[iCont]) : _CB_BR_(phi)->at(EFmuonCont[iCont]));

      for (size_t iTrk = 0; iTrk < v_pt.size(); ++iTrk) {
        if (usedEfMuonId.valid and
            isEqual(usedEfMuonId.pt, v_pt[iTrk]) and
            isEqual(usedEfMuonId.eta, v_eta[iTrk]) and
            isEqual(usedEfMuonId.phi, v_phi[iTrk])) continue;

        if (not MuonHypothesis::EF_isPassed(v_pt[iTrk], v_eta[iTrk], chainForThisMuon)) continue;
        double dR_tmp = dR(eta, phi, v_eta[iTrk], v_phi[iTrk]);
        if (not (dR_tmp < dR_min)) continue;
        dR_min = dR_tmp;

        efMuonId.valid = true;
        efMuonId.pt = v_pt[iTrk];
        efMuonId.eta = v_eta[iTrk];
        efMuonId.phi = v_phi[iTrk];
        efMuonId.indicies.first = EFmuonCont[iCont];
        efMuonId.indicies.second = iTrk;
      }
    }
  }

  return dR_min;
}


std::pair<bool, bool>
MuonTriggerMatching::matchDimuon(const TLorentzVector& muon1,
                                 const TLorentzVector& muon2,
                                 const DimuonChainInfo& chainInfo)
{
  EFmuon trkId1, trkId2, dummy;
  const double dr1 = matchedTrackDetail(trkId1, dummy, muon1.Eta(), muon1.Phi(),
                                        chainInfo.thresholds.first, "", chainInfo.chain);
  if (chainInfo.isEFFS and trkId1.valid) trkId1.valid = checkSeed(muon1.Eta(), muon1.Phi(), chainInfo.l2chain);
  const double dr2 = matchedTrackDetail(trkId2, dummy, muon2.Eta(), muon2.Phi(),
                                        chainInfo.thresholds.second, "", chainInfo.chain);

  if (trkId1.valid and trkId2.valid and
      isEqual(trkId1.pt, trkId2.pt) and
      isEqual(trkId1.eta, trkId2.eta) and
      isEqual(trkId1.phi, trkId2.phi)) {
    if (dr1 > dr2) {
      matchedTrackDetail(trkId1, trkId2, muon1.Eta(), muon1.Phi(),
                         chainInfo.thresholds.first, "", chainInfo.chain);
    if (chainInfo.isEFFS and trkId1.valid) trkId1.valid = checkSeed(muon1.Eta(), muon1.Phi(), chainInfo.l2chain);

    } else {
      matchedTrackDetail(trkId2, trkId1, muon2.Eta(), muon2.Phi(),
                         chainInfo.thresholds.second, "", chainInfo.chain);
    }
  }
  return std::pair<bool, bool>(trkId1.valid, trkId2.valid);
}


bool
MuonTriggerMatching::L1_isPassed(const int iRoI,
                                 const std::string& l1item)
{
  if (iRoI < 0) return false;
  return getL1pt(m_d3pd->trig_L1_mu_thrName->at(iRoI)) >= getL1pt(l1item);
}


int
MuonTriggerMatching::getL1pt(const std::string& l1item)
{
  int rc = -1;

  std::vector<std::string> tokens;
  tokenize(l1item, tokens, "_");
  std::string pt;
  if (tokens.size() == 1) {
    pt = tokens.at(0);

  } else if ((tokens.size() == 2 ) and (tokens.at(0) == "L1")) {
    pt = tokens.at(1);

  } else {
    std::cerr << "MuonTriggerMatching::getL1pt: cannot parse: " << l1item << std::endl;
    return rc;
  }

  const size_t index = pt.find("MU");
  if (index != std::string::npos) {
    std::istringstream iss(pt.substr(index + 2));
    iss >> rc;
  } else {
    std::cerr << "MuonTriggerMatching::getL1pt: cannot parse: " << l1item << std::endl;
  }

  return rc;
}


void
MuonTriggerMatching::tokenize(const std::string& str,
                              std::vector<std::string>& tokens,
                              const std::string& delimiters)
{
  tokens.clear();
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  std::string::size_type pos = str.find_first_of(delimiters, lastPos);

  while ((std::string::npos != pos) or (std::string::npos != lastPos)) {
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delimiters, pos);
    pos = str.find_first_of(delimiters, lastPos);
  }
}


bool
MuonTriggerMatching::decodeDimuonChain(DimuonChainInfo& chainInfo)
{
  chainInfo.isValid = false;

  std::map<std::string, DimuonChainInfo >::const_iterator p = m_DimuonChainMap.find(chainInfo.chain);
  if (p != m_DimuonChainMap.end()) {
    chainInfo = p->second;
    return chainInfo.isValid;
  }

  std::vector<std::string> tokens;
  tokenize(chainInfo.chain, tokens, "_");
  if (tokens.size() < 2) return false;
  if (tokens[0] != "EF") return false;
  chainInfo.is2MuXX = (tokens[1].substr(0, 3) == "2mu");

  if (chainInfo.is2MuXX) {
    std::string threshold = std::string("EF_" + tokens[1].substr(1));
    chainInfo.thresholds.first = threshold;
    chainInfo.thresholds.second = threshold;
    chainInfo.isValid = true;
    if (tokens.size() == 3) chainInfo.tightness = tokens[2];

  } else {
    if (tokens.size() < 4) return false;
    if (tokens[3] != "EFFS") return false;
    if ((tokens[1].substr(0,2) != "mu") or (tokens[2].substr(0,2) != "mu")) return false;
    std::string threshold1 = std::string("EF_" + tokens[1]);
    std::string threshold2 = std::string("EF_" + tokens[2]);
    chainInfo.isEFFS = true;
    chainInfo.thresholds.first = threshold1;
    chainInfo.thresholds.second = threshold2;
    if (tokens.size() == 5) chainInfo.tightness = tokens[4];
    chainInfo.l2chain = "L2_" + tokens[1] + (chainInfo.tightness.empty() ? "" : "_" + chainInfo.tightness);
    chainInfo.isValid = true; 
  }

  m_DimuonChainMap[chainInfo.chain] = chainInfo;

  return chainInfo.isValid;
}


bool
MuonTriggerMatching::isEqual(const double x,
                             const double y)
{
  if (fabs(x - y) < std::numeric_limits<float>::epsilon()) return true;
  return false;
}


double
MuonTriggerMatching::dR(const double eta1,
                        const double phi1,
                        const double eta2,
                        const double phi2)
{
  double deta = fabs(eta1 - eta2);
  double dphi = fabs(phi1 - phi2) < TMath::Pi() ? fabs(phi1 - phi2) : 2*TMath::Pi() - fabs(phi1 - phi2);
  return sqrt(deta*deta + dphi*dphi);
}


int
MuonTriggerMatching::getChainIndex(const std::string& chain)
{
  int smk = static_cast<int>(*(m_d3pd->trig_DB_SMK));
  std::map<std::string, int> ChainIdMap = (m_MapOfChainIdMap.count(smk)) ? m_MapOfChainIdMap[smk] : m_MapOfChainIdMap[-1];

  if (ChainIdMap.find(chain) == ChainIdMap.end()) {
    if (m_NotFoundChain.find(chain) == m_NotFoundChain.end()) {
      std::cerr << "MuonTriggerMatching\t" << "ERROR\t"
                << chain << " does not exist in ChainIdMap for SMK = " << smk
                << " (if SMK = -1, it means the Map is created from TrigMuonEfficiency/MuonChainIdMap.h)" << std::endl;
      m_NotFoundChain.insert(chain);
    }
    return -1;
  }

  const short ChainId = static_cast<short>(ChainIdMap[chain]);
  for (int iChain = 0; iChain < *(m_d3pd->trig_Nav_n); ++iChain) {
    if (m_d3pd->trig_Nav_chain_ChainId->at(iChain) == ChainId) return iChain;
  }

  if (m_NotFoundChain.find(chain) == m_NotFoundChain.end()) {
    std::cerr << "MuonTriggerMatching\t" << "ERROR\t"
              << chain << " does not exist in Flat Navigation Branch." << std::endl;
    m_NotFoundChain.insert(chain);
  }
  return -1;
}


void
MuonTriggerMatching::readTrigConfTree(TTree* TrigConfTree)
{
  int smk=-9999;
  std::map<std::string, int>* hltmap=0;

  if (TrigConfTree) {
    TrigConfTree->SetBranchAddress("SMK", &smk);
    TrigConfTree->SetBranchAddress("HLTNameMap", &hltmap);

    TrigConfTree->GetEntry(0);
    if (not ((smk != -9999) and hltmap)) {
      std::cerr << "MuonTriggerMatching\t" << "ERROR\t"
                << "TrigConfTree does exist, but could not SetBranchAddress for SMK and HLTNameMap." << std::endl;
      return;
    }

    std::map<std::string, int>::const_iterator p;
    for (int iEntry = 0; iEntry < TrigConfTree->GetEntries(); ++iEntry) {
      TrigConfTree->GetEntry(iEntry);
      if (m_MapOfChainIdMap.count(smk)) continue;

      std::map<std::string, int> ChainIdMap;
      for (p = hltmap->begin(); p != hltmap->end(); ++p) {
        if ((p->first.find("EF_mu") != 0) and
            (p->first.find("EF_2mu") != 0) and
            (p->first.find("L2_mu15") != 0) and
            (p->first.find("L2_mu20") != 0)) continue;

        int id = p->second;
        if (p->first.find("EF_") == 0) id += ChainEntry::kEFChainIdOffset;
        ChainIdMap.insert(std::pair<std::string, int>(p->first, id));
      }
      m_MapOfChainIdMap.insert(std::pair<int, std::map<std::string, int> >(smk, ChainIdMap));
    }

  } else {
    std::cerr << "MuonTriggerMatching\t" << "inf> " << "Create ChainIdMap from TrigMuonEfficiency/MuonChainIdMap.h.\n";
    std::cerr << std::endl;
    createChainIdMapFromFile();
  }
}


#include "TrigMuonEfficiency/MuonChainIdMap.h"
// eof
