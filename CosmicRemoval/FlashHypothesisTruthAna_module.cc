////////////////////////////////////////////////////////////////////////
// Class:       FlashHypothesisTruthAna
// Module Type: analyzer
// File:        FlashHypothesisTruthAna_module.cc
// Author:      Wes Ketchum
// 
// Description: Module that compares a reconstructed flash (from optical
//              system) with a flash hypothesis based on the truth particle.
// Input:       recob::OpFlash, simb::MCParticle
//
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "art/Framework/Services/Optional/TFileService.h"

#include <memory>

#include "BeamFlashTrackMatchTaggerAlg.h"

namespace cosmic {
  class FlashHypothesisTruthAna;
}

class cosmic::FlashHypothesisTruthAna : public art::EDAnalyzer {
public:
  explicit FlashHypothesisTruthAna(fhicl::ParameterSet const & p);
  // The destructor generated by the compiler is fine for classes
  // without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  FlashHypothesisTruthAna(FlashHypothesisTruthAna const &) = delete;
  FlashHypothesisTruthAna(FlashHypothesisTruthAna &&) = delete;
  FlashHypothesisTruthAna & operator = (FlashHypothesisTruthAna const &) = delete;
  FlashHypothesisTruthAna & operator = (FlashHypothesisTruthAna &&) = delete;
  void reconfigure(fhicl::ParameterSet const& p);
  void beginJob() override;
  void analyze(art::Event const& e) override;


private:

  // Declare member data here.
  BeamFlashTrackMatchTaggerAlg fAlg;
  std::string fMCModuleLabel;
  std::string fFlashModuleLabel;
  
};


cosmic::FlashHypothesisTruthAna::FlashHypothesisTruthAna(fhicl::ParameterSet const & p)
  : EDAnalyzer(p),
    fAlg(p.get<fhicl::ParameterSet>("BeamFlashTrackMatchAlgParams")),
    fMCModuleLabel(p.get<std::string>("MCModuleLabel")),
    fFlashModuleLabel(p.get<std::string>("FlashModuleLabel"))
{}

void cosmic::FlashHypothesisTruthAna::reconfigure(fhicl::ParameterSet const& p){
  fhicl::ParameterSet alg_params = p.get<fhicl::ParameterSet>("BeamFlashTrackMatchAlgParams");
  fAlg.reconfigure(alg_params);

  fMCModuleLabel = p.get<std::string>("MCModuleLabel");   
  fFlashModuleLabel = p.get<std::string>("FlashModuleLabel");
}

void cosmic::FlashHypothesisTruthAna::beginJob(){
  art::ServiceHandle<art::TFileService> tfs;  
  fAlg.SetHypothesisComparisonTree(tfs->make<TTree>("hc_tree", "HypothesisComparisonTree"));
}

void cosmic::FlashHypothesisTruthAna::analyze(art::Event const& evt)
{
  //services we'll be using
  art::ServiceHandle<geo::Geometry> geomHandle;
  geo::Geometry const& geom(*geomHandle);
  art::ServiceHandle<phot::PhotonVisibilityService> pvsHandle;
  phot::PhotonVisibilityService const& pvs(*pvsHandle);
  art::ServiceHandle<util::LArProperties> larpHandle;
  util::LArProperties const& larp(*larpHandle);
  art::ServiceHandle<opdet::OpDigiProperties> opdigipHandle;
  opdet::OpDigiProperties const& opdigip(*opdigipHandle);

  //Get Flashes from event.
  art::Handle< std::vector<recob::OpFlash> > flashHandle;
  evt.getByLabel(fFlashModuleLabel, flashHandle);
  std::vector<recob::OpFlash> const& flashVector(*flashHandle);

  //get mcparticles out of the event
  art::Handle< std::vector<simb::MCParticle> > mcParticleHandle;
  evt.getByLabel(fMCModuleLabel,mcParticleHandle);
  std::vector<simb::MCParticle> const& mcParticleVector(*mcParticleHandle);

  fAlg.RunHypothesisComparison(evt.run(),
			       evt.event(),
			       flashVector, mcParticleVector, 
			       geom, pvs, larp, opdigip);
}

DEFINE_ART_MODULE(cosmic::FlashHypothesisTruthAna)
