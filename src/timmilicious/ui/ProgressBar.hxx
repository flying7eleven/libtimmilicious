#if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ )
	#define __TIMMILICIOUS_UI_PROGRESSBAR_HXX__

//
#include <stdexcept>

namespace timmilicious {

	namespace ui {

		class ProgressBar {
			public:
				ProgressBar();
				virtual ~ProgressBar();

				void updateProgress() throw( );
				float getProgress() const throw( );
				void setProgress( const float progress, bool refresh = false ) throw( std::range_error );

			private:
				unsigned short int getTerminalWidth( int fileDescriptor ) const throw( );

				float mMaxProgress;
				float mCurrentProgress;

		}; /* class ProgressBar */

	} /* namespace ui */

} /* namespace timmilicious*/

#endif /* if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ ) */
