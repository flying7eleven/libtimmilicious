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
#include <timmilicious/io/HDF5.hxx>
using namespace timmilicious::io;

// #include <awesomeIO/ReaderFactory.h>
// #include <awesomeIO/iReader.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>

HDF5::HDF5( const std::string & file, const bool & overwrite ) noexcept( false ) {
	// check if a valid path was supplied or not
	if( file.length() <= 0 ) {
		throw std::invalid_argument( "You have to supply a correct file path." );
	}

	// if we should overwrite the file, do so
	if( overwrite ) {
		this->mFileId = H5Fcreate( file.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT );
		H5Fclose( this->mFileId );
	}
	this->mFileId = H5Fopen( file.c_str(), H5F_ACC_CREAT | H5F_ACC_RDWR, H5P_DEFAULT );

	// check if the file was opened correctly
	if( this->mFileId < 0 ) {
		// TODO: error handling
	}
}

HDF5::~HDF5() noexcept {
	if( this->mFileId > -1 ) {
		H5Fclose( this->mFileId );
		this->mFileId = -1;
	}
}

bool HDF5::groupExists( const std::string & groupPath ) const noexcept {
	std::vector< std::string > splittedPath;

	// if the check is if the root path exists, just return true
	if( unlikely( groupPath.length() == 1 && groupPath == "/" ) ) {
		return true;
	}

	// split the supplied path into submodules
	boost::algorithm::split( splittedPath, groupPath, boost::is_any_of( "/" ) );

	// loop through the paths
	boost::filesystem::path currentGroupPath( "/" );

	//
	for( std::vector< std::string >::const_iterator i = splittedPath.begin(); i != splittedPath.end(); ++i ) {
		// skip the first (empty entry)
		if( i->length() < 1 ) {
			continue;
		}

		// check if the group exists, if not we can return false
		currentGroupPath /= *i;
		if( H5Lexists( this->mFileId, currentGroupPath.c_str(), H5P_DEFAULT ) == 0 ) {
			return false;
		}
	}

	// it seems that the path exists
	return true;
}

void HDF5::addMatrix( const cv::Mat & matrix, const std::string & pathInsideHDF5, const std::string & fileNameInContainer ) noexcept {
	hsize_t dims[ 2 ];
	hid_t dataspace_id, adataspace_id, dataset_id, attribute_id;
	herr_t status;
	hsize_t adims = 1;
	bool threeChan = false;

	// check if the group already exists, of not create it
	if( !this->groupExists( pathInsideHDF5 ) ) {
		this->createGroup( pathInsideHDF5 );
	}

	// check which native type should be used
	int nativeType = H5T_STD_REF_OBJ;
	switch( matrix.type() ) {
		case CV_8U:
			nativeType = H5T_STD_U8LE;
			threeChan = false;
			break;
		case CV_8S:
			nativeType = H5T_STD_I8LE;
			threeChan = false;
			break;
		case CV_8UC3: // 8 bit RGB
			nativeType = H5T_STD_U8LE;
			threeChan = true;
			break;
		default:
			std::cerr << "ERROR: Image type is unkown: " << matrix.type() << std::endl; // TODO: better error handling
	}

	// create the data space for the dataset
	dims[ 0 ] = static_cast< hsize_t >( matrix.rows );
	dims[ 1 ] = static_cast< hsize_t >( matrix.cols * ( threeChan ? 3 : 1 ) );
	dataspace_id = H5Screate_simple( 2, dims, NULL );

	// open the requested group
	hid_t groupId = H5Gopen( this->mFileId, pathInsideHDF5.c_str(), H5P_DEFAULT );

	// create the dataset
	dataset_id = H5Dcreate2( groupId, fileNameInContainer.c_str(), nativeType, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT );

	//
	status = H5Dwrite( dataset_id, nativeType, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT, matrix.ptr() );

	// determine the value for the attribute which indicates if it is a color image or not
	const int32_t matrixType = matrix.type();

	// create the type of the attribute
	adataspace_id = H5Screate_simple( 1, &adims, NULL );

	// define the name and type of the attribute
	attribute_id = H5Acreate2( dataset_id, "MatrixType", H5T_STD_I32LE, adataspace_id, H5P_DEFAULT, H5P_DEFAULT );

	// write the attribute value to the file
	status = H5Awrite( attribute_id, H5T_NATIVE_UCHAR, &matrixType );

	// close the attribute itself
	status = H5Aclose( attribute_id );

	// close the data space used for the attribute
	status = H5Sclose( adataspace_id );

	// end access to the dataset and release resources used by it.
	status = H5Dclose( dataset_id );

	// terminate access to the data space.
	status = H5Sclose( dataspace_id );

	// close the opened group again
	status = H5Gclose( groupId );
}

void HDF5::createGroup( const std::string & groupPath ) noexcept {
	std::vector< std::string > splittedPath;

	// if the user wants to create the root element, just skip this step
	if( unlikely( groupPath.length() == 1 && groupPath == "/" ) ) {
		return;
	}

	// split the supplied path into submodules
	boost::algorithm::split( splittedPath, groupPath, boost::is_any_of( "/" ) );

	// loop through the paths
	boost::filesystem::path currentGroupPath( "/" );

	for( std::vector< std::string >::const_iterator i = splittedPath.begin(); i != splittedPath.end(); ++i ) {
		// skip the first (empty entry)
		if( i->length() < 1 ) {
			continue;
		}

		// check if the group exists, if not create it
		currentGroupPath /= *i;
		bool cGroupExists = this->groupExists( currentGroupPath.string() );
		if( !cGroupExists ) {
			hid_t group_new = H5Gcreate( this->mFileId, currentGroupPath.string().c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT );
			H5Gclose( group_new );
		}
	}
}
