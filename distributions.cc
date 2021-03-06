#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"


#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/DiProtonDiPhotonCandidate.h"

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"

#include <vector>
#include <string>

#include "common_input.h"

typedef math::XYZTLorentzVector LorentzVector;

using namespace std;
using namespace edm;

//----------------------------------------------------------------------------------------------------

struct PlotGroup
{
	TH1D *h_diproton_px, *h_diproton_py, *h_diproton_pz, *h_diproton_pT, *h_diproton_m;
	TH1D *h_diphoton_px, *h_diphoton_py, *h_diphoton_pz, *h_diphoton_pT, *h_diphoton_m;
	TH1D *h_missing_px, *h_missing_py, *h_missing_pz, *h_missing_pT, *h_missing_m;

	TH2D *h2_diph_pT_vs_diph_m, *h2_miss_m_vs_diph_m, *h2_miss_m_vs_dipr_m, *h2_miss_m_vs_diph_pT;

	PlotGroup()
	{
	}

	void Init()
	{
		h_diproton_px = new TH1D("", "", 100, -500., +500);
		h_diproton_py = new TH1D("", "", 100, -500., +500.);
		h_diproton_pz = new TH1D("", "", 100, -1000., +1000.);
		h_diproton_pT = new TH1D("", "", 100, 0., 500.);
		h_diproton_m = new TH1D("", "", 100, 10e3, 13e3);
		
		h_diphoton_px = new TH1D("", "", 100, -500., +500.);
		h_diphoton_py = new TH1D("", "", 100, -500., +500.);
		h_diphoton_pz = new TH1D("", "", 100, -1000., +1000.);
		h_diphoton_pT = new TH1D("", "", 100, 0., +1000.);
		h_diphoton_m = new TH1D("", "", 100, 0., +1500.);
		
		h_missing_px = new TH1D("", "", 100, -500., +500.);
		h_missing_py = new TH1D("", "", 100, -500., +500.);
		h_missing_pz = new TH1D("", "", 100, -1500., +1500.);
		h_missing_pT = new TH1D("", "", 100, 0., +500.);
		h_missing_m = new TH1D("", "", 100, -2500., +2500.);

		h2_diph_pT_vs_diph_m = new TH2D("", ";diph m;diph pT", 100, 0., 1500., 100, 0., 1000.);
		h2_miss_m_vs_diph_m = new TH2D("", ";diph m;miss m", 100, 0., 1500., 100, -2500., +2500.);
		h2_miss_m_vs_dipr_m = new TH2D("", ";dipr m;miss m", 100, 10E3, 13E3, 100, -2500., +2500.);
		h2_miss_m_vs_diph_pT = new TH2D("", ";diph pT;miss m", 100, 0., 1000., 100, -2500., +2500.);
	}

