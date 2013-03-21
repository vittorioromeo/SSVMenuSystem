cmake_minimum_required(VERSION 2.8)
project(SSVMenuSystem)

set(SSVMENUSYSTEM_BUILD_SHARED_LIB FALSE CACHE BOOL "Build shared libraries.")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type." FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" CACHE STRING "" FORCE)

if(SSVMENUSYSTEM_BUILD_SHARED_LIB)
	set(LIB_TYPE SHARED)
else()
	set(LIB_TYPE STATIC)
endif()

set(SRC_DIR "src")
set(INC_DIR "include")

set(
	SOURCES
	${INC_DIR}/${PROJECT_NAME}/Menu/Category.h
	${INC_DIR}/${PROJECT_NAME}/Menu/ItemBase.h
	${INC_DIR}/${PROJECT_NAME}/Menu/Menu.h
	${INC_DIR}/${PROJECT_NAME}/Items/Goto.h
	${INC_DIR}/${PROJECT_NAME}/Items/Single.h
	${INC_DIR}/${PROJECT_NAME}/Items/Slider.h
	${INC_DIR}/${PROJECT_NAME}/Items/Toggle.h
	${SRC_DIR}/${PROJECT_NAME}/Menu/Category.cpp
	${SRC_DIR}/${PROJECT_NAME}/Menu/ItemBase.cpp
	${SRC_DIR}/${PROJECT_NAME}/Menu/Menu.cpp
	${SRC_DIR}/${PROJECT_NAME}/Items/Goto.cpp
	${SRC_DIR}/${PROJECT_NAME}/Items/Single.cpp
	${SRC_DIR}/${PROJECT_NAME}/Items/Slider.cpp
	${SRC_DIR}/${PROJECT_NAME}/Items/Toggle.cpp
)

include_directories(${INC_DIR})
add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})

if(SSVMENUSYSTEM_BUILD_SHARED_LIB)
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)
else()
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX -s)
endif()

if(WIN32)
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
else()
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION lib
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
endif()

install(DIRECTORY ${INC_DIR}
	DESTINATION .)
