#-Wl,-rpath=$(formats_dir)/CMSdataFormat/lib \

#	-lflashggMetaData \
#	-lflashggMicroAOD \
#	-lflashggSystematics \
#	-lflashggTaggers \
#	-lflashggValidation \

#	-lRecoEgammaEgammaTools \
#	-lRecoEgammaElectronIdentification \
#	-lRecoHIHiEgammaAlgos \
#	-lRecoJetsJetProducers \
#	-lRecoMETMETAlgorithms \
#	-lRecoParticleFlowPFTracking \

CLHEP_DIR = /cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.1.1-giojec4

all: distributions

distributions: distributions.cc common_input.h
	g++ --std=c++11 -O3 -g `root-config --libs` `root-config --cflags` -Wall -Wno-attributes \
	-I$(CMSSW_BASE)/src \
	-I$(CMSSW_RELEASE_BASE)/src \
	-I$(CLHEP_DIR)/include \
	-L$(CMSSW_BASE)/lib/slc6_amd64_gcc530 \
	-L$(CMSSW_RELEASE_BASE)/lib/slc6_amd64_gcc530 \
	-L$(CLHEP_DIR)/lib \
	-lFWCoreCommon \
	-lGenVector \
	-lDataFormatsFWLite \
	-lDataFormatsCommon \
	-lflashggDataFormats \
	-lRecoBTagSoftLepton \
	-lDataFormatsCandidate \
	distributions.cc -o distributions
