CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( libTimmilicious )

# set the current verison of the library
SET( TIMMI_LIB_VERSION "1.1.0" )
SET( TIMMI_LIB_SOVERSION "2" ) # should just be changed if the ABI changes

# find and configure the required libraries
FIND_PACKAGE( Boost COMPONENTS system thread timer REQUIRED )

# generate a list of all source files of the library
SET( LIBTIMMI_SOURCE_FILES ${LIBTIMMI_SOURCE_FILES} "${PROJECT_BINARY_DIR}/timmilicious.cxx" )
SET( LIBTIMMI_SOURCE_FILES ${LIBTIMMI_SOURCE_FILES} src/timmilicious/ui/ProgressBar.cxx )
SET( LIBTIMMI_SOURCE_FILES ${LIBTIMMI_SOURCE_FILES} src/timmilicious/io/HDF5.cxx )

# generate a list of all header files of the library
SET( LIBTIMMI_HEADER_FILES ${LIBTIMMI_HEADER_FILES} src/timmilicious/timmilicious.hxx )
SET( LIBTIMMI_HEADER_FILES ${LIBTIMMI_HEADER_FILES} src/timmilicious/ui/ProgressBar.hxx )
SET( LIBTIMMI_HEADER_FILES ${LIBTIMMI_HEADER_FILES} src/timmilicious/io/HDF5.hxx )

# set flags to get clean code (at least on UNIX platforms)
IF( UNIX OR CMAKE_COMPILER_IS_GNUCXX )
	IF( CMAKE_COMPILER_IS_GNUCXX )
		SET( CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -std=c++11" CACHE STRING "Flags used by the compiler during all build types." FORCE )
	ELSE()
		SET( CMAKE_CXX_FLAGS "-Wall -Werror -pedantic" CACHE STRING "Flags used by the compiler during all build types." FORCE )
	ENDIF()
ENDIF()

#
SET(CMAKE_MODULES_INSTALL_DIR ${CMAKE_ROOT}/Modules CACHE FILEPATH "Find script and CMake Config file will be installed to this directory")

# add the include directories for building this library
INCLUDE_DIRECTORIES( "${CMAKE_CURRENT_SOURCE_DIR}/src" )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# define a macro to install the header file properly
MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
FOREACH(HEADER ${${HEADER_LIST}})
    STRING( LENGTH ${HEADER} HEADER_LEN )
    MATH( EXPR HEADER_LEN "${HEADER_LEN}-4" )
    STRING( SUBSTRING ${HEADER} 4 ${HEADER_LEN} HEADER2 )
    STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER2})
    INSTALL(FILES ${HEADER} DESTINATION include/${DIR})
ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

#
CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/src/timmilicious/timmilicious.cxx.in" "${PROJECT_BINARY_DIR}/timmilicious.cxx" )

# specify how to build the library
ADD_LIBRARY( timmilicious SHARED ${LIBTIMMI_SOURCE_FILES} ${LIBTIMMI_HEADER_FILES} ) 
TARGET_LINK_LIBRARIES( timmilicious ${Boost_LIBRARIES} )
SET_TARGET_PROPERTIES( timmilicious PROPERTIES VERSION ${TIMMI_LIB_VERSION} SOVERSION ${TIMMI_LIB_SOVERSION} )

# build the testing application
ADD_EXECUTABLE( timmitest_progressbar src/test.cxx )
TARGET_LINK_LIBRARIES( timmitest_progressbar timmilicious )

# define the install actions to perform
INSTALL( TARGETS timmilicious DESTINATION lib )
INSTALL( FILES FindTimmilicious.cmake DESTINATION ${CMAKE_MODULES_INSTALL_DIR} )
INSTALL_HEADERS_WITH_DIRECTORY( LIBTIMMI_HEADER_FILES )
