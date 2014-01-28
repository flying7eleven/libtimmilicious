#include <timmilicious/ui/ProgressBar.hxx>
using namespace timmilicious::ui;

int main( int, char ** ) {
	ProgressBar *testBar = new ProgressBar();

	testBar->setStatusText( "Processing images..." );
	testBar->setMaxProgress( 1000 );
	testBar->setProgress( 0 );

	delete testBar;
	return 0;
}
