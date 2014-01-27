#include <timmilicious/ui/ProgressBar.hxx>
using namespace timmilicious::ui;

int main( int, char ** ) {
	ProgressBar *testBar = new ProgressBar();

	testBar->updateProgress();

	delete testBar;
	return 0;
}
