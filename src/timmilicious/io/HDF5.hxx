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
#include <timmilicious/timmilicious.hxx>
#include <opencv2/opencv.hpp>
#include <boost/any.hpp>
#include <hdf5.h>
#include <string>
#include <map>

namespace timmilicious {

	namespace io {

		/**
		 * This class provides helper methods for accessing data inside of HDF5
		 * container files.
		 */
		class HDF5 {
			public:
				/**
				 * Create a new instance of this class.
				 *
				 * \param[in] file The HDF5 file which should be opened or created.
				 * \param[in] overwrite True if the file should be overwritten (if it exists), false if not.
				 *
				 * \throws std::invalid_argument Will be thrown if an invalid file path was supplied.
				 */
				HDF5( const std::string & file, const bool & overwrite = false ) noexcept( false );

				/**
				 * Destructor of this class.
				 */
				virtual ~HDF5() noexcept;

				/**
				 * Create a new group (path inside of the HDF5 file) for storing data.
				 *
				 * \param[in] groupPath The full path to the group which should be created.
				 */
				void createGroup( const std::string & groupPath ) noexcept;

				/**
				 * Check if the supplied group (path inside of the HDF5 file) exists.
				 *
				 * \param[in] groupPath The group to check.
				 * \return True if the path exists, false if not.
				 */
				bool groupExists( const std::string & groupPath ) const noexcept;

				/**
				 * Adds an OpenCV matrix to the HDF5 container.
				 *
				 * \param[in] matrix The matrix to add to the container file.
				 * \param[in] pathInsideHDF5 The path inside of the container.
				 * \param[in] fileNameInContainer The name of the matrix inside of the container file.
				 */
				void addMatrix( const cv::Mat & matrix, const std::string & pathInsideHDF5, const std::string & fileNameInContainer ) noexcept;

				/**
				 * Get the attributes for a file inside of the HDF5 container.
				 *
				 * \param[in] filenameInsideHDF5 The file inside of the HDF5 container
				 * \return A vector of attributes found for the supplied file.
				 */
				std::map< std::string, boost::any > getAttributes( const std::string & filenameInsideHDF5 ) noexcept;

			private:
				hid_t mFileId; // << The internal handle to the opened HDF5 file.

				ALIGN_CLASS( 4 );

		}; /* class HDF5 */

	} /* namespace io */

} /* namespace timmilicious */

#endif /* if !defined( __TIMMILICIOUS_IO_HDF5_HXX__ ) */
