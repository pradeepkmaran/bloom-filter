#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "BloomFilter::bloom_filter_static" for configuration "Release"
set_property(TARGET BloomFilter::bloom_filter_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(BloomFilter::bloom_filter_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libbloomfilter.a"
  )

list(APPEND _cmake_import_check_targets BloomFilter::bloom_filter_static )
list(APPEND _cmake_import_check_files_for_BloomFilter::bloom_filter_static "${_IMPORT_PREFIX}/lib/libbloomfilter.a" )

# Import target "BloomFilter::bloom_filter_shared" for configuration "Release"
set_property(TARGET BloomFilter::bloom_filter_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(BloomFilter::bloom_filter_shared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libbloomfilter.so"
  IMPORTED_SONAME_RELEASE "libbloomfilter.so"
  )

list(APPEND _cmake_import_check_targets BloomFilter::bloom_filter_shared )
list(APPEND _cmake_import_check_files_for_BloomFilter::bloom_filter_shared "${_IMPORT_PREFIX}/lib/libbloomfilter.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
