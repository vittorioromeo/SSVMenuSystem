cmake_minimum_required(VERSION 2.8)
project(SSVMenuSystem)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/SSVCMake/cmake/modules/;${CMAKE_MODULE_PATH}")
include(SSVCMake)

SSVCMake_setDefaultSettings()
SSVCMake_setDefaultFlags()
SSVCMake_setDefaultGlobs()
SSVCMake_findExtlib(SSVUtils)

add_library(HEADER_ONLY_TARGET STATIC ${SRC_LIST})
set_target_properties(HEADER_ONLY_TARGET PROPERTIES LINKER_LANGUAGE CXX)

install(DIRECTORY ${INC_DIR} DESTINATION .)
