/**
 * This file is part of libTimmilicious.
 * Copyright (C) 2014 Tim Hütz
 *
 * libTimmilicious is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libTimmilicious is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * ERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libTimmilicious. If not, see <http://www.gnu.org/licenses/>.
 */
#if !defined( __TIMMILICIOUS_TIMMILICIOUS_HXX__ )
	#define __TIMMILICIOUS_TIMMILICIOUS_HXX__

/**
 * Use this macro for if-branches which are likely to be entered. This helps the branch prediction to optimize
 * the code and therefore the speed of the execution.
 */
#if !defined( likely )
	#if defined( __GNUC__ ) || defined( __clang__ )
		#define likely( x ) __builtin_expect( !!( x ), 1 )
	#else
		#define likely( x ) x
	#endif
#else
	#error "It seems that the likely(x) marcro was defined previously. Check that before using libTimmilicous!"
#endif

/**
 * Use this macro for if-branches which are unlikely to be entered. This helps the branch prediction to optimize
 * the code and therefore the speed of the execution.
 */
#if !defined( unlikely )
	#if defined( __GNUC__ ) || defined( __clang__ )
		#define unlikely( x ) __builtin_expect( !!( x ), 0 )
	#else
		#define unlikely( x ) x
	#endif
#else
	#error "It seems that the unlikely(x) marcro was defined previously. Check that before using libTimmilicous!"
#endif

namespace timmilicious {

	/**
	 * Get the ABI version of the library.
	 *
	 * \returns The ABI version for the library.
	 *
	 * \warning The method is *NOT* thread-safe.
	 */
	unsigned short int getABIVersion();

	/**
	 * Get the API version of the library.
	 *
	 * The last release of the library was version 1.0.0 but you are using a dev.
	 * version of the library which has some new features implemented. The full
	 * version would look like "1.0.0-14-g3fe", which means that there were 14
	 * code changes since the last release. In this case, this method would
	 * return "1.0.0-14-g3fe". For release versions the return value is the same
	 * as returned in \ref timmilicious::getShortAPIVersion.
	 *
	 * \returns The API version for the library.
	 *
	 * \warning The method is *NOT* thread-safe.
	 */
	const char *getAPIVersion();

	/**
	 * Get the (short) API version of the library.
	 *
	 * Most of the times this is enough to query. The returned string will contain
	 * just the major minor and patch version of the library but not the drift
	 * from the last version number. For example:
	 *
	 * The last release of the library was version 1.0.0 but you are using a dev.
	 * version of the library which has some new features implemented. The full
	 * version would look like "1.0.0-14-g3fe", which means that there were 14
	 * code changes since the last release. In this case, this method would
	 * return "1.0.0".
	 *
	 * \returns The API version for the library.
	 *
	 * \warning The method is *NOT* thread-safe.
	 */
	const char *getShortAPIVersion();

} /* namespace timmilicious*/

#endif /* if !defined( __TIMMILICIOUS_TIMMILICIOUS_HXX__ ) */
