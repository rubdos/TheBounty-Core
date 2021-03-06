/****************************************************************************
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef Y_MONITOR_H
#define Y_MONITOR_H

#include <yafray_config.h>

__BEGIN_YAFRAY
//! Progress bar abstract class with pure virtual members
class YAFRAYCORE_EXPORT progressBar_t
{
	public:
		virtual ~progressBar_t(){}
		//! initialize (or reset) the monitor, give the total number of steps that can occur
		virtual void init(int totalSteps) = 0;
		//! update the montior, increment by given number of steps; init has to be called before the first update.
		virtual void update(int steps = 1) = 0;
		//! finish progress bar. It could output some summary, simply disappear from GUI or whatever...
		virtual void done() = 0;
		//! method to pass some informative text to the progress bar in case needed
		virtual void setTag(const char* text) = 0;
};

/*! the default console progress bar (implemented in console.cc)
*/
class YAFRAYCORE_EXPORT ConsoleProgressBar_t : public progressBar_t
{
	public:
		ConsoleProgressBar_t(int cwidth = 80);
		virtual void init(int totalSteps);
		virtual void update(int steps=1);
		virtual void done();
		virtual void setTag(const char* text) {};
		
	protected:
		int width, totalBarLen;
		int lastBarLen;
		int nSteps;
		int doneSteps;
};


__END_YAFRAY

#endif // Y_MONITOR_H
