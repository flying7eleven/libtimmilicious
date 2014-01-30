# - Try to find Timmilicious
# Once done this will define
#
#  TIMMILICIOUS_FOUND - system has libtimmilicious
#  TIMMILICIOUS_INCLUDE_DIR - the libtimmilicious include directory
#  TIMMILICIOUS_LIBRARIES - Link these to use libtimmilicious

# find the libtimmilicious include directory
FIND_PATH( TIMMILICIOUS_INCLUDE_DIR timmilicious/timmilicious.hxx
		PATHS
			/usr/local/include/
			/usr/include/
			/opt/include/
			/opt/local/include/
			${TIMMILICIOUS_DIR}/include
			$ENV{CPLUS_INCLUDE_PATH}
	)

# find the libtimmilicious library
FIND_LIBRARY( TIMMILICIOUS_LIBRARIES 
		NAMES
			timmilicious
		PATH_SUFFIXES
			lib64 lib
		PATHS 
			/usr/local
			/usr
			/opt/local
			/opt
			${TIMMILICIOUS_DIR}/lib
			$ENV{LD_LIBRARY_PATH}
	)

# handle the QUIETLY and REQUIRED arguments and set TIMMILICIOUS_FOUND to TRUE if all listed variables are TRUE
INCLUDE( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( TIMMILICIOUS DEFAULT_MSG TIMMILICIOUS_INCLUDE_DIR TIMMILICIOUS_LIBRARIES )
