#if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ )
	#define __TIMMILICIOUS_UI_PROGRESSBAR_HXX__

//
#include <stdexcept>
#include <string>

namespace timmilicious {

	namespace ui {

		class ProgressBar {
			public:
				ProgressBar();
				virtual ~ProgressBar();

				void setStatusText( const std::string & status ) throw( );
				void updateProgress() throw( );
				unsigned int getProgress() const throw( );
				void setProgress( const unsigned int progress, bool refresh = false ) throw( std::range_error );
				void setMaxProgress( const unsigned int progress ) throw( std::range_error );
				unsigned int getMaxProgress() const throw( );

			private:
				unsigned short int getTerminalWidth( int fileDescriptor ) const throw( );

				std::string mStatusText;
				unsigned int mMaxProgress;
				unsigned int mCurrentProgress;

		}; /* class ProgressBar */

	} /* namespace ui */

} /* namespace timmilicious*/

#endif /* if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ ) */
