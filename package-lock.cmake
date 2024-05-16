# CPM Package Lock
# This file should be committed to version control

# zstd
CPMDeclarePackage(zstd
  NAME zstd
  GIT_TAG v1.5.5
  GIT_REPOSITORY https://github.com/facebook/zstd.git
  GIT_SHALLOW TRUE
  EXCLUDE_FROM_ALL TRUE
  SOURCE_SUBDIR build/cmake
  OPTIONS
    "ZSTD_BUILD_PROGRAMS OFF"
    "ZSTD_BUILD_CONTRIB OFF"
    "ZSTD_BUILD_TESTS OFF"
    "ZSTD_BUILD_STATIC ON"
    "ZSTD_BUILD_SHARED OFF"
    "ZSTD_LEGACY_SUPPORT OFF"
)

CPMDeclarePackage(libdwarf
  NAME libdwarf
  GIT_TAG v0.9.2
  GIT_REPOSITORY https://github.com/jeremy-rifkin/libdwarf-lite.git
  GIT_SHALLOW TRUE
  EXCLUDE_FROM_ALL TRUE
  OPTIONS
    "PIC_ALWAYS TRUE"
    "BUILD_DWARFDUMP FALSE"
)