#if !defined( __TIMMILICIOUS_TIMMILICIOUS_HXX__ )
	#define __TIMMILICIOUS_TIMMILICIOUS_HXX__

namespace timmilicious {

	/**
	 * Get the ABI version of the library.
	 *
	 * \returns The ABI version for the library.
	 *
	 * \warning The method is *NOT* thread-safe.
	 */
	const unsigned short int getABIVersion();

	/**
	 * Get the API verison of the library.
	 *
	 * \returns The API version for the library.
	 *
	 * \warning The method is *NOT* thread-safe.
	 */
	const char *getAPIVersion();

} /* namespace timmilicious*/

#endif /* if !defined( __TIMMILICIOUS_TIMMILICIOUS_HXX__ ) */
