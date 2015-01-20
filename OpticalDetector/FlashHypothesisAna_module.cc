////////////////////////////////////////////////////////////////////////
// Class:       FlashHypothesisAna
// Module Type: analyzer
// File:        FlashHypothesisAna_module.cc
//
// Generated at Mon Jan 19 18:46:10 2015 by Wesley Ketchum using artmod
// from cetpkgsupport v1_08_02.
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

#include "FlashHypothesisAnaAlg.h"

namespace opdet{
  class FlashHypothesisAna;
}

namespace opdet{
  
  class FlashHypothesisAna : public art::EDAnalyzer {
  public:
    explicit FlashHypothesisAna(fhicl::ParameterSet const & p);
    // The destructor generated by the compiler is fine for classes
    // without bare pointers or other resource use.
    
    // Plugins should not be copied or assigned.
    FlashHypothesisAna(FlashHypothesisAna const &) = delete;
    FlashHypothesisAna(FlashHypothesisAna &&) = delete;
    FlashHypothesisAna & operator = (FlashHypothesisAna const &) = delete;
    FlashHypothesisAna & operator = (FlashHypothesisAna &&) = delete;
    
    // Required functions.
    void analyze(art::Event const & e) override;
    
    // Selected optional functions.
    void beginJob() override;
    
  private:
    
    std::string fMCParticleLabel;
    std::string fMCSimPhotonCollectionLabel;
    
    FlashHypothesisAnaAlg fAlg;
    
  };
  
  
  FlashHypothesisAna::FlashHypothesisAna(fhicl::ParameterSet const & p)
    :
    EDAnalyzer(p),
    fMCParticleLabel(p.get<std::string>("MCParticleLabel")),
    fMCSimPhotonCollectionLabel(p.get<std::string>("MCSimPhotonCollectionLabel")),
    fAlg(p.get<fhicl::ParameterSet>("FlashHypothesisAnaAlgParams"))
  {}
  
  void FlashHypothesisAna::analyze(art::Event const & e)
  {
  }
  
  void FlashHypothesisAna::beginJob()
  {
    art::ServiceHandle<geo::Geometry> geoHandle;
    geo::Geometry const& geo(*geoHandle);
    
    art::ServiceHandle<art::TFileService> tfs;    

    fAlg.SetOutputObjects(tfs->make<TTree>(),
			  tfs->make<TH1F>(), tfs->make<TH1F>(), tfs->make<TH1F>(),
			  tfs->make<TH1F>(), tfs->make<TH1F>(), tfs->make<TH1F>(),
			  geo);
    fAlg.SetOpDetPositions(geo);
  }

}

DEFINE_ART_MODULE(opdet::FlashHypothesisAna)
  