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
#if !defined( __TIMMILICIOUS_IO_HDF5_HXX__ )
	#define __TIMMILICIOUS_IO_HDF5_HXX__

//
#include <hdf5.h>
#include <string>

namespace timmilicious {

	namespace io {

		/**
		 *
		 */
		class HDF5 {
			public:
				/**
				 *
				 * \param file
				 * \param overwrite
				 */
				HDF5( const std::string & file, const bool & overwrite = false );

				/**
				 *
				 */
				virtual ~HDF5();

				/**
				 *
				 * \param fileNameInContainer
				 * \param imageFile
				 * \param pathInsideHDF5
				 */
				void addImageToHDF5( const std::string & fileNameInContainer, const std::string & imageFile, const std::string & pathInsideHDF5 = "/" );

				/**
				 *
				 * \param groupPath
				 */
				void createGroup( const std::string & groupPath );

				/**
				 *
				 * \param groupPath
				 * \return
				 */
				bool groupExists( const std::string & groupPath ) const;

			private:
				hid_t mFileId; // << TODO

		}; /* class HDF5 */

	} /* namespace io */

} /* namespace timmilicious */

#endif /* if !defined( __TIMMILICIOUS_IO_HDF5_HXX__ ) */
