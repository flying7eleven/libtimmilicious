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
#include <gtest/gtest.h>
#include <timmilicious/io/HDF5.hxx>
using namespace timmilicious::io;

#define HDF5_TEST_FILE_PATH "/tmp/hdf5test.h5"

TEST( HDF5, Constructor ) {
	ASSERT_THROW( HDF5( "" ), std::invalid_argument );
	ASSERT_THROW( HDF5( "", true ), std::invalid_argument );
	ASSERT_THROW( HDF5( "", false ), std::invalid_argument );
	ASSERT_NO_THROW( HDF5( HDF5_TEST_FILE_PATH ) );
	ASSERT_NO_THROW( HDF5( HDF5_TEST_FILE_PATH, false ) );
	ASSERT_NO_THROW( HDF5( HDF5_TEST_FILE_PATH, true ) );
}

TEST( HDF5, createGroup ) {
	HDF5 file( HDF5_TEST_FILE_PATH, true );

	ASSERT_NO_THROW( file.createGroup( "/" ) ); // the root is always available and should not be created
	ASSERT_NO_THROW( file.createGroup( "/short/path" ) );
	ASSERT_NO_THROW( file.createGroup( "/this/is/a/longer/test/path/inside/of/the/hdf5/file" ) );
}

TEST( HDF5, groupExists ) {
	HDF5 file( HDF5_TEST_FILE_PATH, true );

	ASSERT_EQ( true, file.groupExists( "/" ) ); // the root is always available
	ASSERT_EQ( false, file.groupExists( "/short/path" ) );
	ASSERT_EQ( false, file.groupExists( "/this/is/a/longer/test/path/inside/of/the/hdf5/file" ) );

	file.createGroup( "/short/path" );
	file.createGroup( "/this/is/a/longer/test/path/inside/of/the/hdf5/file" );

	ASSERT_EQ( true, file.groupExists( "/" ) ); // the root is always available
	ASSERT_EQ( true, file.groupExists( "/short/path" ) );
	ASSERT_EQ( true, file.groupExists( "/this/is/a/longer/test/path/inside/of/the/hdf5/file" ) );
}
