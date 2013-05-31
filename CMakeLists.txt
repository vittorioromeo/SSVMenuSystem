cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type.")
project(SSVMenuSystem)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -W -pedantic" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-fno-omit-frame-pointer -g3 -gdwarf-2 -O0" CACHE STRING "" FORCE)
set(SSVMENUSYSTEM_BUILD_SHARED_LIB TRUE CACHE BOOL "Build shared libraries.")

if(SSVMENUSYSTEM_BUILD_SHARED_LIB)
	set(LIB_TYPE SHARED)
else()
	set(LIB_TYPE STATIC)
endif()

set(SRC_DIR "src")
set(INC_DIR "include")

file(GLOB SRC_LIST
	"${INC_DIR}/${PROJECT_NAME}/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/Menu/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/Menu/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/Items/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/Items/*.cpp"
)

include_directories(${INC_DIR})
add_library(${PROJECT_NAME} ${LIB_TYPE} ${SRC_LIST})

if(SSVMENUSYSTEM_BUILD_SHARED_LIB)
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)
else()
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX -s)
endif()

if(WIN32)
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
else()
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION lib LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif()

install(DIRECTORY ${INC_DIR} DESTINATION .)
