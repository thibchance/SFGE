/*
 MIT License

 Copyright (c) 2017 SAE Institute Switzerland AG

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef SFGE_TIME_UTILITY_H_
#define SFGE_TIME_UTILITY_H_

namespace sfge
{

/**
* \brief Timer utility class used to measure time
*/
class Timer
{
public:
	Timer(float time, float period);
	/**
	* \brief Called each frame to lower the m_Time amount
	*/
	void Update(float dt);
	/**
	* \brief Check if the Timer is over 
	*/
	bool IsOver();
	/**
	* \brief Reset the m_Time to the value of the m_Period
	*/
	void Reset();

	/**
	* \brief Return the ratio between 0.0 and 1.0 of the current time
	*/
	float GetCurrent();
	/**
	* \brief Return the current time since the timer started
	*/
	float GetCurrentTime();
	/**
	* Getter of the period
	*/
	float GetPeriod() const;
	/**
	* Setter of the period
	*/
	void SetPeriod(float period);
	/**
	* \brief Getter of the time
	*/
	float GetTime() const;
	/**
	* \brief Setter of the time
	*/
	void SetTime(float time);


private:
	float m_Time;
	float m_Period;
};
}

#endif /* INCLUDE_UTILITY_TIME_UTILITY_H_ */
