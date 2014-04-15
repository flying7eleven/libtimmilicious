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
#include <timmilicious/timmilicious.hxx>
#include <timmilicious/ui/ProgressBar.hxx>
#include <boost/thread/lock_guard.hpp>
#include <cstdio>
#include <cstring> // memset
#include <unistd.h>
#include <sys/ioctl.h>

using namespace timmilicious::ui;

ProgressBar::ProgressBar( const std::string & statusText, short int progressBarWidth ) throw( std::invalid_argument ) {
	this->mCurrentProgress = 0;
	this->mMaxProgress = 100;
	this->mProgressBarWidth = progressBarWidth;
	this->mStatusText = statusText;
	this->mShowTimeEstimation = false;
	this->mTimePerElementRequired.clear();

	// be sure that the progress bar width is at least not negative
	if( progressBarWidth < 0 ) {
		throw std::invalid_argument( "The progress bar width has to be positive." );
	}

	// show the current status automatically, just if a pre-defined status text was set
	if( this->mStatusText.length() > 0 ) {
		this->updateProgress();
	}
}

ProgressBar::~ProgressBar() throw( ) {
	// nothing to do here
}

void ProgressBar::showTimeEstimation( const bool & show ) throw( ) {
	this->mShowTimeEstimation = show;
}

void ProgressBar::setProgress( const int progress, bool refresh ) throw( std::range_error, std::invalid_argument ) {
	if( unlikely( progress < 0 ) ) {
		throw std::invalid_argument( "The progress cannot be less than zero." );
	}
	if( unlikely( progress > this->mMaxProgress ) ) {
		throw std::range_error( "The new progress must be between 0 and the max. value of the progress." );
	}
	this->mCurrentProgress = progress;
	if( refresh ) {
		this->updateProgress();
	}
}

void ProgressBar::setProgressTS( const int progress, bool refresh ) throw( std::range_error, std::invalid_argument ) {
	boost::lock_guard< boost::mutex > guard( this->mCurrentProgressValueMutex );

	this->setProgress( progress, refresh );
}

unsigned int ProgressBar::getProgress() const throw( ) {
	return this->mCurrentProgress;
}

void ProgressBar::increaseProgress( const int val, bool refresh ) throw( std::range_error, std::invalid_argument ) {
	if( unlikely( val < 1 ) ) {
		throw std::invalid_argument( "The increment value has to been 1 or higher." );
	}
	if( unlikely( val + this->mCurrentProgress > this->mMaxProgress ) ) {
		throw std::range_error( "The new progress must be between 0 and the max. value of the progress. It seems that the max. value gets exceeded." );
	}
	this->mProgressTimer.stop();
	this->mTimePerElementRequired = this->mProgressTimer.elapsed(); // TODO: do a better estimation
	this->mCurrentProgress += val;
	if( refresh ) {
		this->updateProgress();
	}
	this->mProgressTimer.start();
}

void ProgressBar::increaseProgressTS( const int val, bool refresh ) throw( std::range_error, std::invalid_argument ) {
	boost::lock_guard< boost::mutex > guard( this->mCurrentProgressValueMutex );

	this->increaseProgress( val, refresh );
}

unsigned int ProgressBar::getMaxProgress() const throw( ) {
	return this->mMaxProgress;
}

