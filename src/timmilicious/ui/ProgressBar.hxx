#if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ )
	#define __TIMMILICIOUS_UI_PROGRESSBAR_HXX__

// include the required headers
#include <stdexcept>
#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/timer/timer.hpp>

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
				 *
				 * \param[in] progressBarWidth The width of the progress bar in columns.
				 */
				ProgressBar( unsigned short int progressBarWidth = 50 ) throw( );

				/**
				 * \brief Default destructor of this class.
				 */
				virtual ~ProgressBar() throw( );

				/**
				 * Set the status text for the progress indicator.
				 *
				 * \param[in] status The text to display.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				void setStatusText( const std::string & status ) throw( );

				/**
				 * Redraw the progress line with the current state of the progress bar.
				 *
				 * \throws std::length_error Will be thrown if the space for showing any kind of the progress indicator is to small.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				void updateProgress() throw( std::length_error );

				/**
				 * Get the current progress.
				 *
				 * Get the current progress of the progress bar. This is *NOT* a percent value.
				 * its the value stored by setProgress(...).
				 *
				 * \return The value for the current process.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				unsigned int getProgress() const throw( );

				/**
				 * Set the current progress.
				 *
				 * \param[in] progress The progress to set.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 *
				 * \warning The method is *NOT* thread-safe. Use the method with the TS prefix instead.
				 */
				void setProgress( const unsigned int progress, bool refresh = false ) throw( std::range_error );

				/**
				 * Set the current progress.
				 *
				 * \param[in] progress The progress to set.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 *
				 * \remarks This is a thread-safe implementation.
				 */
				void setProgressTS( const unsigned int progress, bool refresh = false ) throw( std::range_error );
				/**
				 * Increases the current progress value by a value.
				 *
				 * \param[in] val The value to increase the progress value by.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 *
				 * \warning The method is *NOT* thread-safe. Use the method with the TS prefix instead.
				 */
				void increaseProgress( const unsigned int val = 1, bool refresh = false ) throw( std::range_error );

				/**
				 * Increases the current progress value by a value.
				 *
				 * \param[in] val The value to increase the progress value by.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 *
				 * \remarks This is a thread-safe implementation.
				 */
				void increaseProgressTS( const unsigned int val = 1, bool refresh = false ) throw( std::range_error );
				/**
				 * Set the maximum value for the progress.
				 *
				 * \param[in] max The new max. progress value.
				 *
				 * \throws std::range_error Will be thrown if the new maximum value is lower than the current progress value.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				void setMaxProgress( const unsigned int max ) throw( std::range_error );

				/**
				 * Get the current max. progress value.
				 *
				 * \return The current max. progress value.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				unsigned int getMaxProgress() const throw( );

				/**
				 * Specify if the time estimation should be displayed or not.
				 *
				 * \param[in] show True if the time estimation should be displayed, false if not.
				 *
				 * \warning The method is *NOT* thread-safe. Therefore, timings shown while this
				 *          option is on are *NOT* correct.
				 */
				void showTimeEstimation( const bool & show ) throw( );

			private:

				/**
				 * Get the current width of the terminal.
				 *
				 * \param[in] fileDesciptor The file descriptor of the terminal to query.
				 *
				 * \return The width (in character counts) for the specified terminal.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				unsigned short int getTerminalWidth( int fileDescriptor ) const throw( );

				std::string mStatusText; // <<< The current status text to use.
				unsigned int mMaxProgress; // <<< The currently set max. progress value.
				unsigned int mCurrentProgress; // <<< The current progress value.
				unsigned short int mProgressBarWidth; // <<< The size of the progress indiciator.
				boost::mutex mCurrentProgressValueMutex; // <<< The mutex to make the current progress thread-safe
				bool mShowTimeEstimation; // <<< Should the time estimation be shown?
				boost::timer::cpu_timer mProgressTimer; // <<< A timer used for estimating the runtime.
				boost::timer::cpu_times mTimePerElementRequired; // <<< The variable which stores the estimated time per element required.

		}; /* class ProgressBar */

	} /* namespace ui */

} /* namespace timmilicious*/

#endif /* if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ ) */
