#include <timmilicious/timmilicious.hxx>
#include <timmilicious/ui/ProgressBar.hxx>
#include <unistd.h>
using namespace timmilicious::ui;

int main( int, char ** ) {
	ProgressBar *testBar = new ProgressBar();

	std::cout << "ProgressBar using libTimmilicious " << timmilicious::getAPIVersion()
		  << " (" << timmilicious::getABIVersion() << ")" << std::endl << std::endl;

	testBar->setStatusText( "Processing images..." );
	testBar->setMaxProgress( 1000 );
	testBar->showTimeEstimation( true );

	for( int i = 0; i < 1000; ++i ) {
		testBar->increaseProgress();
		testBar->updateProgress();
		usleep( 10000 );
	}

	delete testBar;
	return 0;
}
