/**
 * libtimmilicious - A library for beautifying your console output
 * Copyright (C) 2014 Tim Hütz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see {http://www.gnu.org/licenses/}.
 */
#if !defined( __TIMMILICIOUS_TIMMILICIOUS_HXX__ )
	#define __TIMMILICIOUS_TIMMILICIOUS_HXX__

/**
 * Use this macro for if-branches which are likely to be entered. This helps the branch prediction to optimize
 * the code and therefore the speed of the execution.
 */
#if !defined( likely )
	#if defined( __GNUC__ )
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
	#if defined( __GNUC__ )
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
	 * Get the API verison of the library.
	 *
	 * \returns The API version for the library.
	 *
	 * \warning The method is *NOT* thread-safe.
	 */
	const char *getAPIVersion();

} /* namespace timmilicious*/

#endif /* if !defined( __TIMMILICIOUS_TIMMILICIOUS_HXX__ ) */