	void Write() const
	{
		h_diproton_px->Write("h_diproton_px");
		h_diproton_py->Write("h_diproton_py");
		h_diproton_pz->Write("h_diproton_pz");
		h_diproton_pT->Write("h_diproton_pT");
		h_diproton_m->Write("h_diproton_m");
		
		h_diphoton_px->Write("h_diphoton_px");
		h_diphoton_py->Write("h_diphoton_py");
		h_diphoton_pz->Write("h_diphoton_pz");
		h_diphoton_pT->Write("h_diphoton_pT");
		h_diphoton_m->Write("h_diphoton_m");
		
		h_missing_px->Write("h_missing_px");
		h_missing_py->Write("h_missing_py");
		h_missing_pz->Write("h_missing_pz");
		h_missing_pT->Write("h_missing_pT");
		h_missing_m->Write("h_missing_m");

		h2_diph_pT_vs_diph_m->Write("h2_diph_pT_vs_diph_m");
		h2_miss_m_vs_diph_m->Write("h2_miss_m_vs_diph_m");
		h2_miss_m_vs_dipr_m->Write("h2_miss_m_vs_dipr_m");
		h2_miss_m_vs_diph_pT->Write("h2_miss_m_vs_diph_pT");
	}
};

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: distributions [options]\n");
	printf("OPTIONS:\n");
	printf("		-input <file>				 file with list of input files\n");
	printf("		-min-idx <number>		 first file index\n");
	printf("		-max-idx <number>		 last file index\n");
	printf("		-output <filename>		output file name\n");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	printf("running\n");

	// parameter defaults
	string input_list_file_name = "";
	signed int input_min_idx = 0;
	signed int input_max_idx = -1;
	string output_file_name = "distributions.root";

	// parse command line
	for (int ai = 1; ai < argc; ai++)
	{
		if (strcmp(argv[ai], "-input") == 0)
		{
			if (++ai >= argc)
			{
				printf("ERROR: -input option needs an argument.\n");
				PrintUsage();
				return 1;
			}

			input_list_file_name = argv[ai];
			continue;
		}

		if (strcmp(argv[ai], "-min-idx") == 0)
		{
			if (++ai >= argc)
			{
				printf("ERROR: -min-idx option needs an argument.\n");
				PrintUsage();
				return 1;
			}

			input_min_idx = atoi(argv[ai]);
			continue;
		}

		if (strcmp(argv[ai], "-max-idx") == 0)
		{
			if (++ai >= argc)
			{
				printf("ERROR: -max-idx option needs an argument.\n");
				PrintUsage();
				return 1;
			}

			input_max_idx = atoi(argv[ai]);
			continue;
		}

		if (strcmp(argv[ai], "-output") == 0)
		{
			if (++ai >= argc)
			{
				printf("ERROR: -output option needs an argument.\n");
				PrintUsage();
				return 1;
			}

			output_file_name = argv[ai];
			continue;
		}

		printf("ERROR: unrecognised option `%s'.\n", argv[ai]);
		PrintUsage();
		return 2;
	}

	// validate parameters
	if (input_list_file_name.empty())
	{
		printf("ERROR: input_list_file_name not set.\n");
		PrintUsage();
		return 3;
	}

	// get input
	vector<string> input_files;
	LoadInputFiles(input_list_file_name, input_min_idx, input_max_idx, input_files);

	printf("> input files\n");
	for (const auto &f : input_files)
		printf("    %s\n", f.c_str());

	fwlite::ChainEvent event(input_files);

	// prepare output
	TFile *f_out = TFile::Open(output_file_name.c_str(), "recreate");

	// book histograms
	PlotGroup p_without_cuts;
	p_without_cuts.Init();

	// settings
	vector<string> triggerPatterns = {
		"HLT_DoublePhoton60_v4",
		"HLT_DoublePhoton85_v5"
	};

	// event loop
	for (event.toBegin(); ! event.atEnd(); ++event)
	{
		// get trigger data
		fwlite::Handle<TriggerResults> triggerResults;
		triggerResults.getByLabel(event, "TriggerResults", "", "HLT");

		const TriggerNames &triggerNames = event.triggerNames(*triggerResults);

		// select desired triggers
		bool trigger_selected = false;
		for (const auto &tp : triggerPatterns)
		{
			signed int idx = triggerNames.triggerIndex(tp);

			if (idx < 0)
				continue;

			int ssize = triggerResults->size();
			if (idx >= ssize)
				continue;

			printf("idx = %i\n", idx);

			if (triggerResults->accept(idx))
			{
				trigger_selected = true;
				break;
			}
		}

		if (!trigger_selected)
			continue;

		// get di-photon and di-proton data
		fwlite::Handle< vector<flashgg::DiProtonDiPhotonCandidate> > diphpr;
		diphpr.getByLabel(event, "flashggDiProtonsDiPhotons");

		for (unsigned int i = 0; i < diphpr->size(); i++)
		{
			const flashgg::DiProtonDiPhotonCandidate &pc = diphpr->at(i);
	
			// kinematics
			double p0 = 6500.;	// GeV
		
			LorentzVector p4_init(0., 0., 0., 2.* p0);
		
			LorentzVector p4_diphoton = pc.diphoton()->p4();
		
			// xi's are positive
			// without guarantee: proton1 is left arm, proton2 is right arm
			double xi_L = pc.diproton()->proton1()->xi();
			double xi_R = pc.diproton()->proton2()->xi();
		
			// TODO: verify L/R conventions TOTEM vs. CMS
			LorentzVector p4_diproton(0., 0., p0*(xi_L - xi_R), p0*(2. - xi_L - xi_R));
		
			LorentzVector p4_missing = p4_init - p4_diproton - p4_diphoton;
		
			// fill after-cuts histograms
			p_without_cuts.h_diproton_px->Fill(p4_diproton.px());
			p_without_cuts.h_diproton_py->Fill(p4_diproton.py());
			p_without_cuts.h_diproton_pz->Fill(p4_diproton.pz());
			p_without_cuts.h_diproton_pT->Fill(p4_diproton.pt());
			p_without_cuts.h_diproton_m->Fill(p4_diproton.mass());
		
			p_without_cuts.h_diphoton_px->Fill(p4_diphoton.px());
			p_without_cuts.h_diphoton_py->Fill(p4_diphoton.py());
			p_without_cuts.h_diphoton_pz->Fill(p4_diphoton.pz());
			p_without_cuts.h_diphoton_pT->Fill(p4_diphoton.pt());
			p_without_cuts.h_diphoton_m->Fill(p4_diphoton.mass());
		
			p_without_cuts.h_missing_px->Fill(p4_missing.px());
			p_without_cuts.h_missing_py->Fill(p4_missing.py());
			p_without_cuts.h_missing_pz->Fill(p4_missing.pz());
			p_without_cuts.h_missing_pT->Fill(p4_missing.pt());
			p_without_cuts.h_missing_m->Fill(p4_missing.mass());

			p_without_cuts.h2_diph_pT_vs_diph_m->Fill(p4_diphoton.mass(), p4_diphoton.pt());
			p_without_cuts.h2_miss_m_vs_diph_m->Fill(p4_diphoton.mass(), p4_missing.mass());
			p_without_cuts.h2_miss_m_vs_dipr_m->Fill(p4_diproton.mass(), p4_missing.mass());
			p_without_cuts.h2_miss_m_vs_diph_pT->Fill(p4_diphoton.pt(), p4_missing.mass());
		}
	}

	// save plots
	gDirectory = f_out->mkdir("without cuts");
	p_without_cuts.Write();

	// clean up
	delete f_out;

	return 0;
}