unsigned short int ProgressBar::getTerminalWidth( int fileDescriptor ) const throw( ) {
	const unsigned short default_tty = 80;
	const unsigned short default_notty = 0;
	unsigned short termwidth = 0;

	//
	if( unlikely( !isatty( fileDescriptor ) ) ) {
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
	if( likely( ioctl( fileDescriptor, TIOCGWINSZ, &win ) == 0 ) ) {
		termwidth = win.ws_col;
	}
#endif

	//
	return termwidth == 0 ? default_tty : termwidth;
}

void ProgressBar::setStatusText( const std::string & status ) throw( ) {
	this->mStatusText = status;
}

void ProgressBar::setMaxProgress( const int max ) throw( std::range_error, std::invalid_argument ) {
	if( unlikely( max < 1 ) ) {
		throw std::invalid_argument( "The maximum value must be at least 1." );
	}
	if( unlikely( max < this->mCurrentProgress ) ) {
		throw std::range_error( "The maximum value must be the same as the current progress or higher." );
	}
	this->mMaxProgress = max;
}

void ProgressBar::updateProgress() throw( std::length_error ) {
	char percentBuffer[ 6 ];

	// clear the percent buffer
	memset( percentBuffer, 0, sizeof( char ) * 6 );

	// get the current number of columns for the active terminal
	const unsigned short int terminalColumns = this->getTerminalWidth( fileno( stdout ) );

	// calculate some important values
	const float currentProgress = ( static_cast< float >( this->mCurrentProgress ) / static_cast< float >( this->mMaxProgress ) ) * 100.0f;
	const unsigned short int timingColumns = this->mShowTimeEstimation ? 6 : 0;
	const short int numberOfSpaces = terminalColumns - this->mProgressBarWidth - 2 - 5 - this->mStatusText.length() - timingColumns; // progress indicator - bar indicator - number pct - status len
	const unsigned short int progressDone = static_cast< unsigned short int >( currentProgress / ( 100.0f / this->mProgressBarWidth ) );
	const unsigned short int progressNotDone = this->mProgressBarWidth - progressDone;

	// show the text for the current status the user has set
	fputs( this->mStatusText.c_str(), stdout );

	// write the current progress as a number into a buffer
	sprintf( percentBuffer, "% 4d%%", static_cast< int >( currentProgress ) );

	// just show the progress bar if we have enough room to do that
	if( ( numberOfSpaces + timingColumns ) > 0 ) {

		// put in as many spaces that the progress bar is right-aligned
		for( short int i = 0; i < numberOfSpaces; ++i ) {
			putchar( ' ' );
		}

		// if the time estimation should be displayed (and there is enough space), show it here
		if( this->mShowTimeEstimation && numberOfSpaces > 0 ) {
			if( this->mTimePerElementRequired.wall > 0.0 ) {
				boost::timer::nanosecond_type const oneSecond( 1 * 1000000000LL );
				double secondsRemaining = ( this->mTimePerElementRequired.wall * static_cast< double >( this->mMaxProgress - this->mCurrentProgress ) ) / oneSecond;
				const unsigned short int minutesRemaining = static_cast< unsigned short int >( secondsRemaining / 60.0 );
				secondsRemaining -= 60.0 * minutesRemaining;
				fprintf( stdout, "%02d:%02d ", minutesRemaining, static_cast< int >( secondsRemaining + 0.5 ) );
			} else {
				fputs( "--:-- ", stdout );
			}
		}
		// if the estimation should be displayed, but there is not enough room, print the missing spaces instead
		else if( this->mShowTimeEstimation ) {
			for( unsigned short int i = 0; i < ( numberOfSpaces + timingColumns ); ++i ) {
				putchar( ' ' );
			}
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
	// since there is not enough room for the progress bar, right-align the progress indicator instead
	else {
		const short int numberOfSpaces2 = terminalColumns - 5 - this->mStatusText.length(); // number pct - status len

		// if there is even not enough room for that, throw an exception
		if( unlikely( numberOfSpaces2 < 0 ) ) {
			throw std::length_error( "There is not enough space to show any kind of progress indicator." );
		}

		// put in as many spaces that the progress number is right-aligned
		for( short int i = 0; i < numberOfSpaces2; ++i ) {
			putchar( ' ' );
		}
	}

	// print the current progress as number
	fputs( percentBuffer, stdout );
	if( unlikely( this->mCurrentProgress == this->mMaxProgress ) ) {
		fputs( "\n", stdout );
	} else {
		fputs( "\r", stdout );
	}
	fflush( stdout );
}
