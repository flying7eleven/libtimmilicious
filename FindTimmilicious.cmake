# Locate registration
#
# This module defines
# TIMMILICIOUS_FOUND: if false, do not try to link to registration
# TIMMILICIOUS_LIBRARY, TIMMILICIOUS_LIBRARIES, TIMMILICIOUS_LIBS: where to find libtimmilicious
# TIMMILICIOUS_INCLUDE_DIR, TIMMILICIOUS_INCLUDE_DIRS, TIMMILICIOUS_INCLUDE_PATH: where to find the libtimmilicious header
#

set(_INCLUDEDIRS ENV CPLUS_INCLUDE_PATH)
set(_LIBDIRS ENV LD_LIBRARY_PATH)

# find the registration include directory
find_path(_INCLUDE_DIR timmilicious/timmilicious.hxx
PATHS
/usr/local/include/
/usr/include/
/opt/include/
/opt/local/include/
${_INCLUDEDIRS}
)

# find the registration library
find_library(TIMMILICIOUS_LIBRARY 
NAMES timmilicious
PATH_SUFFIXES lib64 lib
PATHS 
/usr/local
/usr
/opt/local
/opt
${_LIBDIRS}
)
SET ( TIMMILICIOUS_LIBS ${TIMMILICIOUS_LIBRARY} )
SET ( TIMMILICIOUS_LIBRARIES ${TIMMILICIOUS_LIBRARY} )
SET ( TIMMILICIOUS_INCLUDE_DIRS ${TIMMILICIOUS_INCLUDE_DIR} )
SET ( TIMMILICIOUS_INCLUDE_PATH ${TIMMILICIOUS_INCLUDE_DIR} )

# handle the QUIETLY and REQUIRED arguments and set REGISTRATION_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TIMMILICIOUS DEFAULT_MSG TIMMILICIOUS_INCLUDE_DIR TIMMILICIOUS_LIBRARY)
