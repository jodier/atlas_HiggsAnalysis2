#ifndef __ElectronTriggerMatching_h__
#define __ElectronTriggerMatching_h__
/**
 * @author  Toyonobu Okuyama
 * @author  Takashi Matsushita
 */


#include <string>
#include <map>
#include <set>
#include "TTree.h"
#include "TLorentzVector.h"

#include "TrigMuonEfficiency/TriggerNavigationVariables.h"
typedef TriggerNavigationVariables MTT__D3PDEvent;

/**
 *  This class implements method for electron trigger matching with navigation information in ntuple analysis.
 *
 *  Validated on NTUP_SMWZ. Should work on any ntuples which contains TrigMuonD3PDMaker block
 */
class ElectronTriggerMatching {
  public:
    struct EFelectron {
      bool valid;
      float charge;
      int roi;
      float eta;
      float phi;

      EFelectron() : valid(false), charge(0.), roi(-1), eta(-1.e30), phi(-1.e30) {}
    };

    /** default constructor
     *
     * @param d3pd [in] class object used for the given ntuple analysis
     * @param TrigConfTree [in] pointer of physicsMeta/TrigConfTree block [optional]
     */
    ElectronTriggerMatching(const MTT__D3PDEvent *d3pd,
                            TTree *TrigConfTree=0)
      : m_d3pd(d3pd),
        m_matchingDr(0.15),
        m_MapOfChainIdMap(),
        m_NotFoundChain() {
      readTrigConfTree(TrigConfTree);
    }
    virtual ~ElectronTriggerMatching(){}


    /** returns minimum distance required for offline electron and trigger object matching
     *
     * @return m_matchingDr
     */
    double getDeltaR() const {return m_matchingDr;}


    /** set minimum distance required for offline electron and trigger object matching
     *
     * @param dr [in] matching distance for offline electron and trigger object matching
     */
    void setDeltaR(const double dr) {m_matchingDr = dr;}


    /** look for matching EF electron trigger object
     *
     * @param eta [in] eta of an offline electron
     * @param phi [in] phi of an offline electron
     * @param chain [in] single electron EF chain name. ex) "EF_mu18"
     * @return true if matching EF object was found false otherwise.
     */
    bool match(const double eta,
               const double phi,
               const std::string& chain);

    /** look for matching EF di-electron trigger object
     *
     * @param electron1 [in] TLorentzVector of electron
     * @param electron2 [in] TLorentzVector of electron
     * @param chain [in] di-electron EF chain name. ex) "EF_2e12"
     * @param result1 [out] bool values indicating if electron1 passed the di-muon trigger.
     * @param result2 [out] bool values indicating if electron2 passed the di-muon trigger.
     * @return true if matching EF object was found false otherwise.
     */
    bool matchDielectron(const TLorentzVector& electron1,
                     const TLorentzVector& electron2,
                     const std::string& chain,
                     bool& result1,
                     bool& result2);

    // for developers
    void showSMKeys();
    void dumpChainIdMap(const int SMK);
    void createChainIdMapFile(const int SMK);


  private:
    const MTT__D3PDEvent* m_d3pd; 
    double m_matchingDr;
    std::map<int, std::map<std::string, int> > m_MapOfChainIdMap; // [SMK - [ChainName - ChainId] ]
    std::set<std::string> m_NotFoundChain;
 
    double matchedTrackDetail(EFelectron& efElectronId,
                              const EFelectron& usedEfElectronId,
                              const double eta,
                              const double phi,
                              const std::string& chainEventTrigger);


    int getChainIndex(const std::string& chain);
    void readTrigConfTree(TTree* TrigConfTree);
    double dR(const double eta1,
              const double phi1,
              const double eta2,
              const double phi2);
    void createChainIdMapFromFile(); //implementation in ChainIdMap.h
    void tokenize(const std::string& str,
                  std::vector<std::string>& tokens,
                  const std::string& delimiters);
    bool decodeDielectronChain(const std::string& chain);
    bool isEqual(const double x,
                 const double y);
};

#endif //__ElectronTriggerMatching_h__
// eof
