CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( libTimmilicious )

# set the current verison of the library
SET( TIMMI_LIB_VERSION "1.0.0" )
SET( TIMMI_LIB_SOVERSION "1" ) # should just be changed if the ABI changes

# generate a list of all source files of the library
SET( LIBTIMMI_SOURCE_FILES ${LIBTIMMI_SOURCE_FILES} src/timmilicious/ui/ProgressBar.cxx )

# generate a list of all header files of the library
SET( LIBTIMMI_HEADER_FILES ${LIBTIMMI_HEADER_FILES} src/timmilicious/ui/ProgressBar.hxx )

# add the include directories for building this library
INCLUDE_DIRECTORIES( "${CMAKE_CURRENT_SOURCE_DIR}/src" )

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

# specify how to build the library
ADD_LIBRARY( timmilicious SHARED ${LIBTIMMI_SOURCE_FILES} ${LIBTIMMI_HEADER_FILES} ) 
SET_TARGET_PROPERTIES( timmilicious PROPERTIES VERSION ${TIMMI_LIB_VERSION} SOVERSION ${TIMMI_LIB_SOVERSION} )

# build the testing application
ADD_EXECUTABLE( timmitest_progressbar src/test.cxx )
TARGET_LINK_LIBRARIES( timmitest_progressbar timmilicious )

# define the install actions to perform
INSTALL( TARGETS timmilicious DESTINATION lib )
INSTALL_HEADERS_WITH_DIRECTORY( LIBTIMMI_HEADER_FILES )
