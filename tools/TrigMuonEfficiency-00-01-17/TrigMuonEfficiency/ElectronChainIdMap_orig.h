#ifndef ElectronChainIdMap_h
#define ElectronChainIdMap_h
void ElectronTriggerMatching::createChainIdMapFromFile() {
  std::map<std::string, int> ChainIdMap;
  ChainIdMap.insert(std::pair<std::string, int>("EF_e20_medium", 10297));
  ChainIdMap.insert(std::pair<std::string, int>("EF_e22_medium", 10528));
  ChainIdMap.insert(std::pair<std::string, int>("EF_e22vh_medium1", 10049));
  ChainIdMap.insert(std::pair<std::string, int>("EF_e45_medium1", 10547));
  m_MapOfChainIdMap.insert(std::pair<int, std::map<std::string, int> >(-1, ChainIdMap));

  std::map<std::string, int> ChainIdMap295;
  ChainIdMap295.insert(std::pair<std::string, int>("EF_e20_medium", 10297));
  ChainIdMap295.insert(std::pair<std::string, int>("EF_e22_medium", 10528));
  ChainIdMap295.insert(std::pair<std::string, int>("EF_e22_medium1", 10049));
  ChainIdMap295.insert(std::pair<std::string, int>("EF_e45_medium1", 10547));
  ChainIdMap295.insert(std::pair<std::string, int>("EF_2e12_medium",10361));
  ChainIdMap295.insert(std::pair<std::string, int>("EF_2e12T_medium",10718));
  m_MapOfChainIdMap.insert(std::pair<int, std::map<std::string, int> >(295, ChainIdMap295));

  std::map<std::string, int> ChainIdMap308;
  ChainIdMap308.insert(std::pair<std::string, int>("EF_e20_medium", 10297));
  ChainIdMap308.insert(std::pair<std::string, int>("EF_e22_medium", 10528));
  ChainIdMap308.insert(std::pair<std::string, int>("EF_e22_medium1", 10049));
  ChainIdMap308.insert(std::pair<std::string, int>("EF_e45_medium1", 10547));
  ChainIdMap308.insert(std::pair<std::string, int>("EF_2e12_medium",10361));
  ChainIdMap308.insert(std::pair<std::string, int>("EF_2e12T_medium",10718));
  m_MapOfChainIdMap.insert(std::pair<int, std::map<std::string, int> >(308, ChainIdMap308));

  std::map<std::string, int> ChainIdMap310;
  ChainIdMap310.insert(std::pair<std::string, int>("EF_e22vh_medium", 10528));
  ChainIdMap310.insert(std::pair<std::string, int>("EF_e22vh_medium1", 10049));
  ChainIdMap310.insert(std::pair<std::string, int>("EF_e45_medium1", 10547));
  ChainIdMap310.insert(std::pair<std::string, int>("EF_e22vh_medium", 10528));
  ChainIdMap310.insert(std::pair<std::string, int>("EF_e22vh_medium1", 10049));
  ChainIdMap310.insert(std::pair<std::string, int>("EF_2e12Tvh_medium",10718));
  m_MapOfChainIdMap.insert(std::pair<int, std::map<std::string, int> >(310, ChainIdMap310));
}
#endif
