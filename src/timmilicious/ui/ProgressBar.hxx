#if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ )
	#define __TIMMILICIOUS_UI_PROGRESSBAR_HXX__

// include the required headers
#include <stdexcept>
#include <string>

namespace timmilicious {

	namespace ui {

		/**
		 * A simple progress bar for indicating a longer progress on the console (stdout). It
		 * can deal with different width of the terminal and adapts the progress bar size if
		 * the terminal gets resized.
		 */
		class ProgressBar {
			public:
				/**
				 * \brief Default constructor of this class.
				 */
				ProgressBar() throw( );

				/**
				 * \brief Default destructor of this class.
				 */
				virtual ~ProgressBar() throw( );

				/**
				 * Set the status text for the progress indicator.
				 *
				 * \param[in] status The text to display.
				 */
				void setStatusText( const std::string & status ) throw( );

				/**
				 * Redraw the progress line with the current state of the progress bar.
				 */
				void updateProgress() throw( );

				/**
				 * Get the current progress.
				 *
				 * Get the current progress of the progress bar. This is *NOT* a percent value.
				 * its the value stored by setProgress(...).
				 *
				 * \return The value for the current process.
				 */
				unsigned int getProgress() const throw( );

				/**
				 * Set the current progress.
				 *
				 * \param[in] progress The progress to set.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 */
				void setProgress( const unsigned int progress, bool refresh = false ) throw( std::range_error );

				/**
				 * Increases the current progress value by a value.
				 *
				 * \param[in] val The value to increase the progress value by.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 */
				void increaseProgress( const unsigned int val = 1, bool refresh = false ) throw( std::range_error );

				/**
				 * Set the maximum value for the progress.
				 *
				 * \param[in] max The new max. progress value.
				 *
				 * \throws std::range_error Will be thrown if the new maximum value is lower than the current progress value.
				 */
				void setMaxProgress( const unsigned int max ) throw( std::range_error );

				/**
				 * Get the current max. progress value.
				 *
				 * \return The current max. progress value.
				 */
				unsigned int getMaxProgress() const throw( );

			private:

				/**
				 * Get the current width of the terminal.
				 *
				 * \param[in] fileDesciptor The file descriptor of the terminal to query.
				 *
				 * \return The width (in character counts) for the specified terminal.
				 */
				unsigned short int getTerminalWidth( int fileDescriptor ) const throw( );

				std::string mStatusText; // <<< The current status text to use.
				unsigned int mMaxProgress; // <<< The currently set max. progress value.
				unsigned int mCurrentProgress; // <<< The current progress value.

		}; /* class ProgressBar */

	} /* namespace ui */

} /* namespace timmilicious*/

#endif /* if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ ) */
