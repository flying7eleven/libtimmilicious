#include <gtest/gtest.h>
#include <timmilicious/ui/ProgressBar.hxx>
using namespace timmilicious::ui;

TEST( ProgressBar, Constructor ) {
	ASSERT_NO_THROW( ProgressBar() );
	ASSERT_NO_THROW( ProgressBar( "" ) );
	ASSERT_NO_THROW( ProgressBar( "This is a test" ) );
	ASSERT_NO_THROW( ProgressBar( "", 0 ) );
	ASSERT_NO_THROW( ProgressBar( "This is a test", 0 ) );
	ASSERT_NO_THROW( ProgressBar( "", 10 ) );
	ASSERT_NO_THROW( ProgressBar( "This is a test", 10 ) );
	ASSERT_THROW( ProgressBar( "", -10 ), std::invalid_argument );
	ASSERT_THROW( ProgressBar( "This is a test", -10 ), std::invalid_argument );
}

TEST( ProgressBar, setStatusText ) {
	ProgressBar progress;

	ASSERT_NO_THROW( progress.setStatusText( "" ) );
	ASSERT_NO_THROW( progress.setStatusText( "This is a test" ) );
}

TEST( ProgressBar, getMaxProgress ) {
	ProgressBar progress;

	ASSERT_EQ( 100, progress.getMaxProgress() ); // should be 100 if nothing was set
}

TEST( ProgressBar, getProgress ) {
	ProgressBar progress;

	ASSERT_EQ( 0, progress.getProgress() ); // should be zero if nothing was set
}

TEST( ProgressBar, setProgress ) {
	ProgressBar progress;

	ASSERT_THROW( progress.setProgress( -10 ), std::invalid_argument );
	ASSERT_NO_THROW( progress.setProgress( 10 ) );
	ASSERT_EQ( 10, progress.getProgress() );
	ASSERT_THROW( progress.setProgress( progress.getMaxProgress() + 1 ), std::range_error );
}

TEST( ProgressBar, setProgressTS ) {
	ProgressBar progress;

	ASSERT_THROW( progress.setProgressTS( -10 ), std::invalid_argument );
	ASSERT_NO_THROW( progress.setProgressTS( 10 ) );
	ASSERT_EQ( 10, progress.getProgress() );
	ASSERT_THROW( progress.setProgressTS( progress.getMaxProgress() + 1 ), std::range_error );
}

TEST( ProgressBar, setMaxProgress ) {
	ProgressBar progress;

	ASSERT_NO_THROW( progress.setMaxProgress( 110 ) );
	ASSERT_EQ( 110, progress.getMaxProgress() );
	ASSERT_THROW( progress.setMaxProgress( -110 ), std::invalid_argument ); // the max. progress should be at least
	ASSERT_THROW( progress.setMaxProgress( 0 ), std::invalid_argument ); // 1 (or better bigger)

	progress.setProgress( 10, false );
	ASSERT_THROW( progress.setMaxProgress( 9 ), std::range_error ); // max. progress is smaller than the current progress
	ASSERT_NO_THROW( progress.setMaxProgress( 10 ) ); // max. progress is the same as the current progress (100% finished)
}

TEST( ProgressBar, showTimeEstimation ) {}

TEST( ProgressBar, updateProgress ) {}

TEST( ProgressBar, increaseProgress ) {}

TEST( ProgressBar, increaseProgressTS ) {}
