#ifndef INCLUDED_INPUTSOURCE_H
#define INCLUDED_INPUTSOURCE_H

#include <string>
using namespace std;

class CInputSystem;

enum ESourceType
{
	SourceInvalid = -1,
	SourceEmpty = 0,
	SourceSwitch = 1,
	SourceHalfAxis = 2,
	SourceFullAxis = 3
};
 
/*
 * Provides values to inputs, either in the form of a bool for switch inputs or an int value within a given range for analog/axis inputs.
 */
class CInputSource
{
protected:
	CInputSource(ESourceType sourceType);

public:
	const ESourceType type;

	//
	// Static helper methods
	//

	/*
	 * Clamps the given value to between the min and max values.
	 */
	static int Clamp(int val, int minVal, int maxVal);

	/*
 	 * Scales the given value, that falls within the stated 'from' range, to be between the given 'to' range.
	 */
	static int Scale(int val, int fromMinVal, int fromMaxVal, int toMinVal, int toMaxVal);

	/*
	 * Scales the given value, that falls within the stated 'from' range, to be between the given 'to' range.
	 * The off values are supplied to avoid rounding errors and ensure that the scaled value has the correct off value when required.
	 */
	static int Scale(int val, int fromMinVal, int fromOffVal, int fromMaxVal, int toMinVal, int toOffVal, int toMaxVal);

	/*
	 * Returns true if this source represents a switch input (such as a button).  Otherwise it is assumed to be an analog input (such as axis or pedal).
	 */
	ESourceType GetType();

	/*
	 * Returns true if the source is active (taken from GetValueAsSwitch).
	 */
	bool IsActive();

	/*
	 * Reads a boolean value for a switch input.
	 * Returns true if the value was set.
	 */
	virtual bool GetValueAsSwitch(bool &val) = 0;

	/*
	 * Reads an int value for an analog/axis input, guaranteeing that the value falls within the given range and has the correct off value when required.
	 * Returns true if the value was set.
	 */
	virtual bool GetValueAsAnalog(int &val, int minVal, int offVal, int maxVal) = 0;
};

#endif // INCLUDED_INPUTSOURCE_H