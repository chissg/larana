# OpFlashFinder_module.cc is not built - it seems specific to uboone
art_make(
  LIB_LIBRARIES
    lardataobj_RecoBase
    larcorealg_Geometry
    art::Framework_Services_Registry
    messagefacility::MF_MessageLogger
    fhiclcpp::fhiclcpp
    cetlib_except::cetlib_except
    ROOT::Core
    ROOT::Hist
  )

install_headers()
install_source()
