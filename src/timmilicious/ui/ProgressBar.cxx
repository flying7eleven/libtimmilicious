#include <timmilicious/ui/ProgressBar.hxx>
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>
using namespace timmilicious::ui;

ProgressBar::ProgressBar() {
	this->mCurrentProgress = 0;
	this->mMaxProgress = 100;
	this->mStatusText = "";
}

ProgressBar::~ProgressBar() {
	// nothing to do here
}

void ProgressBar::setProgress( const unsigned int progress, bool refresh ) throw( std::range_error ) {
	if( progress > this->mMaxProgress || progress < 0 ) {
		throw std::range_error( "The new progress must be between 0.0 and the max. value of the progress." );
	}
	this->mCurrentProgress = progress;
	if( refresh ) {
		this->updateProgress();
	}
}

unsigned int ProgressBar::getProgress() const throw( ) {
	return this->mCurrentProgress;
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
	if( ioctl( fd, TIOCGSIZE, &win ) == 0 ) {
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
	// TODO: delete the previous bar

	//
	const unsigned short int cols = this->getTerminalWidth( fileno( stdout ) );

	// draw the current progress
	putchar( '[' );
	for( int i = 0; i < 50; ++i ) {
		putchar( '-' );
	}
	putchar( ']' );

	// print
	fputs( "   0%\n", stdout );
}
