cmake_minimum_required(VERSION 3.14)
project(bloom-filter LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Optimization flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")

# Header directories
include_directories(include)

# Source files
set(SOURCE_FILES
    src/MurmurHash3.cpp
    src/bloom_filter_c.cpp
)

# Header files
set(HEADER_FILES
    include/MurmurHash3.h
    include/bloom_filter.hpp
    include/bloom_filter_c.h
)

# Build static library
add_library(bloom_filter_static STATIC ${SOURCE_FILES})
set_target_properties(bloom_filter_static PROPERTIES OUTPUT_NAME bloomfilter)

# Build shared library
add_library(bloom_filter_shared SHARED ${SOURCE_FILES})
set_target_properties(bloom_filter_shared PROPERTIES OUTPUT_NAME bloomfilter)

# Testing
enable_testing()
add_executable(test_bloom tests/test_bloom.cpp)
target_link_libraries(test_bloom bloom_filter_static)
add_test(NAME BloomTest COMMAND test_bloom)

# Installation logic
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(TARGETS bloom_filter_static bloom_filter_shared
    EXPORT BloomFilterTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT BloomFilterTargets
    FILE BloomFilterTargets.cmake
    NAMESPACE BloomFilter::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BloomFilter
)

write_basic_package_version_file(
    BloomFilterConfigVersion.cmake
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    cmake/BloomFilterConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/BloomFilterConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BloomFilter
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/BloomFilterConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/BloomFilterConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BloomFilter
)
