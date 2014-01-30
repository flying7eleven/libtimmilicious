#include <timmilicious/ui/ProgressBar.hxx>
#include <boost/thread/lock_guard.hpp>
#include <cstdio>
#include <cstring> // memset
#include <unistd.h>
#include <sys/ioctl.h>
using namespace timmilicious::ui;

ProgressBar::ProgressBar() throw( ) {
	this->mCurrentProgress = 0;
	this->mMaxProgress = 100;
	this->mProgressBarWidth = 50;
	this->mStatusText = "";
}

ProgressBar::~ProgressBar() throw( ) {
	// nothing to do here
}

void ProgressBar::setProgress( const unsigned int progress, bool refresh ) throw( std::range_error ) {
	if( progress > this->mMaxProgress ) {
		throw std::range_error( "The new progress must be between 0 and the max. value of the progress." );
	}
	this->mCurrentProgress = progress;
	if( refresh ) {
		this->updateProgress();
	}
}

void ProgressBar::setProgressTS( const unsigned int progress, bool refresh ) throw( std::range_error ) {
	boost::lock_guard< boost::mutex > guard( this->mCurrentProgressValueMutex );

	this->setProgress( progress, refresh );
}

unsigned int ProgressBar::getProgress() const throw( ) {
	return this->mCurrentProgress;
}

void ProgressBar::increaseProgress( const unsigned int val, bool refresh ) throw( std::range_error ) {
	if( val + this->mCurrentProgress > this->mMaxProgress ) {
		throw std::range_error( "The new progress must be between 0 and the max. value of the progress." );
	}
	this->mCurrentProgress += val;
	if( refresh ) {
		this->updateProgress();
	}
}

void ProgressBar::increaseProgressTS( const unsigned int val, bool refresh ) throw( std::range_error ) {
	boost::lock_guard< boost::mutex > guard( this->mCurrentProgressValueMutex );

	this->increaseProgress( val, refresh );
}

unsigned short int ProgressBar::getTerminalWidth( int fileDescriptor ) const throw( ) {
	const unsigned short default_tty = 80;
	const unsigned short default_notty = 0;
	unsigned short termwidth = 0;

	//
	if( !isatty( fileDescriptor ) ) {
		return default_notty;
	}

	//
#if defined( TIOCGSIZE )
	struct ttysize win;
	if( ioctl( fileDescriptor, TIOCGSIZE, &win ) == 0 ) {
		termwidth = win.ts_cols;
	}
#elif defined( TIOCGWINSZ )
	struct winsize win;
	if( ioctl( fileDescriptor, TIOCGWINSZ, &win ) == 0 ) {
		termwidth = win.ws_col;
	}
#endif

	//
	return termwidth == 0 ? default_tty : termwidth;
}

void ProgressBar::setStatusText( const std::string & status ) throw( ) {
	this->mStatusText = status;
}

void ProgressBar::setMaxProgress( const unsigned int max ) throw( std::range_error ) {
	if( max < this->mCurrentProgress ) {
		throw std::range_error( "The maximum value must be the same as the current progress or higher." );
	}
	this->mMaxProgress = max;
}

void ProgressBar::updateProgress() throw( ) {
	char percentBuffer[ 6 ];

	// clear the percent buffer
	memset( percentBuffer, 0, sizeof( char ) * 6 );

	// get the current number of columns for the active terminal
	const unsigned short int terminalColumns = this->getTerminalWidth( fileno( stdout ) );

	// calculate some important values
	const float currentProgress = ( static_cast< float >( this->mCurrentProgress ) / static_cast< float >( this->mMaxProgress ) ) * 100.0f;
	const unsigned short int numberOfSpaces = terminalColumns - this->mProgressBarWidth - 2 - 6 - this->mStatusText.length(); // progress indicator - bar indicator - number pct - status len
	const unsigned short int progressDone = static_cast< unsigned short int >( currentProgress / ( 100.0f / this->mProgressBarWidth ) );
	const unsigned short int progressNotDone = this->mProgressBarWidth - progressDone;

	// show the text for the current status the user has set
	fputs( this->mStatusText.c_str(), stdout );

	// write the current progress as a number into a buffer
	sprintf( percentBuffer, " % 4d%%", static_cast< int >( currentProgress ) );

	// just show the progress bar if we have enough room to do that
	if( true ) {

		// put in as many spaces that the progress bar is right-aligned
		for( int i = 0; i < numberOfSpaces; ++i ) {
			putchar( ' ' );
		}

		// indicate the start of the progress bar
		putchar( '[' );

		// put the markers for the already done work
		for( unsigned short int i = 0; i < progressDone; ++i ) {
			putchar( '#' );
		}

		// put the markers for the work not done
		for( unsigned short int i = 0; i < progressNotDone; ++i ) {
			putchar( '-' );
		}

		// indicate the end of the progress bar
		putchar( ']' );
	}

	// print the current progress as number
	fputs( percentBuffer, stdout );
	if( this->mCurrentProgress == this->mMaxProgress ) {
		fputs( "\n", stdout );
	} else {
		fputs( "\r", stdout );
	}
	fflush( stdout );
}
