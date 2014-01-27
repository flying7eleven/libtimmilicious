#include <timmilicious/ui/ProgressBar.hxx>
#include <cstdio>
using namespace timmilicious::ui;

ProgressBar::ProgressBar() {
	this->mCurrentProgress = 0.0f;
	this->mMaxProgress = 100.0f;
}

ProgressBar::~ProgressBar() {
	// nothing to do here
}

void ProgressBar::setProgress( const float progress, bool refresh ) throw( std::range_error ) {
	if( progress > this->mMaxProgress || progress < 0.0f ) {
		throw std::range_error( "The new progress must be between 0.0 and the max. value of the progress." );
	}
	this->mCurrentProgress = progress;
	if( refresh ) {
		this->updateProgress();
	}
}

float ProgressBar::getProgress() const throw( ) {
	return this->mCurrentProgress;
}

void ProgressBar::updateProgress() throw( ) {
	// TODO: delete the previous bar

	// draw the current progress
	putchar( '[' );
	for( int i = 0; i < 100; ++i ) {
		putchar( '-' );
	}
	putchar( ']' );
}
