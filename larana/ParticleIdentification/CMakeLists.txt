art_make(
  LIB_LIBRARIES
    art::Framework_Principal
    art::Framework_Services_Registry
    art::Persistency_Provenance
    art_root_io::TFileService_service
    art_root_io::tfile_support
    art::Utilities
    fhiclcpp::fhiclcpp
    messagefacility::MF_MessageLogger
    ROOT::Core
    ROOT::Hist
    ROOT::MathCore
    ROOT::Physics
    ROOT::RIO
    ROOT::TMVA
    ROOT::Tree
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    larcorealg_Geometry
    lardataobj_AnalysisBase
    larreco_Calorimetry
    nusimdata::SimulationBase
  MODULE_LIBRARIES
   larana_ParticleIdentification
  )

install_headers()
install_fhicl()
install_source()

add_subdirectory(scripts)
