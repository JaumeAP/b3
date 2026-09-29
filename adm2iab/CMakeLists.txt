# ADM -> IAB conversion package. Kept independent of the cineia executable/
# IMF-to-DCP re-encoding tool: this converts source ADM/BW64 content into
# IAB, cineia repackages an already-authored IAB bitstream into a DCP - two
# separate pipeline stages (see adm_bed_mapping.h for what is implemented so
# far).

add_library(adm2iab STATIC
    adm_bed_mapping.h
    adm_bed_mapping.cpp
)
target_include_directories(adm2iab PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(adm2iab PUBLIC
    IABLib
)
target_include_directories(adm2iab PRIVATE
    ${IABLib_HEADER_PATH}
)

add_executable(adm_bed_mapping_selfcheck
    adm_bed_mapping_selfcheck.cpp
)
target_link_libraries(adm_bed_mapping_selfcheck
    adm2iab
)
target_include_directories(adm_bed_mapping_selfcheck PRIVATE
    ${IABLib_HEADER_PATH}
)
