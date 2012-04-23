#!/bin/sh

EXTERNAL_HEADER_PATH=
if [ $# -eq 1 ]; then
  EXTERNAL_HEADER_PATH=$1
  EXTERNAL_HEADER_NAME=`basename ${EXTERNAL_HEADER_PATH}`
  CLASS_NAME=${EXTERNAL_HEADER_NAME%.h}
  grep "D3PDReader" $1 > /dev/null
  NOT_D3PD_READER=$?
else
  echo "usage> $0 <path to header file>"
  exit 1
fi


if [ $NOT_D3PD_READER = 1 ]; then
#------------------------------------------------------------------#
# for root analysis with direct access to ntuple variables
#------------------------------------------------------------------#
  cat > tmp.header <<EOF
#include <vector>
#include <string>
using namespace std;
EOF

  cat ${EXTERNAL_HEADER_PATH} >> tmp.header
  mv tmp.header ${EXTERNAL_HEADER_PATH}

  for ii in MuonTriggerMatching ElectronTriggerMatching
  do
    cat > ../TrigMuonEfficiency/${ii}.h <<EOF
#include "${EXTERNAL_HEADER_PATH}"
typedef ${CLASS_NAME} MTT__D3PDEvent;
EOF
  cat ../skeleton/standard_h > ../Root/${ii}.cxx

  done

else
#------------------------------------------------------------------#
# for root analysis with D3PDReader to access ntuple variables
#------------------------------------------------------------------#
  for ii in MuonTriggerMatching ElectronTriggerMatching
  do
    cat > ../TrigMuonEfficiency/${ii}.h <<EOF
namespace D3PDReader {
  class TrigD3PDObject;
}
#define MTT__D3PDEvent D3PDReader::TrigD3PDObject
EOF
    echo "#include \"${EXTERNAL_HEADER_PATH}\"" > ../Root/${ii}.cxx
    cat ../skeleton/d3pdreader_h >> ../Root/${ii}.cxx
  done

  cat > tmp__h << EOF
#ifndef LEPTON_TRIGGER_MATCHING
#define LEPTON_TRIGGER_MATCHING
#include "TrigMuonEfficiency/MuonTriggerMatching.h" 
#include "TrigMuonEfficiency/ElectronTriggerMatching.h" 
#endif
EOF
  cat ../Root/LinkDef.h >> tmp__h
  mv tmp__h ../Root/LinkDef.h
fi

for ii in MuonTriggerMatching ElectronTriggerMatching
do
  cat ../skeleton/${ii}_cxx >> ../Root/${ii}.cxx
  cat ../skeleton/${ii}_h >> ../TrigMuonEfficiency/${ii}.h
done

# eof
