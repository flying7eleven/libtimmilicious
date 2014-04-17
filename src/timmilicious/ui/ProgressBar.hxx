/**
 * This file is part of libTimmilicious.
 * Copyright (C) 2014 Tim Hütz
 *
 * libTimmilicious is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libTimmilicious is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * ERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libTimmilicious. If not, see <http://www.gnu.org/licenses/>.
 */
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
				 * \param[in] statusText The text which describes the status of the progress bar.
				 * \param[in] progressBarWidth The width of the progress bar in columns.
				 *
				 * \throws std::invalid_argument Will be thrown if the progressBarWidth parameter is negative.
				 */
				ProgressBar( const std::string & statusText = "", short int progressBarWidth = 50 ) noexcept( false );

				/**
				 * \brief Default destructor of this class.
				 */
				virtual ~ProgressBar() noexcept;

				/**
				 * Set the status text for the progress indicator.
				 *
				 * \param[in] status The text to display.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				void setStatusText( const std::string & status ) noexcept;

				/**
				 * Redraw the progress line with the current state of the progress bar.
				 *
				 * \throws std::length_error Will be thrown if the space for showing any kind of the progress indicator is to small.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				void updateProgress() noexcept( false );

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
				int getProgress() const noexcept;

				/**
				 * Set the current progress.
				 *
				 * \param[in] progress The progress to set.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 * \throws std::invalid_argument Will be thrown if the progress value is less than zero.
				 *
				 * \warning The method is *NOT* thread-safe. Use the method with the TS prefix instead.
				 */
				void setProgress( const int progress, bool refresh = false ) noexcept( false );

				/**
				 * Set the current progress.
				 *
				 * \param[in] progress The progress to set.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 * \throws std::invalid_argument Will be thrown if the progress value is less than zero.
				 *
				 * \remarks This is a thread-safe implementation.
				 */
				void setProgressTS( const int progress, bool refresh = false ) noexcept( false );
				/**
				 * Increases the current progress value by a value.
				 *
				 * \param[in] val The value to increase the progress value by.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 * \throws std::invalid_argument Will be thrown if value is set to an negative value or zero.
				 *
				 * \warning The method is *NOT* thread-safe. Use the method with the TS prefix instead.
				 */
				void increaseProgress( const int val = 1, bool refresh = false ) noexcept( false );

				/**
				 * Increases the current progress value by a value.
				 *
				 * \param[in] val The value to increase the progress value by.
				 * \param[in] refresh If set to true, the progress bar will be redrawn automatically, if false nothing will be done.
				 *
				 * \throws std::range_error Will be thrown if the value is higher than the max. value for the progress.
				 * \throws std::invalid_argument Will be thrown if value is set to an negative value or zero.
				 *
				 * \remarks This is a thread-safe implementation.
				 */
				void increaseProgressTS( const int val = 1, bool refresh = false ) noexcept( false );
				/**
				 * Set the maximum value for the progress.
				 *
				 * \param[in] max The new max. progress value.
				 *
				 * \throws std::range_error Will be thrown if the new maximum value is lower than the current progress value.
				 * \throws std::invalid_argument Will be thrown if max. value for the progress bar should be zero or less.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				void setMaxProgress( const int max ) noexcept( false );

				/**
				 * Get the current max. progress value.
				 *
				 * \return The current max. progress value.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				int getMaxProgress() const noexcept;

				/**
				 * Specify if the time estimation should be displayed or not.
				 *
				 * \param[in] show True if the time estimation should be displayed, false if not.
				 *
				 * \warning The method is *NOT* thread-safe. Therefore, timings shown while this
				 *          option is on are *NOT* correct.
				 */
				void showTimeEstimation( const bool & show ) noexcept;

			private:

				/**
				 * Get the current width of the terminal.
				 *
				 * \param[in] fileDescriptor The file descriptor of the terminal to query.
				 *
				 * \return The width (in character counts) for the specified terminal.
				 *
				 * \warning The method is *NOT* thread-safe.
				 */
				unsigned short int getTerminalWidth( int fileDescriptor ) const noexcept;

				std::string mStatusText; // <<< The current status text to use.
				int mMaxProgress; // <<< The currently set max. progress value.
				int mCurrentProgress; // <<< The current progress value.
				short int mProgressBarWidth; // <<< The size of the progress indiciator.
				boost::mutex mCurrentProgressValueMutex; // <<< The mutex to make the current progress thread-safe
				bool mShowTimeEstimation; // <<< Should the time estimation be shown?
				boost::timer::cpu_timer mProgressTimer; // <<< A timer used for estimating the runtime.
				boost::timer::cpu_times mTimePerElementRequired; // <<< The variable which stores the estimated time per element required.

		}; /* class ProgressBar */

	} /* namespace ui */

} /* namespace timmilicious*/

#endif /* if !defined( __TIMMILICIOUS_UI_PROGRESSBAR_HXX__ ) */
