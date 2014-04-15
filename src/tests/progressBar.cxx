#include <gtest/gtest.h>
#include <timmilicious/ui/ProgressBar.hxx>
using namespace timmilicious::ui;

TEST( ProgressBar, Constructor ) {
	ASSERT_NO_THROW( ProgressBar() );
	ASSERT_NO_THROW( ProgressBar( "" ) );
	ASSERT_NO_THROW( ProgressBar( "This is a Test" ) );
	ASSERT_NO_THROW( ProgressBar( "", 0 ) );
	ASSERT_NO_THROW( ProgressBar( "This is a Test", 0 ) );
	ASSERT_NO_THROW( ProgressBar( "", 10 ) );
	ASSERT_NO_THROW( ProgressBar( "This is a Test", 10 ) );
	ASSERT_THROW( ProgressBar( "", -10 ), std::invalid_argument );
	ASSERT_THROW( ProgressBar( "This is a Test", -10 ), std::invalid_argument );
}
