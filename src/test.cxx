#include <timmilicious/ui/ProgressBar.hxx>
using namespace timmilicious::ui;

int main( int, char ** ) {
	ProgressBar *testBar = new ProgressBar();

	testBar->setStatusText( "Processing images..." );
	testBar->setMaxProgress( 1000 );

	for( int i = 0; i <= 1000; ++i ) {
		testBar->setProgress( i );
		testBar->updateProgress();
	}

	delete testBar;
	return 0;
}
