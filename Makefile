#############################################################################

DIR=$(shell pwd)

#############################################################################

CINT          = rootcint
ROOTCONFIG    = root-config

#############################################################################

ROOTLIBS      = $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS     = $(shell $(ROOTCONFIG) --glibs)
ROOTCFLAGS    = $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS   = $(shell $(ROOTCONFIG) --ldflags)

#############################################################################

ATLASFLAGS    = -DSTANDALONE \
-I tools/ggFReweighting-00-00-08 \
-I tools/HiggsZZ4lUtils-00-00-07 \
-I tools/PileupReweighting-00-02-02 \
-I tools/TrigMuonEfficiency-00-01-17 \
-I tools/egammaAnalysisUtils-00-02-76 \
-I tools/MuonIsolationCorrection-00-08 \
-I tools/MuonMomentumCorrections-00-05-03 \
-I tools/MuonEfficiencyCorrections-01-01-03

ATLASLIBS    = -L./tools \
-legammaAnalysisUtils \
-lggFReweighting \
-lHiggsZZ4lUtils \
-lMuonEfficiencyCorrections \
-lMuonIsolationCorrection \
-lMuonMomentumCorrections \
-lPileupReweighting \
-lTrigMuonEfficiency

#############################################################################

CXX           =g++
CXXFLAGS      =-std=c++98 -g -O2 -fPIC -ansi -Wall $(ROOTCFLAGS) $(ATLASFLAGS)

LD            =g++
LDFLAGS       =-g $(ROOTLDFLAGS) -L.

LIBS          = $(ROOTLIBS) -lTreePlayer
GLIBS         = $(ROOTGLIBS) -lTreePlayer

#############################################################################

OBJS1         = core/main.o core/core.o core/config.o core/loader.o core/utils.o

OBJS2         = analysis/higgs_analysis/main.o analysis/higgs_analysis/triggers.o analysis/higgs_analysis/utils.o analysis/higgs_analysis/isLoosePP.o analysis/higgs_analysis/Z_analysis.o analysis/higgs_analysis/H_analysis.o

OBJS3         = analysis/test/main.o analysis/higgs_analysis/triggers.o analysis/higgs_analysis/utils.o analysis/higgs_analysis/isLoosePP.o

OBJS4         = analysis/z_studies/eff.o

OBJS5         = analysis/z_studies/mass.o

OBJS6         = analysis/z_studies/ZcandPeriod.o

OBJS7         = analysis/l_study/main.o analysis/higgs_analysis/triggers.o analysis/higgs_analysis/utils.o analysis/higgs_analysis/isLoosePP.o

#############################################################################

all: core $(OBJS2) $(OBJS3)  $(OBJS7) #$(OBJS5) $(OBJS6)
#	@cd $(DIR)/tools && make && cd $(DIR)

	$(LD) $(LDFLAGS) -o higgs_analysis $(OBJS2) $(LIBS) -L. -lcore $(ATLASLIBS)
	$(LD) $(LDFLAGS) -o      test      $(OBJS3) $(LIBS) -L. -lcore $(ATLASLIBS)
#	$(LD) $(LDFLAGS) -o       eff      $(OBJS4) $(LIBS) $(ATLASLIBS) -lRooFitCore -lRooFit
#	$(LD) $(LDFLAGS) -o      mass      $(OBJS5) $(LIBS) $(ATLASLIBS)
#	$(LD) $(LDFLAGS) -o   ZcandPeriod  $(OBJS6) $(LIBS) $(ATLASLIBS)
	$(LD) $(LDFLAGS) -o     l_study    $(OBJS7) $(LIBS) -L. -lcore $(ATLASLIBS)

#############################################################################

ALL: core $(OBJS2) $(OBJS3) $(OBJS7) # $(OBJS5) $(OBJS6)
	@cd $(DIR)/tools && make all && cd $(DIR)

	$(LD) $(LDFLAGS) -o higgs_analysis $(OBJS2) $(LIBS) -L. -lcore $(ATLASLIBS)
	$(LD) $(LDFLAGS) -o      test      $(OBJS3) $(LIBS) -L. -lcore $(ATLASLIBS)
#	$(LD) $(LDFLAGS) -o       eff      $(OBJS4) $(LIBS) $(ATLASLIBS) -lRooFitCore -lRooFit
#	$(LD) $(LDFLAGS) -o      mass      $(OBJS5) $(LIBS) $(ATLASLIBS)
#	$(LD) $(LDFLAGS) -o   ZcandPeriod  $(OBJS6) $(LIBS) $(ATLASLIBS)
	$(LD) $(LDFLAGS) -o     l_study    $(OBJS7) $(LIBS) -L. -lcore $(ATLASLIBS)

#############################################################################

clean:
#	@cd $(DIR)/tools && make clean && cd $(DIR)

	rm -fr $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) libcore.a higgs_analysis test eff mass ZcandPeriod l_study

#############################################################################

CLEAN:
	@cd $(DIR)/tools && make clean && cd $(DIR)

	rm -fr $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) libcore.a higgs_analysis test eff mass ZcandPeriod l_study

#############################################################################

core: $(OBJS1)
	ar -rcs libcore.a $(OBJS1) && ranlib libcore.a

#############################################################################

%.o: %.C
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

%.o: %.cc
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

%.o: %.cxx
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

#############################################################################

