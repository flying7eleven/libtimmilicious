#include <timmilicious/ui/ProgressBar.hxx>
#include <unistd.h>
using namespace timmilicious::ui;

int main( int, char ** ) {
	ProgressBar *testBar = new ProgressBar();

	testBar->setStatusText( "Processing images..." );
	testBar->setMaxProgress( 1000 );

	for( int i = 0; i < 1000; ++i ) {
		testBar->increaseProgress();
		testBar->updateProgress();
		usleep( 10000 );
	}

	delete testBar;
	return 0;
}
